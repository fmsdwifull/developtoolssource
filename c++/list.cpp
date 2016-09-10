#include <iostream>   
#include <list>   

using namespace std;  
  
int main()  
{  
    list<int> c1;  
    c1.push_back(1);//从尾部push数据（结点）到list中    
    c1.push_back(2);   
    c1.push_back(3);  
    c1.push_back(4);  
      
    c1.push_front(0);//从头部push数据（结点）到list中    
      
    c1.pop_back();//从尾部pop数据（结点）出去   
    
    int& i = c1.back();//获取list中尾部数据（结点） 
    
    const int& ii = c1.front();//获取list中头部 数据（结点）   
      
      
    cout << "The last integer of c1 is " << i << endl;  
    cout << "The front interger of c1 is " << ii << endl;  
      
    cout << "for each" << endl;  
    //循环遍历数据举例   
    list<int>::iterator it; //定义遍历指示器(类似于int i=0)    
    
    for(it = c1.begin(); it!= c1.end() ;it++)  
    {  
        cout << *it << endl;  
    }  
    //system("pause");  
	return 0;
}  
