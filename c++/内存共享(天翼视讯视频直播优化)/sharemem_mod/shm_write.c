
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/select.h>
#include <regex.h>
#include <time.h>
#include "shm_write.h"


int datefile_num=0;
static int sec_time[50];
_find3f  find3name[50];
time_t std_time=0;
Pd *share_mems;
_tx  *shared_stuff2;
extern _tx  *udp_buf;

Elem *elem=NULL;
static int std_num;
static int std_num;



void *shared_memory1 = (void *)0;
void *shared_memory2 = (void *)0;



//void *shared_memory = (void *)0;

static int channel_num;


time_t GetTimeD(void);
int    STHash(time_t k_time);
int    FindOldFile(char (*datedir)[50],char *channel_dir,int num);
void   SelectkSort(int *a,int n);
void   CheckProgram(char *channel_name,char *date_name,time_t start,time_t end);
void   LoadDateFile(char *dir,int depth);
void   GetMemCommu(void);
void   GetMemStore(void);
void   GetUdpBuf(void);
void   LoadIndexFile(char *matchpath,int n);
void   WriteIndexFile(char *path,int tmp_nums,int tmp ,int i);
void   FindThreeFile(int datefile_num );
void   FreeResource(void);
void   DealDateFunc(void);





/***********************main func*****************************/
int main(void)
{
	//communicate
    GetUdpBuf();
	InitUdpSocket(3333);
	//GetMemCommu();
    //get shared memory which is communicate
    GetMemStore();
    //load date
    LoadDateFile("/home/admin/TV/",0);
	
	DealDateFunc();
    FreeResource();

    return 0;
}


/*******************hash func***************************/
int STHash(time_t k_time)
{
	time_t xx=0;
	xx=k_time-std_time;
	//printf("*******xx*************:%d\n",xx);
	return xx;
}

/******************get the time by day with seconds*******************/
time_t GetTimeD(void)
{
	time_t today_day;
	struct tm *ptr;
	
	time_t lt;
	lt =time(NULL);
	ptr=localtime(&lt);
	return lt;
}


/********************select sort**************************/
#if 1
void SelectkSort(int *a,int n)
{
 int i,j,key,temp;
 for(i=0;i<n-1;i++)
 { 
    key=i;
  	for(j=i+1;j<n-1;j++)
    {
      if(a[key]<a[j])
       key=j;
    }
    if(key!=i)
    {
       temp=a[key];
       a[key]=a[i];
       a[i]=temp; 
    }
  }
 
}

#endif

/**********************fine the oldest file***************************/
int FindOldFile(char (*datedir)[50],char *channel_dir,int num)
{
	int i; 
	time_t sec_time3[3];
	time_t min_time3=0;
	char path2[50];
	struct stat statbuf3;
	
    for(i=0;i<3;i++)
	{
		sec_time3[i]=0;
	}

	for(i=0;i<num;i++)
	{
		sprintf(path2,"/home/admin/TV/%s/%s",channel_dir,datedir[i]);
		if(lstat(path2,&statbuf3)==-1)
		{
			perror("lstat fail");
			return ;
		}
		sec_time3[i]=statbuf3.st_mtime;
	}
	min_time3=sec_time3[0];
	for(i=0;i<num;i++)
	{
        
		if(min_time3>sec_time3[i])
		{
			min_time3=sec_time3[i];			
		}
		
	}	
	//printf("the min time is :%d\n",min_time3);
	for(i=0;i<num;i++)
	{
		if(min_time3==sec_time3[i])	
		{
			return i;
		}
	}
	return -1;
	
}


