#include <stdio.h>
#include <pthread.h>
#define BUFFER_SIZE 16 // ����������

void *producer(void *data)
{
	while(1)
	{
		sleep(1);
	}
}

void *consumer(void *data)
{
	while(1)
	{
		sleep(1);
	}
}

int main(void)
{
    pthread_t th_a, th_b;

    /* ���������ߺ��������߳�*/
    pthread_create(&th_a, NULL, producer, 0);
    pthread_create(&th_b, NULL, consumer, 0);
    /* �ȴ������߳̽���*/
    pthread_join(th_a, &retval);
    pthread_join(th_b, &retval);
    return 0;
}