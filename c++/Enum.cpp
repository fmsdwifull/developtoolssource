// Enum.cpp

#include <iostream>
using namespace std;






class X
{
public:
	enum weight { light, medium, heavy, very_heavy };
	enum {d1 = 3, d2 = 5 };
	
	int x;
	weight wx;

	X(int i, int j) { x = i + d1; wx = (weight)(j +medium); }
};

enum { c1 = 17, c2 = 19 };
enum height { tall, very_tall };


int main()
{
	X obj1(100, 200);
	cout << obj1.x << " "<< obj1.wx << endl;
	// X obj2(100, light); // wrong
	int y = c1;
	cout << y << endl;
	height h;
	h = tall;
	cout << h << endl;
	return 0;
}
