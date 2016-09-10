
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <error.h>
#include <errno.h>

#define ROWNUM 23*3600 
#define FILLLENGTH 24  
#define CHNUMS 30
//#define FILLLENGTH 50  


typedef struct rq{
    char date_name[30];  //日期名称
    char index_file[ROWNUM][FILLLENGTH]; //ROWNUM表示这些文件有这么多，FILLLENGTH表示文件名称这么长
}Rq;

typedef struct pd{
    char channel_name[20];//频道名
    Rq datearray[3]; //日期结构，下面定义
}Pd;


int datefile_num=0;
Pd *share_mems;
void *shared_memory = (void *)0;

static int channel_num;

/***************conver str to time*****************************/
time_t StrToSec(const char *strtm)
{
	char *str=NULL;
	char arrt[20];
	int  hour=0,min=0,sec=0;
    //notice please
	if(strcpy(arrt,strtm)==NULL)
	{
		printf("xxxxxxxxxxxxxx\n");
		exit(-1);
	}
 
	//printf("%s\n",strtm);
    if((str=strtok(arrt,":"))!=NULL)
	    hour=atoi(str);
	if((str=strtok(NULL,":"))!=NULL)
	    min=atoi(str);
    if((str=strtok(NULL,":"))!=NULL)
	    sec=atoi(str);
	return hour*60*60+min*60+sec;
}




/************************a file which is test**********************/
void CheckProgram(char *channel_name,char *date_name,char* startstr,char* endstr)
{
        int i;
        time_t  start=0,end=0;
		start=StrToSec(startstr);
		end=StrToSec(endstr);
    
		printf("find the file betw from :%d to :%d\n",start,end);
        printf("you find %s: channel, day  is %s:  ,time is  from %d:hour:%d mins to %d:hour:%d mins\n",channel_name,date_name,start/3600,start%3600/60,end/3600,end%3600/60);


	 
		for(i=0;i<CHNUMS;i++)
        {
            //sprintf("xxxxx1:%s\n",share_mems[i].channel_name);
            if(strcmp(share_mems[i].channel_name,channel_name)==0)
            {
                int j;
                printf("find the channel:%s \n",channel_name);

                for(j=0;j<3;j++)
                {
                	

                    //printf("xxxxx2:%s\n",share_mems[i].datearray[j].date_name);
                    if(strcmp(share_mems[i].datearray[j].date_name,date_name)==0)
                    {
                        int n=0;
                        printf("find the date file :%s\n",date_name); 
                        for(n=start;n<end;n++)
                        {
                            if(strlen(share_mems[i].datearray[j].index_file[n])!=0)
                                   printf("%s\n",share_mems[i].datearray[j].index_file[n]);
                
                        }
                    }
                }
            }
        }

}



/***********************main func ****************************/
int main()
{
    int running = 1;
    int i;

    int shmid;
	char xx[5];

	strcpy(xx,"1234567");
    shmid = shmget((key_t)1001, CHNUMS*sizeof(Pd), 0666 | IPC_CREAT);
    if(shmid == -1)
    {
       fprintf(stderr, "shmget failed:%s\n",strerror(errno));
       exit(EXIT_FAILURE);
    }
    shared_memory = shmat(shmid, (void*)0, 0);
    if(shared_memory == (void *)-1)
    {
        fprintf(stderr, "shmat failed:%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    share_mems = (Pd *)shared_memory;
    for(i=0;i<28;i++)
    {
        ;//memset(share_mems[i],'\0',sizeof(share_mems[i]));
    }
    //memset(share_mems,0,28*sizeof(Pd));
    printf("Memory attached at %X\n", (int)shared_memory);
    printf("************check***************\n");
    CheckProgram("DD","20130102","9:39:12","11:41:43");

	return 0;
	         

}


