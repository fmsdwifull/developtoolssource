
/**************************************************************************************************************
 **文件:client.c
 **编写者:liusaiiyu
 **编写日期:
 **简要描述:TCP客户端
 **修改者:
 **修改日期:2012年11月5号
 **注:客户端可随时收发数据
 **************************************************************************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

#define IP "127.0.0.1"
#define PORT 6676

/****** 线程：客户端接收程序 *************************************************************************************/
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
    while(1)
    {   
        memset(&ser_addr, 0, len);
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
    int len =  -1;
    pthread_t pid;
    void *retval = NULL;
    char buf[128] = {0};
    struct sockaddr_in ser_addr;

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
    ser_addr.sin_addr.s_addr = inet_addr(IP);
    
    //connect
    cnt = connect(sfd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr));
    if(0 > cnt)
    {
        perror("connect err:");
        goto _out;
    }else{
    printf("connect service success\n");
    }
        
    //create pthread
    cnt = pthread_create(&pid, NULL, fun_recvfrom, &sfd);
    if(0 > cnt)
    {
        perror("pthread create err:");
        goto _out;
    }   
    
    //客户端发送信息
    while(1)
    {
        len = sizeof(struct sockaddr);
        //init buf
        fgets(buf, sizeof(buf), stdin);
        //sendto
        cnt = sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&ser_addr, len);
        if(0 > cnt)
        {
            perror("send to err:");
            goto _out;
        }
    }
    
    //wait
    pthread_join(pid, (void *)&retval); 

    //close
    close(sfd);
    return 0;
_out:
    close(sfd);
    return -1;
}

