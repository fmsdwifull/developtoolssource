// fang.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "stdio.h"


#define N 1

int main(void)
{
	int arr[2*N + 1][2*N + 1] = {0};
	int i,j;
	//for(int k = 2*N+1;k > 0;k--)
	for(int k = 0;k < 2*N+1;k++)
	{
		for(i = 0;i < 2*N+1;i++)
		{
			for(j = 0;j < 2*N+1;j++)
			{
				//printf("xx:%d\n",i-j);
				if((i + j ==4*N+1-k )||(i + j ==k-1 )||(i - j ==k-2*N-1 )||(i - j ==2*N+1-k ))
				{
					//arr[i][j] = 2*N +1 - (k-1);
					arr[i][j] = N  - (k-1);
				}
				//else
				//{
				//	continue;
				//}
			}
		}
	}
#if 0
	for(int k = 0;k <= N;k++)
	{
		for(i = 0;i < 2*N+1;i++)
		{
			for(j = 0;j < 2*N+1;j++)
			{
				if((i == N-k)||(i ==N+k)||(j == N-k)||(j == N+k))
				{
					arr[i][j] = N-k+1;
				}
				//else
				//{
				//	continue;
				//}
			}
		}
	}
#endif
	for(i = 0;i < 2*N+1 ;i++)
	{
		for(j = 0;j <2*N+1;j++)
		{
			printf("%5d",arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

