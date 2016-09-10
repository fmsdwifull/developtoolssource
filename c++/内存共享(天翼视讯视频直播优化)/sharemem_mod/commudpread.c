#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>

#include <sys/select.h>
#include <time.h>

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#include "shm_write.h"


#define PORT 3333
#define IP  "192.168.0.108"
#define BUFFER_SIZE 1

int sfd=-1;
int flag=0;
_tx  *udp_buf;


pthread_t udprecvid;

char buf[50];



void* WaitDateFunc(void)
{
	int len=0;
	printf("enter pthread\n");
	while(1)
	{
		if((len=UdpRecvBuff())==0)
		{
			printf("recv error\n");
			exit(-1);
		}else{
			printf("have data \n");
			udp_buf->have_data=1;
		}
		
		usleep(100);
		printf("#\n");
	}

}

/****************************************************/
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

	 if((ret=pthread_create(&udprecvid,NULL,(void *)WaitDateFunc,NULL))!=0)
	 {
		perror("creat_pthread error");
	 }	
	 //pthread_join(udprecvid,&status);

}

//---------------------------------------------------------------------------
int UdpRecvBuff(void)
{

  struct sockaddr_in From;
  int addr_len;
  int nSize;

  memset(&From, 0, sizeof(struct sockaddr_in));
  
  From.sin_family = AF_INET   ;
  From.sin_port = htons(3333);
  From.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(LocalIP);//INADDR_ANY;
  addr_len=sizeof(From);
  

  bind(sfd, (struct sockaddr *)&From, sizeof(From));
  
  if((nSize=recvfrom(sfd,udp_buf,sizeof(_tx),0,(struct sockaddr *)&From,&addr_len))==0)
  {
	  perror("recvfrom error");
  }else
	  printf("rec data is :%s,%s\n",udp_buf->channel_text,udp_buf->filedate_text);

  return nSize;

}


void CloseUdpSocket(void)
{
  pthread_cancel(udprecvid);
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
