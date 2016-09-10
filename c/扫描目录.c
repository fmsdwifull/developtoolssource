#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
void printdir(char *dir,int depth)
{
    int i;
    int count=0;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    static  char pindao[100][20];
    if((dp=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory:%s\n",dir);
        return;
    }

    chdir(dir);
    while((entry=readdir(dp))!=NULL)
    {
        //printf("%s\n",entry->d_name);
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
	    if((strcmp(entry->d_name,".")!=0)&&(strcmp(entry->d_name,"..")!=0))
            {
            	//printf("%s\n",entry->d_name);	
		strcpy(pindao[count],entry->d_name);
		count++;
            }
            //if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
            //continue;
            //printf("%*s%s/\n",depth,"",entry->d_name);
            //printdir(entry->d_name,depth+4);
        }
        //chdir("..")i;
    }
    for(i=0;i<count;i++)
	printf("%s\n",pindao[i]);
    printf("%s\n",pindao[2]);
    printf("count:%d\n",count);
    closedir(dp);
}
int main()
{
  printdir("./",0);
  return 0;
}
