/*****************************************************
*指定结构体的地址和长度，则可以完成内存复制
******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


#define MAXSIZE 1000


typedef struct 
{
    int a;
    int b;
    char c[10];
}bao;


int main()
{
    bao *A=NULL;
    char *B=NULL;

    if((A=(bao *)malloc(sizeof(bao)))==NULL)
    {
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }else{
        memset(A,0,sizeof(bao));
    }

    if((B=(char *)malloc(sizeof(bao)))==NULL)
    {
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }else{
        memset(B,0,sizeof(bao));
    }

    A->a=10;
    A->b=20;
    strcpy(A->c,"CHINA");

    memcpy(B,(char*)A,sizeof(bao));
    


    printf("11:%d\n",*B);
    printf("22:%d\n",*(B+4));
    
    printf("33:%s\n",B+8);
    

    
    printf("%s,%d\n",A->c,sizeof(bao));
   
    printf("0:%x\n",A);
    
    printf("1:%x\n",&(A->a));
   
    printf("2:%x\n",&(A->b));

    printf("a:%d\n",*A);
    
    printf("b:%d\n",*((char*)A+4));
    printf("b:%x\n",A+1);
    
    printf("%x\n",A+1);

    return 0;
}
