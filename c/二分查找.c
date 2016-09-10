#include <stdio.h>
void main()
{
    int high = 9,low = 0,m,k,a[10]={1,2,3,4,5,6,7,8,9,10};//hing和low赋初值
    scanf("%d",&k);
    while (high>=low)//>=
    {
        m=(high+low)/2;
        if(k<a[m])
            high=m-1;
        else if(k>a[m])
            low=m+1;
        else
        {
            printf("yes:%d\n",a[m]);
            return;//这两句地方放错了
        }
    }
        printf("no");
        return;
}
