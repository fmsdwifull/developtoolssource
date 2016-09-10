#include <iostream>   
#include <stdlib.h>   
#include <time.h>   
using namespace std;  
#define size 10   
struct temp  
{  
    int number;  
    int index;   
};  
int main()   
{  
    int i = 0;  
    int s[size];  
    //通过随机数得到数组的初始值   
    srand(time(NULL));  
    struct temp tmp[size];   
    for (i=0; i<size; i++)  
    {  
        s[i] = rand() % 100;   
        tmp[i].number = s[i];  
        tmp[i].index = i;  
    }  
    cout << "enter arrays is ：" << endl;  
    for (i=0; i<size; i++)   
        cout << s[i] << endl;   
    for (int j=0; j<size;j++)   
    {  
        for (int i=size-2; i>=j; i--)   
            if (s[i] > s[i+1])   
            {  
                int t = s[i];   
                s[i] = s[i+1];   
                s[i+1] = t;  
                  
                temp tt;  
                tt.index = tmp[i].index;  
                tmp[i].index = tmp[i+1].index;  
                tmp[i+1].index = tt.index;  
            }   
    }  
    cout << endl << "the after array is：" << endl;  
    for (i=0;i < size;i++)   
        cout << s[i] << endl;  
    cout << "the after array index is：" << endl;  
    for (i=0; i<size; i++)   
        cout << tmp[i].index << endl;   
}   
