#define MaxSize 5
#include<stdio.h>
#include<malloc.h>
struct queue{
    int qu[MaxSize];
    int front;
    int rear;
    int tag; //front==rear时表示队列满或空的标志：tag==1表示满，tag==0表示空
};
struct queue *InitQu()
{   struct queue *q;
    q=(struct queue *)malloc(sizeof(struct queue));//分配空间
    q->front=0;
    q->rear=0;
    q->tag=0;
    return q;
}
//加入队列
int EnQu(struct queue *q,int x)
{
    if(q->rear==q->front && q->tag==1)//表示队列已满
      {
          return 0;
      }
    else
    {
        q->qu[q->rear]=x;
        q->rear=(q->rear+1)%MaxSize; //尾指针向后走一步
        if(q->rear==q->front) //若有元素入队以后出现q->rear==q->front，则表示队列满
            q->tag=1;
        return 1;
    }
}
int DeQu(struct queue *q)
{
    if(q->rear==q->front && q->tag==0)//表示队空
        return 0;
    else
    {
        q->qu[q->front]=0;//将队头元素的值赋值为0
        q->front=(q->front+1)%MaxSize;//头指针向后走一步
        if(q->rear==q->front)//若有元素出队以后出现q->rear==q->front，则表示队列空
            q->tag=0;
         return 1;
}
}
void Display(struct queue *q)
{
    int n,i;//n为队列中元素的个数
    if(q->rear==q->front && q->tag==1)//队列满
        n=MaxSize;
    else
        n=(q->rear-q->front+MaxSize)%MaxSize;
    for(i=0;i<n;i++)
        printf("%4d",q->qu[(q->front+i)%MaxSize]);
    printf("\n");
}
//队列的应用
main()
{
    struct queue *q;
    int c,k,x;
    q=InitQu();
    loop:
        printf("---------(1).入队列请按数字键1.---------------");
        printf("\n---------(2).出队列请按数字键2.---------------");
        printf("\n---------(3).打印队列请按数字键3.-------------");
        printf("\n请选择要进行的操作:");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                {
                    do{
                            printf("请输入入队元素的值:");
                            scanf("%d",&x);
                            EnQu(q,x);
                            printf("\n是否继续入队,是请按数字键1,否则请按其他数字键!");
                            scanf("%d",&k);
                        }while(k==1);
                    goto loop;
                 break;
                 }
        case 2:{
        do{
        DeQu(q);
        printf("\n是否继续出队,是请按数字键1,否则请按其他数字键!");
        scanf("%d",&k);
        }while(k==1);
        goto loop;
        break;
        }
        case 3:{ Display(q);
    goto loop;
    break;
    }
    }
    printf("\n");
}
