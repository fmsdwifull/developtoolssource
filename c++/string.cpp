#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str="初始化string型字符串";//初始化str
    char ch[]="初始化char型字符串";//初始化ch[]数组
    cout<<str<<endl;
    cout<<ch<<endl;
    //string示例
    cout<<"请输入“狗”的英文单词："<<endl;
    cin>>str;
    if(str=="dog")
    {
        cout<<"狗："<<str<<endl;
        cout<<str<<"的第一个字符是："<<str[0]<<endl;
    }
    else
        cout<<"输入错误\n";
    //char示例
    cout<<"请输入“猪”的英文单词："<<endl;
    cin>>ch;
    if(ch=="pig")
    {
        cout<<"猪："<<ch<<endl;
        cout<<ch<<"的第一个字符是："<<ch[0]<<endl;
    }
    else
        cout<<"输入错误\n";
    return 0;
}