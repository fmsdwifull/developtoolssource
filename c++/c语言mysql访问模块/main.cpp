#include "mysqlop.h"

int main()
{
	unsigned char buf[1024*8];
	mysqlop _mysql;
	//_mysql.sqlexec("select * from ticklog",2,NULL);
	_mysql.sqlexec("select * from ticklog",1,buf);
	
	for(int i;i<100;i++)
	{
		//printf("%x ",buf);
	}
	return 0;
}