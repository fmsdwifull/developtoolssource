#include <iostream>   
#include <vector>//包含vector   
using namespace std;//指定命名空间   
  
int main()  
{  
    cout<<"----------vector test-----------"<<endl;  
    
    //定义一个vector   
    //vector <int> vect;  
    //vector <int> vect1(12);//12个int类型元素，每个元素的初始值均为0   
    //vector <int> vect2(12,9);//12个int，初试值均为9   
      
  
    //使用数组初始化vector   
    int a[]={0,1,2,3,4,5,6,7,8,9,0};  
    //vector <数据类型> <容器名> (<开始地址>,<结束地址的下一个地址> )。执行过vt中元素为1,2,3   
    vector <int> vt(a+1,a+4);  
    //在尾部压入3个值   
    vt.push_back(1);  
    vt.push_back(2);  
    vt.push_back(3);  
  
    //定义迭代器iterator   
    vector <int>::iterator iter=vt.begin();//起始地址   
    vector <int>::iterator iter_end=vt.end();//结束地址,两个地址都是指针类型   
    //遍历vt   
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
    //弹出一个元素   
    vt.pop_back();  
      
    //以下两行重新获得起始和结尾地址   
    iter=vt.begin();  
    iter_end=vt.end();
	
    cout<<"----------executed pop_back------"<<endl;  

	for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
  
    //插入元素   
    cout<<"----------insert into------------"<<endl;  
    //插入格式：vector.insert(<起始地址>,<插入的数量>,<元素值>);如果插入的数量为1，则第二个参数可以被省略   
    vt.insert(vt.begin()+1,3,9);  
    iter=vt.begin();  
    iter_end=vt.end();  
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
      
    //删除元素   
    cout<<"----------erase-------------------"<<endl;  
    //删除格式1为：vector.erase(<删除元素的地址>);   
    //删除格式2为：vector.erase(<删除元素的起始地址>，<终止地址>);   
    iter=vt.begin();  
    iter_end=vt.end();  
    vt.erase(iter+1,iter_end);//删除第二个到最后一个的元素   
    iter_end=vt.end();  
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
    return 1;  
}  