/********************load all data when program is starting**********************/
void LoadDateFile(char *dir,int depth)
{
    int i,m=0,k,n;
    int count=0;
    DIR *dp;
	DIR *dp2;
	FILE *fp;
	int length;
	char path[100];
	char buf[100];
	char matchpath[60];

	//int cflags=GEG_EXTENDED;
    struct dirent *entry;
    struct dirent *entry2;
    struct stat statbuf;
	struct stat statbuf2;

	if((elem=(Elem*)malloc(sizeof(Elem)))==NULL)
	{
		printf("malloc fail \n");
		exit(-1);
	}
	memset(elem,0,sizeof(Elem));

    if((dp=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory:%s\n",dir);
        return;
    }

    if(chdir(dir)==-1)
	{
        printf("don't chdir the dir :%s\n",dir);
		exit(-1);
	}
    while((entry=readdir(dp))!=NULL)
    {
        //the nums of channels
        int i=0,j;
		datefile_num=0;

    	sleep(1);
        //printf("channel name is :%s\n",entry->d_name);
		lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))//notice
        {
            if((strcmp(entry->d_name,".")!=0)&&(strcmp(entry->d_name,"..")!=0))
            {
    			if((dp2=opendir(entry->d_name))==NULL)
    			{
        			fprintf(stderr,"cannot open directory:%s\n",entry->d_name);
        			exit(-1);
    			}
	     		if(chdir(entry->d_name)==-1)
				{
        			printf("don't chdir the dir :%s\n",entry->d_name);
					exit(-1);
				}                				
                //record channel name
                if(strcpy(share_mems[channel_num].channel_name,entry->d_name)==NULL)
				{
					perror("strcpy error");
					return ;
				}
                printf("channel is :%s\n",share_mems[channel_num].channel_name);

				for(i=0;i<3;i++)
					memset(share_mems[channel_num].datearray[i].date_name,0,sizeof(share_mems[channel_num].datearray[i].date_name));

				for(k=0;k<50;k++)
				{
					sec_time[k]=0;
				}
                while((entry2=readdir(dp2))!=NULL)
				{
				    if(lstat(entry2->d_name,&statbuf2)==-1)
					{
						perror("istst error");
						return ;
					}
					if(S_ISDIR(statbuf2.st_mode))
					{
                        //record datefile name
                         if((strcmp(entry2->d_name,".")!=0)&&(strcmp(entry2->d_name,"..")!=0))
						 {                           
							find3name[datefile_num].secs=statbuf2.st_mtime;
							strcpy(find3name[datefile_num].name,entry2->d_name);
							sec_time[datefile_num]=statbuf2.st_mtime;
							datefile_num++;
				  		 }
					 }
               }			  
				
			   if(datefile_num!=0)
			   {	  
				    SelectkSort(sec_time,sizeof(sec_time)/sizeof(time_t)+1);		 
					//computer the newest file for fope
					FindThreeFile(datefile_num );			  
				}
                if(datefile_num>3)
			   	     datefile_num=3;
						
                for(n=0;n<datefile_num;n++)
				{
					 //printf("start index record :%s\n",matchpath);
					 sprintf(matchpath,"/home/admin/TV/%s/%s%s.index",entry->d_name,entry->d_name,share_mems[channel_num].datearray[n].date_name);							              
                     LoadIndexFile(matchpath,n);
				}

				chdir("..");

                channel_num++;
            }

        }

    }
    closedir(dp);
   
	

}


/************************a file which is test***********************************/
void CheckProgram(char *channel_name,char *date_name,time_t start,time_t end)
{
  		int i;
		printf("find the file betw from :%d to :%d\n",start,end);
		printf("you find %s: channel, day  is %s:  ,time is  from %d:hour:%d mins to %d:hour:%d mins\n",channel_name,date_name,start/3600+1,start%3600/60,end/3600,end%3600/60);
        for(i=0;i<channel_num;i++)
		{
		    printf("xxxxx1:%s\n",share_mems[i].channel_name);
			
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
						    //printf("%d\n",n);
							if(strlen(share_mems[i].datearray[j].index_file[n])!=0)
								   printf("%s\n",share_mems[i].datearray[j].index_file[n]);
				
						}
					}
				}
			}
		}

}




