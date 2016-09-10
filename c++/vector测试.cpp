#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int>vi;
    int a;
    while(true)
    {
    	cout<<"enter a num , when stop have 0"<<endl;
    	cin>>a;
    	if(a==0)
    		break;
    	vi.push_back(a);   
    	vector<int>::iterator iter;
    	for(iter=vi.begin();iter!=vi.end();++iter)
    		cout<<*iter;      
    }
    return 0;
}
