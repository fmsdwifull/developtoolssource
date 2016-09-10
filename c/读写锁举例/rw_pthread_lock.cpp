/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename��rw_pthread_lock.cpp
* Description��
***************************************************************/
/**************************************************************
* Version��1.0.0
* Original_Author��liusaiyu
* Date��2013-10-17
***************************************************************/
/*********************************
*�ڶ�д�������ڼ�Ҳ����ռʧЧ�ġ�
*�����д����ǰû�ж��ߣ�Ҳû��д�ߣ���ôд�߿������̻�ö�д�����������������������ֱ��û���κ�д�߻���ߡ�
*�����д��û��д�ߣ���ô���߿���������øö�д����������߱������������ֱ��д���ͷŸö�д����
***************************/

#include "pure_rwlock.h"
using namespace pure_baselib;



int num=0;


void * write1(void *prwlock)
{
   int i=0;
   
   pure_rwlock_wrlock((PRWLOCK_S *)prwlock);

   for(i=0;i<10;i++)
   {
   		printf("write1:my_file->num:%d,process=%d,thread num:%d\n",num++,getpid(),pthread_self());
		sleep(1);
   }
   pure_rwlock_unlock((PRWLOCK_S *)prwlock);

   return((void *)1);
}


void *write2(void *prwlock)
{
	int i=0;

	pure_rwlock_wrlock((PRWLOCK_S *)prwlock);

	for(i=0;i<10;i++)
	{
		printf("write2:my_file->num:%d,process=%d,thread num:%d\n",num++,getpid(),pthread_self());
		sleep(1);
	}
	sleep(3);
	pure_rwlock_unlock((PRWLOCK_S *)prwlock);


	return((void *)2);
}


void *read1(void *prwlock)
{
	int i=0;

	printf("enter read:\n");
    pure_rwlock_rdlock((PRWLOCK_S *)prwlock);//��ȡ��д��

	for(i=0;i<10;i++)
	{
		printf("read1111111:my_file->lock_num:%d,process=%d,thread num:%d\n",num,getpid(),pthread_self());
		sleep(1);
	}
	pure_rwlock_unlock((PRWLOCK_S *)prwlock);
	printf("after read:\n");

	return((void *)3);
}
void *read2(void *prwlock)
{
	int i=0;

	printf("enter read:\n");
    pure_rwlock_rdlock((PRWLOCK_S *)prwlock);//��ȡ��д��
	for(i=0;i<10;i++)
	{
		printf("read22222222:my_file->lock_num:%d,process=%d,thread num:%d\n",num,getpid(),pthread_self());
		sleep(1);
	}
	pure_rwlock_unlock((PRWLOCK_S *)prwlock);
	printf("after read:\n");

	return((void *)4);
}



int main(void)
{
	pthread_t th1,th2,th3,th4;
	PRWLOCK_S prwlock;
    int ret;

	pure_rwlock_init(&prwlock);//��ʼ����д��


	ret=pthread_create(&th1,NULL,write1,&prwlock);
	if( ret != 0 )
	{
		perror("pthread1 error");
		return 0;
	}
	usleep(1000);
	ret=pthread_create(&th2,NULL,write2,&prwlock);
	if( ret != 0 )
	{
		perror("pthread2 error");
		return 0;
	}
	usleep(1000);
	ret=pthread_create(&th3,NULL,read1,&prwlock);
	if( ret != 0 )
	{
		perror("pthread3 error");
		return 0;
	}	
	ret=pthread_create(&th4,NULL,read2,&prwlock);
	if( ret != 0 )
	{
		perror("pthread3 error");
		return 0;
	}	
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	pthread_join(th4,NULL);
	
	pure_rwlock_destroy(&prwlock);//���ٶ�д��  

	return 1;
}

