/*
 ============================================================================
 Name        : test.c
 Author      : liusaiyu
 Version     :
 Copyright   : CopyRight ptopn.com
 Description : Hello World in C, Ansi-style
 Date£º2013-10-17
 ============================================================================
 */


#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include "pure_lock.h"
using namespace pure_baselib;
int sum=0;

void * add1(void * plock)
{   
	int i;
	pure_lock_dolock(((PLOCK_S*)plock));
	for(i=0;i<10;i++)
	{
		sum++;
		printf("the firstr sum %d\n",sum);
		sleep(1);
	}
  	pure_lock_unlock(((PLOCK_S*)plock));
	pthread_exit(NULL);
}
void * add2(void *plock)
{     
	int i;
	pure_lock_dolock(((PLOCK_S*)plock));
	for(i=0;i<10;i++)
	{
		sum++;
		printf("the second sum %d\n",sum);
		sleep(1);
	}
  	pure_lock_unlock(((PLOCK_S*)plock));

	pthread_exit(NULL);
	

}


int main(void)
{ 

  PLOCK_S plock;
  pthread_t ptid1,ptid2;

  pure_lock_init(&plock,0);
  
  pthread_create(&ptid1,NULL,add1,&plock);
  pthread_create(&ptid2,NULL,add2,&plock);

  pthread_join(ptid1,NULL);
  pthread_join(ptid2,NULL);

  printf("pthread is exit\n");
  pure_lock_destroy(&plock);
  return 0;
} 
