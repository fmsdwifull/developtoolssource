#include "pure_log.h"


p_base::CLog logi;

int main()
{
	logi.init("/home/doudou/test/log/","test");
       logi.set_log_level(p_base::LOG_INFO);
       logi.prt(p_base::LOG_INFO, "MediaServer Launching.");
	printf("xxxxxxxxxxxxxxxxxxx\n");

	return 0;
}