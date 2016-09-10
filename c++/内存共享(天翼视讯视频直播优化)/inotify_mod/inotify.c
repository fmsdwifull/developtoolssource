/**************
the max nums of channel is 100 now 
the max nums of data dir is  50 now
but it could be changed 

**************/




#include <string.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <error.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/select.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "inotify.h"

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )


char pindao[MAX_CHANNEL][20];
char filedat[3][50];
char path[50]="/home/admin/TV/";

int COUNT,count2;
int fd1,fd2;
int isindex=0;
extern int flag;

_hash find_dir[MAX_CHANNEL];
_tx  *shared_stuff; //xx
_tx  *udp_buf; 


void *shared_memory = (void *)0;


time_t GetTimeD(void);
void   SelectkSort(int *a,int n);
void   InotifyChannel(void);
void   FindChannel(char *dir,int depth);
void   GetShMem(void);
void   GetUdpBuf(void);
void   FillUdpBuf(int num,int id,int newid);
void   CreateIndexFile(char *filepath,int j);



void   FreeResource(void);
void   StartInofying(void);



char  *GetTimeS(void);

int    FindNewFile(char (*datedir)[50],char *channel_dir,int num);
int    FindOldFile(char (*datedir)[50],char *channel_dir);
int    LoadDateFile(char *dir,int depth);
int    GetTimeI(void);
int    ComputerNum(char (*datedir)[50]);	



/***********************main func****************************/
int main( int argc, char **argv ) 
{

	//FILE *fp1;
    //int length=0, i = 0,j,j2,m,n,k=0;
    //int fd1,fd2;
    //int wd1,wd2;
    //int shmid;
	int start_time=0;
	int end_time=0;

    //static int isdir=0,ishaspd=0,isindex=0;

    //char *time2;
    //char filepath[50];
    //struct inotify_event  buffer[BUF_LEN];

    //GetShMem();
    GetUdpBuf();

    //create the inotifier for channel dir and date dir
    fd2 = inotify_init();
    fd1 = inotify_init();
    if ( (fd1 < 0)||(fd2<0) )
    {
        perror( "inotify_init" );
    }
    //find channels and record them
    FindChannel("/home/admin/TV/",0);
    printf("The nums of channel is :%d\n",COUNT);

    start_time=GetTimeI();
    printf("start scan time is :%d\n",start_time);
	//load all channel to inotify and load all sub datefile to inotify
    InotifyChannel();
	end_time=GetTimeI();
    printf("scan end time is:%d\n",end_time);
	printf("need  time is is:%d\n",end_time-start_time);
    InitUdpSocket(3333);
	//enter  main step
    StartInofying();
	FreeResource();

	return 0;


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

/********************get  time with string *************************/
char *GetTimeS(void)
{
    static char now_time[20];
        time_t rawtime;
    struct tm* timeinfo;
    if(time(&rawtime)==-1)
        return ;
    if((timeinfo=localtime(&rawtime))==NULL)
        return ;
    strcpy(now_time,asctime(timeinfo));
    return now_time;
}

/********************get  time int data *************************/
int  GetTimeI(void)
{
    //static char now_time[20];
        time_t rawtime;
    //struct tm* timeinfo;
    if(time(&rawtime)==-1)
        return ;
	else
		return rawtime;
    //if((timeinfo=localtime(&rawtime))==NULL)
    //    return ;
    //strcpy(now_time,asctime(timeinfo));
    //return now_time;
}


/******************get the time by day with seconds standadly*******************/

time_t GetTimeD(void)
{
	time_t today_day;
	struct tm *ptr;
	
	time_t lt;
	lt =time(NULL);
	ptr=localtime(&lt);

    //printf("");
	
	//printf("second:%d\n",ptr->tm_sec);
	//printf("minute:%d\n",ptr->tm_min);
	//printf("hour:%d\n",ptr->tm_hour);
	//printf("mday:%d\n",ptr->tm_mday);
	//printf("month:%d\n",ptr->tm_mon+1);
	//printf("year:%d\n",ptr->tm_year+1900);
	return lt-(ptr->tm_hour)*3600-ptr->tm_min*60-ptr->tm_sec;
	//return lt;
}


/************************find the newest date file for inotifying**************************/
int FindNewFile(char (*datedir)[50],char *channel_dir,int num)
{
	int i; 
	time_t sec_time3[3];
	time_t max_time3=0;
	char path2[50];
	struct stat statbuf3;


	if(num==0)
		return -1;
    for(i=0;i<num;i++)
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
		//printf("my time is :%d\n",statbuf3.st_mtime);
		sec_time3[i]=statbuf3.st_mtime;
		//printf("my time is :%d\n",sec_time3[i]);
	}
	//get  the newest file
	max_time3=sec_time3[0];
	for(i=0;i<num;i++)
	{     
		if(max_time3<sec_time3[i])
		{
			max_time3=sec_time3[i];			
		}
		
	}	   
	for(i=0;i<num;i++)
	{
		if(max_time3==sec_time3[i])	
		{
			return i;
		}
	}
	
}

