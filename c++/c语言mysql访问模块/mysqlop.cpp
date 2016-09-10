#include "mysqlop.h"
#include <string.h>

//msg struct 
#ifndef  _MSG_S_
#define  _MSG_S_
typedef struct	
{
	long mtype;
	unsigned char buffer[1024*8];

}msgtype_s;

#endif

int vec_num;//
int num;//


mysqlop::mysqlop()
{
	 pthread_mutex_init(&lock,NULL);
	 conn_db=mysql_init(NULL);
	 if(!conn_db)
	 {
		 fprintf(stderr, "mysql_init_failed/n");
	 }
	 
	 conn_db = mysql_real_connect(conn_db,"localhost","root","123456","test",0,NULL,0);
	 if( conn_db ){
		 printf("Connection success\n");
	 }else{
		printf("Error connecting to database: %s\n", mysql_error(conn_db));
	 }	 

}
mysqlop::~mysqlop()
{
	mysql_close(conn_db);
}


//void mysqlop::sqlexec(char *sqlstr)
bool mysqlop::sqlexec(char *sqlstr,int type,unsigned char *result)
{
	pthread_mutex_lock(&lock);
	unsigned char buf[1024*8];
	switch (type)
	{
		case 0:
			exec_res(sqlstr);
			break;	
		case 1:
			query_res(sqlstr,result);
			break;
		case 2:
			query_num(sqlstr);
			break;
	}
	pthread_mutex_unlock(&lock);	
	return true;
}


void mysqlop::exec_res(char *sqlstr)
{
	int ok;
	ok=mysql_query(conn_db,sqlstr);
	if(ok)
	{
		printf("Error making query:%s\n", mysql_error(conn_db));
		exit(-1);
	}
	else printf("Query made... \n");
}

void mysqlop::query_res(char *sqlstr,unsigned char *result)
{
	vec_num=0;
	int ok;
	St_Log_RE *st=new St_Log_RE;

	ok=mysql_query(conn_db,sqlstr);
	if(ok)
	{
		printf("Error making query:%s\n", mysql_error(conn_db));
		exit(-1);
	}
	else printf("Query made... \n");

	res=mysql_use_result(conn_db);
	
	unsigned int num_fields;
	unsigned int i;

	num_fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)))
	{
	   unsigned long *lengths;
	   lengths = mysql_fetch_lengths(res);
	   for(i = 0; i < num_fields; i++)
	   {
			st->type_r=HLS_VOD;//×¢ÒâÕâ¸ö			
			st->iWorkID_r=atoi(row[0]);
			st->iUploadNumber_r=atoi(row[2]);
			st->iSequence_r=atoi(row[3]);
			st->spec_r=atoi(row[4]);
			strcpy(st->szLogFilePath_r,row[5]);
	  		printf("*************************:%s\n",st->st->szLogFilePath_r);
	   }	   
	   memcpy(result+vec_num*sizeof(St_Log_RE),(unsigned  char *)st,sizeof(St_Log_RE));
	   memset(st,0,sizeof(St_Log_RE));
	   vec_num++;
	}
	mysql_free_result(res);
	delete st;
}

int mysqlop::query_num(char *sqlstr)
{
	vec_num=0;
	int ok;
	ok=mysql_query(conn_db,sqlstr);
	if(ok)
	{
		printf("Error making query:%s\n", mysql_error(conn_db));
		exit(-1);
	}
	else printf("Query made... \n");

	res=mysql_use_result(conn_db);
	
	unsigned int num_fields;
	unsigned int i;

	num_fields = mysql_num_fields(res);

	num=0;
	while ((row = mysql_fetch_row(res)))
	{
		num++;
	}
	mysql_free_result(res);
	printf("the num is :%d\n",num); 
}

