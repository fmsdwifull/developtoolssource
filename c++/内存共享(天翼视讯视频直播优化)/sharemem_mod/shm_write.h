#ifndef SHMWTITE_H
#define SHMWTITE_H

#define ROWNUM 23*3600 //in case of max 0f ts file
#define FILLLENGTH 24
#define CHNUMS 30



typedef struct elem{
	int sec;
	char filename[50]; 
}Elem;

typedef struct rq{
    char date_name[30];  //��������
    char index_file[ROWNUM][FILLLENGTH]; //ROWNUM��ʾ��Щ�ļ�����ô�࣬FILLLENGTH��ʾ�ļ�������ô��
}Rq;

typedef struct pd{
    char channel_name[20];//Ƶ����
    Rq datearray[3]; //���ڽṹ�����涨��
}Pd;

typedef struct{
    int  have_data;
    char channel_text[30];
    char filedate_text[30];
}_tx;

typedef struct{
	int secs;
	char name[50];
}_find3f;


#endif
