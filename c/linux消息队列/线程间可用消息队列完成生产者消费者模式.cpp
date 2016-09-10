#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <pthread.h>

#include <unistd.h>


#define BUFFER_SIZE 16 // 缓冲区数量




void *producer(void *data)
{
	int msgid;
	int i=0;
	struct msgtype_s 
	{
    	long mtype;
    	char buffer[1024];
	};

	struct msgtype_s msg;
	
	if((msgid=msgget(1022,   IPC_CREAT|0666))==-1)
    {
        fprintf(stderr,"Creat Message  Error:%s\n", strerror(errno));
        exit(1);
    }
	msg.mtype = 2;
    


	//msgsnd(msgid, &msg, sizeof(struct msgtype), 0); 
    //memset(&msg, '/0', sizeof(struct msgtype));
    //msgrcv(msgid, &msg, sizeof(struct msgtype), 2, 0);
    //fprintf(stderr, "Client receive:%s/n", msg.buffer);
    //exit(0);


   
	while(1)
	{
		
		strcpy(msg.buffer, "hello americal");
		//sprintf(msg.buffer,"%s",i++);
		msgsnd(msgid, &msg, sizeof(msg.buffer), IPC_NOWAIT); 
		//memset(&msg, 0, sizeof(struct msgtype_s));

		fprintf(stderr, "Client send:%s\n", msg.buffer);
		
		sleep(2);
	}
}

void *consumer(void *data)
{
	struct msgtype_r 
	{
    	long mtype;
    	char buffer[1024];
	};

	struct msgtype_r msg;
    //key_t key;
    int msgid;
	msg.mtype = 1;
	if((msgid=msgget(1022, IPC_EXCL))==-1)
    {
        fprintf(stderr,"Creat Message  Error:%s/n", strerror(errno));
        exit(1);
    }
	while(1)
	{
		msgrcv(msgid, &msg, sizeof(msg.buffer), 2, IPC_NOWAIT|MSG_NOERROR);
		printf("recv :%s\n",msg.buffer);
		memset(&msg, 0, sizeof(msg.buffer));
		sleep(1);
	}
}

int main(void)
{
    pthread_t th_a, th_b;

    /* 创建生产者和消费者线程*/
    pthread_create(&th_a, NULL, producer, 0);
    pthread_create(&th_b, NULL, consumer, 0);
    /* 等待两个线程结束*/
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    return 0;
}