void GetMemStore(void)
{
	//get shared memory which is stored
	int shmid;
	shmid = shmget((key_t)1001, CHNUMS*sizeof(Pd), 0666 | IPC_CREAT);
	printf("shared memeory size is %d m\n",CHNUMS*sizeof(Pd)/1024/1024);
	if(shmid == -1)
	{
   		fprintf(stderr, "shmget failed:%s\n",strerror(errno));
   		exit(EXIT_FAILURE);
	}
	shared_memory1 = shmat(shmid, (void *)0, 0);
	if(shared_memory1 == (void *)-1)
	{
		fprintf(stderr, "shmat failed:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	share_mems = (Pd *)shared_memory1;

	memset(share_mems,0,CHNUMS*sizeof(Pd));
	printf("Memory attached at %X\n", (int)shared_memory1);

}

/****************************************/
void GetMemCommu(void)
{
	int shmid2;
	if((shmid2=shmget((key_t)1002, sizeof(_tx), 0666 | IPC_CREAT)) == -1)
    {
 		fprintf(stderr, "shmget failed\n");
 		exit(EXIT_FAILURE);
    }
    shared_memory2 = shmat(shmid2, (void *)0, 0);
	if(shared_memory2 == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", (int)shared_memory2);
    shared_stuff2 = (_tx *)shared_memory2;

}
/**********************************************************/
void FreeResource(void)
{
    //free shared memory
    if(shmdt(shared_memory2) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if(shmdt(shared_memory1) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
	free(udp_buf);

}
/************************************************************/
void DealDateFunc(void)
{
	int i;
	while(1)
	{	    
			if(udp_buf->have_data==1)
			{
				printf("A datefile was created \n");
				printf("channel is :%s--datefile is :%s  \n",udp_buf->channel_text,udp_buf->filedate_text);
				udp_buf->have_data=0;
				for(i=0;i<channel_num;i++)
				{
					if(strcmp(udp_buf->channel_text,share_mems[i].channel_name)==0)
					{
						//FILE *fp;
						int tmp=0,m=0,j=0,tmp_nums=0;
						char tmp_datefile[3][50];
						char tmp_path[50];
						//char buf[50];
						//Elem *elem=NULL;
	
						printf("find the channel\n");
						//elem=(Elem*)malloc(sizeof(Elem));
	
						for(j=0;j<3;j++)
						{
							printf("date file name is:%s\n",share_mems[i].datearray[j].date_name);
							if(strlen(share_mems[i].datearray[j].date_name)!=0)
								tmp_nums++;
						}
						printf("have %d date file already\n",tmp_nums);
						
						for(j=0;j<tmp_nums;j++)
							if(strcpy(tmp_datefile[j],share_mems[i].datearray[j].date_name)==NULL)
							{
								printf("strcpy error\n");
								return ;
							}
							
						if(tmp_nums>2)
						{
						   if((tmp=FindOldFile(tmp_datefile,share_mems[i].channel_name,tmp_nums))==-1)
						   {
							   printf("there is no date file\n");
							   return;
						   }
						   printf("the oldest is :%s\n",share_mems[i].datearray[tmp].date_name);
						}						
						if(tmp_nums>2)
						{
							if(strcpy(share_mems[i].datearray[tmp].date_name,udp_buf->filedate_text)==NULL)
							{
								perror("strcpy error");
								return ;
							}
						}else{
							printf("lower 3 ,num is :%d\n",tmp_nums);
							if(strcpy(share_mems[i].datearray[tmp_nums].date_name,udp_buf->filedate_text)==NULL)
							{
								perror("strcpy error");
								return ;
							}
							printf("record the date file :%s\n",share_mems[i].datearray[tmp_nums].date_name);
	
	
						}
						sprintf(tmp_path,"/home/admin/TV/%s/%s%s.index",udp_buf->channel_text,udp_buf->channel_text,udp_buf->filedate_text);						  



						printf("wwwwwwwwwwww:%s\n",tmp_path);
                        //write index file
						//printf("******************%s,%s,%d\n",udp_buf->channel_text,udp_buf->filedate_text,udp_buf->have_data);
                        WriteIndexFile(tmp_path,tmp_nums,tmp ,i);

						
					 }
				}
				
			}	
			printf("*\n");

			
		}

}

/*****************get udp buffer*********************/
void GetUdpBuf(void)
{
    
    //get buffer which is used to communicate 
    if((udp_buf=(_tx*)malloc(sizeof(_tx)))==NULL)
    {
        perror("malloc error");
        free(udp_buf);
        exit(EXIT_FAILURE);
    }else{
        memset(udp_buf,0,sizeof(_tx));
    }

}

/*******************************************************/
void FindThreeFile(int datefile_num )
{
	int j;
	for(j=0;j<datefile_num;j++)
	{
		if(sec_time[0]==find3name[j].secs)
	  	{
			strcpy(share_mems[channel_num].datearray[0].date_name,find3name[j].name);
		}
		if(sec_time[1]==find3name[j].secs)
			strcpy(share_mems[channel_num].datearray[1].date_name,find3name[j].name);
		if(sec_time[2]==find3name[j].secs)
			strcpy(share_mems[channel_num].datearray[2].date_name,find3name[j].name);	
	}
	printf("#####################################################\n");
	printf("%s,%s,%s\n",share_mems[channel_num].datearray[0].date_name,share_mems[channel_num].datearray[1].date_name,share_mems[channel_num].datearray[2].date_name);
	printf("datefile_num :%d\n",datefile_num);
	printf("#####################################################\n");


}
/******************************************************/
void LoadIndexFile(char *matchpath,int n)
{
	 FILE *fp;
	 
	 std_num=0;
	 if((fp=fopen(matchpath,"r"))!=NULL)
	 {
		int addr;
		while(1)
		{	
			int addr=0;
									
			memset(elem,0,sizeof(Elem));		
			if(fread(elem,sizeof(Elem),1,fp)!=1)
			{		
				break;
			}
			if((std_num==0)&&(strcmp(elem->filename,"HashTime")==0))
			{
				std_time=elem->sec;
				//printf("#############std time##############:%d\n",std_time);
			}else{
				addr=STHash(elem->sec);
				//printf("***********std time is : %d****%d*********\n",elem->sec,std_time);						
				//printf("#############addr##############:%d\n",addr);
				if(strcpy(share_mems[channel_num].datearray[n].index_file[addr],elem->filename)==NULL)
				{
					perror("strcpy error");
					return;
				}
				//printf("*****file :%s*****\n",share_mems[channel_num].datearray[n].index_file[addr]);
			 }																			
			 
					
		}	
	
									
		fclose(fp);
	}

}


/*************************************************/

void WriteIndexFile(char *tmp_path,int tmp_nums,int tmp ,int i)
{		
    FILE *fp;
	
	std_num=0;
	printf("*******start write ****************:%s\n",tmp_path);
	if((fp=fopen(tmp_path,"r"))!=NULL)
	{
		Elem *elem=NULL;		
		elem=(Elem*)malloc(sizeof(Elem));
		memset(elem,0,sizeof(Elem));
		elem->sec=0;
		while(1)
		{	
	       //printf("buf:%s\n",buf);
		   int addr=0;              
		   memset(elem,0,sizeof(Elem));
		   if(fread(elem,sizeof(Elem),1,fp)!=1)
		   {									
			  break;
		   }	 
		   printf("*****time :%d, file :%s*****\n",elem->sec,elem->filename);						
		   if((std_num==0)&&(strcmp(elem->filename,"HashTime")==0))
		   {
			   std_time=elem->sec;
           }else{
			  addr=STHash(elem->sec);
			  //printf("***********std time is : %d****%d*********\n",elem->sec,std_time);													
			  printf("#############addr##############:%d\n",addr);
              //direct write ,but check the newest 
			  if(tmp_nums<3)
			  {
				  if(strcpy(share_mems[i].datearray[tmp_nums].index_file[addr],elem->filename)==NULL)
				  {
					  perror("strcpy error");
					  return;
				  }
			  }else{
				 if(strcpy(share_mems[i].datearray[tmp].index_file[addr],elem->filename)==NULL)
				 {
					perror("strcpy error");
					return;
				 }
			 }
			}
		    memset(elem,0,sizeof(Elem));
		    std_num++;
										//m++;							
	    } 				  
		free(elem);
	}else{
		printf("fopen error\n");
		exit(EXIT_FAILURE) ;
	}
	fclose(fp);

}

