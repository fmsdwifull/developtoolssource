#include <stdio.h>
void main()
{
    int high = 9,low = 0,m,k,a[10]={1,2,3,4,5,6,7,8,9,10};//hing��low����ֵ
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
            return;//������ط��Ŵ���
        }
    }
        printf("no");
        return;
}