/**************************find the oldest file for insteading****************************/
int FindOldFile(char (*datedir)[50],char *channel_dir)
{
	int i,tmp_num=0; 
	time_t sec_time3[3];
	time_t min_time3=0;
	char path2[50];
	struct stat statbuf3;
	
    for(i=0;i<3;i++)
	{
		sec_time3[i]=0;
	}

	for(i=0;i<3;i++)
	{
		//printf("ssss:%d\n",strlen(datedir[i]));
		if(strlen(datedir[i])!=0)
			tmp_num++;
	}
	
    //printf("xxxxxxxxxxxxxxxx:%d\n",tmp_num);

	for(i=0;i<tmp_num;i++)
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

	for(i=0;i<tmp_num;i++)
	{
        
		if(min_time3>sec_time3[i])
		{
			min_time3=sec_time3[i];			
		}
		
	}	
    
	//printf("the min time is :%d\n",min_time3);
	for(i=0;i<tmp_num;i++)
	{
		if(min_time3==sec_time3[i])	
		{
			return i;
		}
	}
	return -1;
	
}



/********************find date file and find  the newest file*****************/
int LoadDateFile(char *dir,int depth)
{
    int i,j,k;
    //int count2=0;
    int tmp_count=0;
    DIR *dp2;
	static int sec_time[50];
	_find3f  find3name[DATENUM];
	time_t max_time=0;
    struct dirent *entry2;
    struct stat statbuf2;

   
    if((dp2=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory:%s\n",dir);
        return;
    }

	for(k=0;k<DATENUM;k++)
	{
		sec_time[k]=0;
	}
    chdir(dir);
    while((entry2=readdir(dp2))!=NULL)
    {
        lstat(entry2->d_name,&statbuf2);
        if(S_ISDIR(statbuf2.st_mode))//notice
        {
            if((strcmp(entry2->d_name,".")!=0)&&(strcmp(entry2->d_name,"..")!=0))
            {
				//strcpy(filedat[tmp_count],entry2->d_name);

				find3name[tmp_count].secs=statbuf2.st_mtime;
				strcpy(find3name[tmp_count].name,entry2->d_name);
				
			    sec_time[tmp_count]=statbuf2.st_mtime;
				tmp_count++;
            }
        }
		//notice here
		//if(tmp_count>=3)
		//{
		//	printf("********date file over 3,i shall load 3 only**********\n");
		//	break;
		//}
			//tmp_count=0;
    }
    closedir(dp2);
	if(tmp_count==0)
	{
		return -1;
	}else{
		SelectkSort(sec_time,sizeof(sec_time)/sizeof(time_t)+1);
	
		//computer the newest file for fopen

		for(j=0;j<tmp_count;j++)
		{
			if(sec_time[0]==find3name[j].secs)
				strcpy(filedat[0],find3name[j].name);
			if(sec_time[1]==find3name[j].secs)
				strcpy(filedat[1],find3name[j].name);
			if(sec_time[2]==find3name[j].secs)
				strcpy(filedat[2],find3name[j].name);	
		
		}

    	//printf("#####################################################\n");
		//printf("%s,%s,%s\n",filedat[0],filedat[1],filedat[2]);
		//printf("count :%d\n",tmp_count);
    	//printf("#####################################################\n");


	
#if 0
		max_time=sec_time[0];
		for(j=0;j<tmp_count;j++)
		{
			if(sec_time[j]>max_time)
				max_time=sec_time[j];
		}
    	for(j=0;j<tmp_count;j++)
		{
			if(sec_time[j]==max_time)
			{
				return j;
			}
		}
#endif

		return 0;
	}

}



void InotifyChannel(void)
{
	int n=0;
    for(n=0;n<COUNT;n++)
    {
         int i,wd1,newest_id,tmpnum=0;
		 FILE *fp;
		 char index_file[50];

         for(i=0;i<3;i++)
           memset(filedat[i],0,sizeof(filedat[i]));
   
		 strcpy(path,"/home/admin/TV/");
         strcpy(find_dir[n].channel,pindao[n]);
         strcat(path,find_dir[n].channel);

		 //printf("xxxxxxxxxxxxxxxxx:%s\n",path);

		 wd1= inotify_add_watch(fd1, path, IN_CREATE);
         if(wd1<0)
         {
            perror("inotify error");
            exit(-1);
         }
         find_dir[n].wdid=wd1;

		 printf("****************************************************************\n");
		 printf("the channel name is:%s\n",find_dir[n].channel);
		 //scan sub dir 
		 newest_id=LoadDateFile(path,0);//find the newest date file

		 for(i=0;i<3;i++)
		 {	   
		       printf("date file name:%s\n",filedat[i]);
               if(strlen(filedat[i])!=0)
				  	  tmpnum++;
		 }

         printf("have file nums is:%d\n",tmpnum);
		 //inotify the newest date file
		 if(newest_id==-1)
		 {
			  printf("there have no file\n");
		 }else{

			  
		      strcat(path,"/");
		      strcat(path,filedat[newest_id]);
			  printf("the newest file is :%s\n",filedat[newest_id]);

		      if((wd1= inotify_add_watch(fd2, path, IN_CREATE))==-1)
		      {
					perror("inotify faild:");
					exit(-1);
		 	  }
			  printf("the file was inotified:%s\n",path);
			  
              //open the file for writing      
       	      sprintf(index_file,"/home/admin/TV/%s/%s%s.index",find_dir[n].channel,find_dir[n].channel,filedat[newest_id]);
               
              printf("index_file is :%s\n",index_file);
			  if((fp=fopen(index_file,"a+"))==NULL)
		 	  {
				 printf("fopen error\n");
				 return ;
		 	  }


			  printf("the file was open for writing:%s\n",index_file);
			  //record fp to array ,but need check,,,,,,,,,,,,
		      find_dir[n].fp=fp;
		      if(find_dir[n].fp==NULL)
		      {
			     printf("fp error\n");
				 exit(-1);
				 //return 0;
		      }

			  //record the date file to the struct   

		 	  for(i=0;i<tmpnum;i++)
		      {
		          printf("the file which was loaded:%s\n",filedat[i]);
          	      if(strcpy(find_dir[n].hashwd2.datefile2[i],filedat[i])==NULL)
			      {
					 printf("strcpy error\n");
					 return;
			      }
		      }	
			
		      find_dir[n].hashwd2.date_wd=wd1;
		      strcpy(path,"/home/admin/TV/");
		}
    }

}



/***********************find channel and record them************************/
void  FindChannel(char *dir,int depth)
{
    int i;
    int count=0;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory:%s\n",dir);
        return;
    }
    chdir(dir);
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))//notice
        {
            if((strcmp(entry->d_name,".")!=0)&&(strcmp(entry->d_name,"..")!=0))
            {
                strcpy(pindao[COUNT],entry->d_name);
                COUNT++;
            }
        }
    }
    closedir(dp);
}

