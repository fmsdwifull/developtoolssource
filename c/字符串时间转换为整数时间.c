#include <string.h>
#include <time.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>



time_t StrToSec(char *strtm)
{
	char *str=NULL;
	int  hour=0,min=0,sec=0;
    if((str=strtok(strtm,":"))!=NULL)
	    hour=atoi(str);
	if((str=strtok(NULL,":"))!=NULL)
	    min=atoi(str);
    if((str=strtok(NULL,":"))!=NULL)
	    sec=atoi(str);
	return hour*60*60+min*60+sec;
}


int main(void)
{
	char str[]="23:60:60";
	int time_sec=0;
	time_sec=StrToSec(str);
	printf("now time is :%d\n",time_sec);
	return 0;
}
