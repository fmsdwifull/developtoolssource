#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str="��ʼ��string���ַ���";//��ʼ��str
    char ch[]="��ʼ��char���ַ���";//��ʼ��ch[]����
    cout<<str<<endl;
    cout<<ch<<endl;
    //stringʾ��
    cout<<"�����롰������Ӣ�ĵ��ʣ�"<<endl;
    cin>>str;
    if(str=="dog")
    {
        cout<<"����"<<str<<endl;
        cout<<str<<"�ĵ�һ���ַ��ǣ�"<<str[0]<<endl;
    }
    else
        cout<<"�������\n";
    //charʾ��
    cout<<"�����롰����Ӣ�ĵ��ʣ�"<<endl;
    cin>>ch;
    if(ch=="pig")
    {
        cout<<"��"<<ch<<endl;
        cout<<ch<<"�ĵ�һ���ַ��ǣ�"<<ch[0]<<endl;
    }
    else
        cout<<"�������\n";
    return 0;
}