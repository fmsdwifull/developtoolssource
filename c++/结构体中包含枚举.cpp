#include <stdio.h>
#include<arpa/inet.h>


typedef enum {January,Febrary,March,April,May,June,July,August,September,October,November,December} MONTH;




typedef struct Date
{
	int year;
	MONTH m;
	int day;
}Date_type;

struct Date ComposeDate(int y,MONTH m, int d)
{
	Date_type z = {y,July,d};
	return z;
}

int main(void)
{
	//ComposeDate(2001,July,31);
	return 0;
}



