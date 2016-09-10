#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main ()
{
    int src[]= {1, 2, 3, 4, 5, 6, 7};
    // vector<int> srcVec;
    // srcVec.resize(7); 或者
    vector<int> srcVec(src, src + 7); // 注意！7为长度
    ostream_iterator<int> ofile(cout, " ");
    // 将数值复制到vector里，参数依次是开始、结束，vector数组的开始
    // (看起来src + 7越界了)src + 7 表示结束，srcVec.end()相当于src + 7
    copy (src, src + 7, srcVec.begin());

    cout << "srcVec contains:\n";
    // 将数值复制到输出流中，参数依次是开始、结束，输出流
    copy(srcVec.begin(), srcVec.end(), ofile);
    cout << endl;

    // 将数组向左移动两位
    copy(src + 2, src + 7, src);
    cout<< "shifting array sequence left by 2" << endl;
    copy(src, src + 7, ofile);
    cout << endl;

    // 另一种方法，注意观察copy()中第二个参数
    // srcVec.end()相当于src + 7
    // 将数组向左移动两位
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
