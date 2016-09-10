#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include "inotify.h"

#define PORT 3333
#define IP  "127.0.0.1"
#define BUFFER_SIZE 1

int sfd=-1;
int flag=0;
pthread_t udpsendid;

char buff[50]="#########################";

extern _tx *udp_buf;

void* WaitDateFunc(void)
{
    int len=0;

 
    while(1)
    {
    	
        if( udp_buf->have_data==1)
    	{
    		
            udp_buf->have_data=0;
            if((len=UdpSendBuff(sfd, IP,udp_buf,sizeof(_tx)))==-1)
    		{
                perror("send fail");
    		}else{
				printf("send success,date num is :%d\n",len);
			}
    		
    	}

        usleep(1000);
    }
}


void InitUdpSocket(int lPort)
{
    int ret=0;
    void* status=NULL; 

    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Create socket error\r\n");
        exit(-1);
    } else{
        printf("create socket.\n\r");
    }

     if((ret=pthread_create(&udpsendid,NULL,(void *)WaitDateFunc,NULL))!=0)
     {
        perror("creat_pthread error");
     }	
     //pthread_join(udpsendid,&status);

}

//---------------------------------------------------------------------------
int UdpSendBuff(int m_Socket, char *RemoteHost, _tx *buf,int nlength)
{

  struct sockaddr_in To;
  int nSize;

  To.sin_family=AF_INET;
  To.sin_port=htons(PORT);
  To.sin_addr.s_addr = inet_addr(RemoteHost);
  nSize=sendto(m_Socket,buf,nlength,0,(struct sockaddr*)&To,sizeof(struct sockaddr));
  return nSize;

}

void CloseUdpSocket(void)
{
  pthread_cancel(udpsendid);
  close(sfd);
 
}


#if 0
int main(void)
{
    flag=1;
    InitUdpSocket(3333);
    printf("please num:%d\n");
    scanf("%d\n",&flag);

    
    return 0;
}
#endif
