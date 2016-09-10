
/**************************************************************************************************************
 **�ļ�:server.c
 **��д��:liusaiyu
 **��д����:
 **��Ҫ����:TCP������
 **�޸���:
 **�޸�����:\
 **ע:����������ʱ�շ�����,���������Ϳͻ��˶�û�������˳�����
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


//������ת����IP��inet_ntoa(from.sin_addr)
//����ת�����ַ��inet_addr(SERVER_IP);

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
    *��������ǣ��Է�������IP�˿ڷ���Ϣ�����󶨣��޷����ܡ�SOCKET�൱��һ��ռ�
    *���ˣ��Ҳ�֪���Ѷ�Ӧ�����IP�˿ڽ��յ�����Ϣ�ŵ���Ӧ��SOCKET�ռ��С�
    **************************************************************************/
    cnt = bind(sfd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr));
    if(0 > cnt)
    {
        perror("bind err:");
        goto _out;
    }

    /*************************************************************
    *listen��ʵ��δ��ʼ���ߣ�ֻ�ǰ�SOCKET����Ϊlistenģʽ
    *�������ܿͻ������ӵ��Ǻ����accept������ ��һ������Ϊ
    *������socket���������ڶ�������Ϊ���������������������
    *��������client���ܵ��ܾ��Ĵ���
    *listenֻ����sock_stream��sock_seqpacket��socket�����ΪAF_INET
    *��ڶ�������ֻ������Ϊ128.�ɹ�����0�����󷵻�-1���������errno
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
    *���ڼ���״̬�ķ������ڻ�ÿͻ��˵���������󣬻Ὣ������ڵȴ�������
    *��ϵͳ����ʱ���ú������Ӷ����л������������Ϣ������ͬ���͵��µ��׽�
    *�֣������ظ��׽��ֵ����������µ��׽�������ͨ�ţ��ϵ���Ȼ�ڼ���������
    *�������ɹ������������������󷵻�-1,���������errno.
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
    
    //������Ϣ���ͻ���
    while(1)
    {
        len = sizeof(struct sockaddr);
        //��������
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
    //wait�������ȴ�
    pthread_join(pid, (void *)&retval); 

    //close
    close(sfd);
    return 0;
_out:
    close(sfd);
    return -1;
}

