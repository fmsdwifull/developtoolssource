#include <stdio.h>
#include <pthread.h>
#define BUFFER_SIZE 16 // 缓冲区数量

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

    /* 创建生产者和消费者线程*/
    pthread_create(&th_a, NULL, producer, 0);
    pthread_create(&th_b, NULL, consumer, 0);
    /* 等待两个线程结束*/
    pthread_join(th_a, &retval);
    pthread_join(th_b, &retval);
    return 0;
}