/*****************get shared memory*********************/
void GetShMem()
{
	 int shmid;
    //get shared memory which is used to communicate 
    if((shmid=shmget((key_t)1002, sizeof(_tx), 0666 | IPC_CREAT)) == -1)
    {
 		fprintf(stderr, "shmget failed\n");
 		exit(EXIT_FAILURE);
    }
    shared_memory = shmat(shmid, (void *)0, 0);
    if(shared_memory == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    //printf("Memory attached at %X\n", (int)shared_memory);
    shared_stuff = (_tx *)shared_memory;

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




/************************free resourc***********************/
void   FreeResource(void)
{
	int i;

	free(udp_buf);
	//free shared memory
	if(shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
    for(i=0;i<COUNT;i++)
    {
       ( void )inotify_rm_watch( fd1,find_dir[i].wdid);

    }
    ( void ) close( fd1 );
    ( void ) close( fd2 );

}

/*******************main proc deal********************************/
void  StartInofying(void)
{
	int wd2;
	int length=0,i = 0,j=0,j2=0,m=0,k=0;
	static int isdir=0,ishaspd=0;
	char filepath[50];
	struct inotify_event  buffer[BUF_LEN];
    while(1)
    {
        fd_set fds1;
        fd_set fds2;
        struct timeval tv;
        int r1=0,r2=0,wd_len=0,num=0,min;
		int xx;
		//time_t day_sec=0;
		//Elem e;

		usleep(50);
		//memset(&e,0,sizeof(Elem));
		//memset(&e,0,sizeof(Elem));
		//e.sec=0;
		
        FD_ZERO (&fds1);
        FD_ZERO (&fds2);
        FD_SET (fd1, &fds1);
        FD_SET (fd2, &fds2);
        printf("*\n");
		
        //Timeout.
        tv.tv_sec = 1;
        tv.tv_usec = 0;

		//r1 is channel ,r2 is date file
        r1 = select (fd1 + 1, &fds1, NULL, NULL, &tv);
        r2 = select (fd2 + 1, &fds2, NULL, NULL, &tv);
		
        //这里为什么会这样，fd2 变化的时候，为什么fd1也会变化
        if((r1==1)&&(r2==1))
           r1=0;
        //a file was created ,it's need to read
        //printf("ri:%d---r2:%d\n",r1,r2);
        if((r1==1)&&(isindex==1))
        {
            r1=0;
            isindex=0;
            read( fd1, buffer, BUF_LEN );
            memset(buffer,0,sizeof(buffer));
        }
        switch(r1)
        {
            case -1:
                break;
                perror("error\n");
            case  0:
                break;
            default:
				//indicate there is a dir
                isdir=1;
                num=0;
                length = read( fd1, buffer, BUF_LEN );
                //printf("OK r1:%d r2:%d\n",r1,r2);
        }
        if ( length < 0 ) 
        {
            perror( "read" );
        } 

        if(isdir)
        {
          int tmp2;
          while ( i < length )
          {
            struct inotify_event *event = ( struct inotify_event * ) &buffer[i];
            isdir=0;
            if (event->len)
            {   
                if (event->mask&IN_CREATE)
                {
                    if ( event->mask&IN_ISDIR )
                    {
                       for(j=0;j<COUNT;j++)
                       {
                          //compare wdid for finding the name of channel
                          if(event->wd==find_dir[j].wdid)
                          {
       						 //FILE *fp2;                   
                             int i1,tmp_wd,tmp,tmp2,w=0,r=0,date_num=0;
							 
                             //enter the date dir and inotify
                             strcpy(path,"/home/admin/TV/");
                             strcat(path,find_dir[j].channel);
                             strcat(path,"/");
                             strcat(path,event->name);

							 //free the last wd which is inotifying
                             tmp_wd=find_dir[j].hashwd2.date_wd;
							 ( void )inotify_rm_watch(fd2, tmp_wd );
                           
							 //add the date dir to watch
                             if((wd2= inotify_add_watch(fd2,path,IN_CREATE))==-1)
							 {
								perror("fd2 inotify fail\n");
								return ;
							 }
							 find_dir[j].hashwd2.date_wd=wd2;


							printf("a file was create under :%s\n ",find_dir[j].channel);								 
                            //find how many date file under the channel
                            
							date_num=ComputerNum(find_dir[j].hashwd2.datefile2); 
			             				
						    printf("********there already have %d datefile***** \n",date_num);
							for(r=0;r<date_num;r++)
							{
							    printf("the date file is:%s\n",find_dir[j].hashwd2.datefile2[r]);
							}
            
                            
							//find the newest file for comunicating with other proc
							if(date_num!=0)
							{
								if((tmp2=FindNewFile(find_dir[j].hashwd2.datefile2,find_dir[j].channel,date_num))==-1)
								{
									   printf("have 0 file\n");
								 
								}
								printf("the newest file is :%s\n",find_dir[j].hashwd2.datefile2[tmp2]);
                            	strcpy(path,"/home/admin/TV/");  
       							FillUdpBuf(date_num,j,tmp2);
								
								//delete a file fp when new date file was created,and open the newfile 
								if(fclose(find_dir[j].fp)==0)
							    {
								    printf("a file describe  which is in already was delete success  \n");
							    }else{
							    	perror("close fp error ");
						     	}
							}	

							
						    if(date_num>2)
							{
								//find the oldest for instead of it
							 	if((tmp=FindOldFile(find_dir[j].hashwd2.datefile2,find_dir[j].channel))==-1)
							 	{
									 printf("there is no file\n");
							 	}	
								printf("the oldest file is :%s\n",find_dir[j].hashwd2.datefile2[tmp]);

							}
					        if((date_num==0)||(date_num==1)||(date_num==2))
							{	
							      
							      if(strcpy(find_dir[j].hashwd2.datefile2[date_num],event->name)==NULL)
							      {
								      printf("strcpy error\n");
								      return ;
							      }
								  printf("***the file was into find_dir[j].hashwd2.datefile2[%d]  **\n",date_num);
								   
							}else{
							      printf("the file was instead of :%s\n",find_dir[j].hashwd2.datefile2[tmp]);
							 	  if(strcpy(find_dir[j].hashwd2.datefile2[tmp],event->name)==NULL)
							 	  {
								  	  printf("strcpy error\n");
								      return ;
							       }
								   
							}
			
							 //create a file
							 sprintf(filepath,"/home/admin/TV/%s/%s%s.index",find_dir[j].channel,find_dir[j].channel,event->name);
							 CreateIndexFile(filepath,j);
#if 0
							 printf("the file path was  opened:%s\n",filepath);
							 if((fp2=fopen(filepath,"a+"))==NULL)
							 {
								  printf("fopen fail \n");
								  exit(-1);
							  }else{
								  isindex=1;
								  find_dir[j].fp=fp2;
							  }
							  
							  printf("********write std  time by secs*************\n");
							  day_sec=GetTimeD();
							  e.sec=day_sec;
							  
							  if(strcpy(e.filename,"HashTime")==NULL)
							  {
								  printf("strcpy error\n");
								  return ;
							  }
							  if((xx=fwrite(&e,sizeof(Elem),1,find_dir[j].fp))==0)
							  {
								   printf("fwrite error\n");
								   exit(-1);
							  }
							  fflush(find_dir[j].fp);

#endif
							  
                              date_num=0;

                          }
                       }                  
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
        memset(buffer,0,sizeof(buffer));
        length=0;
        i=0;
    }else{
        //there ts file was created
		switch(r2)
        {
            case -1:
                perror("error\n");
                break;
            case  0:
                break;
            default:
                length = read( fd2, buffer, BUF_LEN );
                break;

        }
        while(k < length )
        {
                int i3;
                char channelname[20];
                struct inotify_event *event = ( struct inotify_event * ) &buffer[k]; //please notice

                //printf("len:%d,%s \n",event->len,event->name);
                if (event->len)
                {
                    if (event->mask&IN_CREATE)
                    {
                        int m,p;
                        for(m=0;m<COUNT;m++)
                        {
                              if(find_dir[m].hashwd2.date_wd==event->wd)
							  {
							        int tmp_time=0,tmp_count=0;
									char *str_time;
									time_t int_time;
									time_t today_day;
									Elem e;

									memset(&e,0,sizeof(Elem));
									e.sec=0;

                                   
								    tmp_count=ComputerNum(find_dir[m].hashwd2.datefile2);    
                                    
									
									tmp_time=FindNewFile(find_dir[m].hashwd2.datefile2,find_dir[m].channel,tmp_count);
									sprintf(channelname,"%s",find_dir[m].channel);
								    printf("channel is :%s,fatrher dir is :%s,filename is :%s\n",find_dir[m].channel,find_dir[m].hashwd2.datefile2[tmp_time],event->name);	

									int_time=GetTimeI();
									//str_time=GetTimeS();
									//printf("time set is :%d\n",int_time);
									
                                    e.sec=int_time;
									if(strcpy(e.filename,event->name)==NULL)
									{
										printf("strcpy error\n");
										return ;
									}
									if(fwrite(&e,sizeof(Elem),1,find_dir[m].fp)==0)
									//if((xx=fwrite(event->name,strlen(event->name),1,find_dir[m].fp))==0)
									{
										printf("fwrite error\n");
										exit(-1);
									}
									//if((xx=fwrite("\n",strlen("\n"),1,find_dir[m].fp))==0)
									//{
									//	printf("fwrite error\n");
									//	exit(-1);
									//}
									fflush(find_dir[m].fp);


							  }
						}   
                    }
                }
                k += EVENT_SIZE + event->len;
        }
            memset(buffer,0,sizeof(buffer));
            length=0;
            k=0;
      }
    }

}

void FillUdpBuf(int num,int id,int newid)
{
	 //tell udp pthread to write
	if(udp_buf->have_data==0)
	{
		
		 //don't communicate with shared memory if there isn't date file
		 printf("have %d file already \n",num);
		 //printf("the newest file is :%s\n",find_dir[id].hashwd2.datefile2[newid]);
		 //show have date file ,on the other hand ,show  have index file
		 //if(num!=0)
		 {	
		    udp_buf->have_data=1;
			//shared_stuff->have_data=1;
			if(strcpy(udp_buf->channel_text,find_dir[id].channel)==NULL)
			{
				 printf("strcpy fail\n");
				 exit(-1);
			}			
			//tell other proc the name of channel and datefile name
			if(strcpy(udp_buf->filedate_text,find_dir[id].hashwd2.datefile2[newid])==NULL)
			{
				printf("strcpy fail\n");
				exit(EXIT_FAILURE);
			}
			printf("tell shared process to write the file :%s to memory\n",find_dir[id].hashwd2.datefile2[newid]);
		  
	 }
	 
  }	

}


int ComputerNum(char (*datedir)[50])	
{
	int i=0,count=0;
	for(i;i<3;i++)
	{
		//printf("ccccccccccc:%s\n",find_dir[j].hashwd2.datefile2[r]);
		if(strlen(datedir[i])!=0)
		{
			count++;
		}	
	}
	return count;
}


void CreateIndexFile(char *filepath,int j)
{
	FILE *fp2;
	time_t day_sec=0;
    Elem e;
    memset(&e,0,sizeof(Elem));
	printf("the file path was  opened:%s\n",filepath);
	if((fp2=fopen(filepath,"a+"))==NULL)
	{
		 printf("fopen fail \n");
		 exit(-1);
	 }else{
		 isindex=1;
		 find_dir[j].fp=fp2;
	 }
	 
	 //printf("********write std time by secs*************\n");
	 day_sec=GetTimeD();
	 e.sec=day_sec;
	 
	 if(strcpy(e.filename,"HashTime")==NULL)
	 {
		 printf("strcpy error\n");
		 return ;
	 }
	 if(fwrite(&e,sizeof(Elem),1,find_dir[j].fp)==0)
	 {
		  printf("fwrite error\n");
		  exit(-1);
	 }
	 fflush(find_dir[j].fp);

}
