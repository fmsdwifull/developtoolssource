#ifndef  __PROBDTH_H_
#define  __PROBDTH_H_

#include <iostream>
#include "task_queue.h"

extern "C"
{
	#include <pthread.h>
}

namespace baselib
{
	class Probeth
	{
		public:
			Probeth(void *);
			~Probeth();
			//virtual void *dowork(void *);
			static void *run(void *);
		private:
			pthread_t th;


	};
}

#endif
