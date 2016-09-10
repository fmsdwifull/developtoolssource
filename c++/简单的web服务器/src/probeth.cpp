#include "probeth.h"
#include "socknet.h"


using namespace baselib ;

extern char	request[BUFSIZ];
extern int     commu_fd;


Probeth::Probeth(void *arg)
{	
	std::cout<<"this is probeth structure"<<std::endl;
	if(pthread_create(&th,NULL,run,arg)!=0)
	{
		std::cout<<"pthread error"<<std::endl;
		exit(-1);
	}
}
Probeth::~Probeth()
{	

}


void *Probeth::run(void * arg)
{
	int num;
	queue<int>  *dq=(queue<int> *)arg;
	while(1)
	{
		
		printf("@@@@@@@@@@@@@@@@@@@@@:%d\n",commu_fd);
		num=dq->get_queue_len();
		if(num==0)
		{
			std::cout<<" have no data in queue  "<<std::endl;		
		}
		else
		{
			std::cout<<" have  data in queue ,have  "<<num<<"   data"<<std::endl;	
			process_rq(request, commu_fd);	//返回给客户端	
		}
		sleep(1);
	}
}

