#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main ()
{
    int src[]= {1, 2, 3, 4, 5, 6, 7};
    // vector<int> srcVec;
    // srcVec.resize(7); ����
    vector<int> srcVec(src, src + 7); // ע�⣡7Ϊ����
    ostream_iterator<int> ofile(cout, " ");
    // ����ֵ���Ƶ�vector����������ǿ�ʼ��������vector����Ŀ�ʼ
    // (������src + 7Խ����)src + 7 ��ʾ������srcVec.end()�൱��src + 7
    copy (src, src + 7, srcVec.begin());

    cout << "srcVec contains:\n";
    // ����ֵ���Ƶ�������У����������ǿ�ʼ�������������
    copy(srcVec.begin(), srcVec.end(), ofile);
    cout << endl;

    // �����������ƶ���λ
    copy(src + 2, src + 7, src);
    cout<< "shifting array sequence left by 2" << endl;
    copy(src, src + 7, ofile);
    cout << endl;

    // ��һ�ַ�����ע��۲�copy()�еڶ�������
    // srcVec.end()�൱��src + 7
    // �����������ƶ���λ
    copy(srcVec.begin() + 2, srcVec.end(), srcVec.begin());
    cout<< "shifting array sequence left by 2" << endl;
    copy(srcVec.begin(), srcVec.end(), ofile);
    cout << endl;
    return 0;
}

#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

int main(void)
{
	vector<string> coll;
	copy(istream_iterator<string>(cin),	// start of source
		 istream_iterator<string>(),	// end of source
		 back_inserter(coll));			//destination
	sort(coll.begin(), coll.end());		//sort
	unique_copy(coll.begin(), coll.end(),				//source
				ostream_iterator<string>(cout, "\n"));	//destination
	return 0;
}
#endif
