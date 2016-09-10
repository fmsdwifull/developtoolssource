#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>


#define __USE_GNU
#include<sched.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>

#define THREAD_MAX_NUM 100  //1��CPU�ڵ���������

int num=0;  //cpu�к���

void* threadFun(void* arg)  //arg  �����̱߳�ţ��Լ����壩
{
         cpu_set_t mask;  //CPU�˵ļ���
         cpu_set_t get;   //��ȡ�ڼ����е�CPU
         int *a = (int *)arg; 
         printf("the a is:%d\n",*a);  //��ʾ�ǵڼ����߳�
         CPU_ZERO(&mask);    //�ÿ�
         CPU_SET(*a,&mask);   //�����׺���ֵ
         
         if (sched_setaffinity(0, sizeof(mask), &mask) == -1)//�����߳�CPU�׺���
         {
                   printf("warning: could not set CPU affinity, continuing...\n");
         }
         while (1)
         {
                   CPU_ZERO(&get);
                   if (sched_getaffinity(0, sizeof(get), &get) == -1)//��ȡ�߳�CPU�׺���
                   {
                            printf("warning: cound not get thread affinity, continuing...\n");
                   }
                   int i;
                   for (i = 0; i < num; i++)
                   {
                            if (CPU_ISSET(i, &get))//�ж��߳����ĸ�CPU���׺���
                            {
                                     printf("this thread %d is running processor : %d\n", i,i);
                            }
                   }
				   sleep(1);
         }

         return NULL;

}

 

int main(int argc, char* argv[])
{
         num = sysconf(_SC_NPROCESSORS_CONF);  //��ȡ����
         pthread_t thread[THREAD_MAX_NUM];
         printf("system has %i processor(s). \n", num);
         int tid[THREAD_MAX_NUM];
         int i;
         for(i=0;i<num;i++)
         {
                   tid[i] = i;  //ÿ���̱߳����и�tid[i]
                   pthread_create(&thread[0],NULL,threadFun,(void*)&tid[i]);
         }
         for(i=0; i< num; i++)
         {
                   pthread_join(thread[i],NULL);//�ȴ����е��߳̽������߳�Ϊ��ѭ������CTRL+C����
         }
         return 0;
}

