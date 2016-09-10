
/**************************************************************************************************************
 **文件:server.c
 **编写者:liusaiyu
 **编写日期:
 **简要描述:TCP服务器
 **修改者:
 **修改日期:\
 **注:服务器可随时收发数据,但服务器和客户端都没有正常退出机制
 **************************************************************************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

#define PORT 6676
#define BACKLOG 30


//长整形转点型IP：inet_ntoa(from.sin_addr)
//点型转网络地址：inet_addr(SERVER_IP);

void *fun_recvfrom(void *agrv)
{
    int sfd = -1;
    int cnt = -1;
    int len = -1;
    char buf[128] = {0};
    time_t my_time;
    struct sockaddr_in ser_addr;

    len = sizeof(struct sockaddr);
    sfd = *(int *)agrv;
    printf("the require is :%d\n",sfd);
    while(1)
    {
        memset(&ser_addr, 0, len);
        memset(buf, 0, sizeof(buf));
        cnt = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&ser_addr, &len); 
        if(0 > cnt)
        {
            perror("recvfrom err:");
            return;
        }
        my_time = time(&my_time);
        printf("%s", ctime(&my_time));
        printf("server : %s", buf);
    }
    return;
}

int main(void)
{
    int cnt =  -1;
    int sfd =  -1;
    int afd =  -1;
    int len =  -1;
    pthread_t pid;
    void *retval = NULL;
    char buf[128] = {0};
    struct sockaddr_in ser_addr;
    struct sockaddr_in from;

    //socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sfd)
    {
        perror("socket err:");
        goto _out;
    }

    //init
    memset(&ser_addr, 0, sizeof(struct sockaddr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    
    /*************************************************************************
    *个人理解是，对方往本机IP端口发信息，不绑定，无法接受。SOCKET相当于一块空间
    *绑定了，我才知道把对应的这个IP端口接收到的信息放到对应的SOCKET空间中。
    **************************************************************************/
    cnt = bind(sfd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr));
    if(0 > cnt)
    {
        perror("bind err:");
        goto _out;
    }

    /*************************************************************
    *listen其实并未开始连线，只是把SOCKET设置为listen模式
    *真正接受客户端连接的是后面的accept函数。 第一个参数为
    *创建的socket描述符，第二个参数为最大连接数，如果超过最大
    *连接数，client会受到拒绝的错误
    *listen只适用sock_stream或sock_seqpacket的socket，如果为AF_INET
    *则第二个参数只能设置为128.成功返回0，错误返回-1，错误代码errno
    ***************************************************************/
    cnt = listen(sfd, BACKLOG);

    if( cnt==-1)
    {
        perror("listen err:");
        goto _out;
    }
    
    len = sizeof(struct sockaddr);
    memset(&from, 0, sizeof(struct sockaddr));

    
    /********************************************************************
    *处于监听状态的服务器在获得客户端的连接请求后，会将其放置在等待队列中
    *当系统空闲时，该函数将从队列中获得请求连接信息，创建同类型的新的套接
    *字，并返回该套接字的描述符。新的套接字用来通信，老的仍然在监听。阻塞
    *函数，成功返回新描述符，错误返回-1,错误代码在errno.
    *******************************************************************/
    afd = accept(sfd, (struct sockaddr *)&from, &len);
    printf("have new connect\n");
    if(0 > afd)
    {
        perror("accept err:");
        goto _out;
    }   

    //create pthread
    cnt = pthread_create(&pid, NULL, fun_recvfrom, &afd);
    if(0 > cnt)
    {
        perror("pthread create err:");
        goto _out;
    }   
    
    //发送信息给客户端
    while(1)
    {
        len = sizeof(struct sockaddr);
        //键盘输入
        fgets(buf, sizeof(buf), stdin);
        //sendto
        cnt = sendto(afd, buf, sizeof(buf), 0, (struct sockaddr *)&from, len);
        if(0 > cnt)
        {
            perror("send to err:");
            goto _out;
        }
    }
    //
    //wait：阻塞等待
    pthread_join(pid, (void *)&retval); 

    //close
    close(sfd);
    return 0;
_out:
    close(sfd);
    return -1;
}

