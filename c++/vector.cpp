#include <iostream>   
#include <vector>//����vector   
using namespace std;//ָ�������ռ�   
  
int main()  
{  
    cout<<"----------vector test-----------"<<endl;  
    
    //����һ��vector   
    //vector <int> vect;  
    //vector <int> vect1(12);//12��int����Ԫ�أ�ÿ��Ԫ�صĳ�ʼֵ��Ϊ0   
    //vector <int> vect2(12,9);//12��int������ֵ��Ϊ9   
      
  
    //ʹ�������ʼ��vector   
    int a[]={0,1,2,3,4,5,6,7,8,9,0};  
    //vector <��������> <������> (<��ʼ��ַ>,<������ַ����һ����ַ> )��ִ�й�vt��Ԫ��Ϊ1,2,3   
    vector <int> vt(a+1,a+4);  
    //��β��ѹ��3��ֵ   
    vt.push_back(1);  
    vt.push_back(2);  
    vt.push_back(3);  
  
    //���������iterator   
    vector <int>::iterator iter=vt.begin();//��ʼ��ַ   
    vector <int>::iterator iter_end=vt.end();//������ַ,������ַ����ָ������   
    //����vt   
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
    //����һ��Ԫ��   
    vt.pop_back();  
      
    //�����������»����ʼ�ͽ�β��ַ   
    iter=vt.begin();  
    iter_end=vt.end();
	
    cout<<"----------executed pop_back------"<<endl;  

	for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
  
    //����Ԫ��   
    cout<<"----------insert into------------"<<endl;  
    //�����ʽ��vector.insert(<��ʼ��ַ>,<���������>,<Ԫ��ֵ>);������������Ϊ1����ڶ����������Ա�ʡ��   
    vt.insert(vt.begin()+1,3,9);  
    iter=vt.begin();  
    iter_end=vt.end();  
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
      
    //ɾ��Ԫ��   
    cout<<"----------erase-------------------"<<endl;  
    //ɾ����ʽ1Ϊ��vector.erase(<ɾ��Ԫ�صĵ�ַ>);   
    //ɾ����ʽ2Ϊ��vector.erase(<ɾ��Ԫ�ص���ʼ��ַ>��<��ֹ��ַ>);   
    iter=vt.begin();  
    iter_end=vt.end();  
    vt.erase(iter+1,iter_end);//ɾ���ڶ��������һ����Ԫ��   
    iter_end=vt.end();  
    for(;iter!=iter_end;iter++)  
    {  
        cout<<*iter<<endl;  
    }  
    return 1;  
}  
