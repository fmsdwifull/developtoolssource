#include <stdio.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>







#ifndef ENUM_H
#define ENUM_H
typedef enum 
{
	HLS_VOD=1,
	HLS_LIVE,
	HTTP_VOD,
	RTSP_LIVE,
	RTSP_VOD,
	RTSP_TIMESHIFT,
	LOG_NULL,
}MediaSvr_Type;
#endif



typedef struct 
{
	MediaSvr_Type type_r;
	int iWorkID_r;//key in db
	int iUploadNumber_r;
	int iSequence_r;
	int spec_r;
	char szLogFilePath_r[128];
}St_Log_RE;




class  mysqlop
{
	public:
		mysqlop();
		~mysqlop();
	    bool sqlexec(char *sqlstr,int type,unsigned char *result);
		
		void exec_res(char *sqlstr);
		void query_res(char *sqlstr,unsigned char *result);		
		int query_num(char *sqlstr);
		
	private:
		MYSQL *conn_db;
		MYSQL_RES *res;
		MYSQL_ROW row;
		pthread_mutex_t lock;

};

