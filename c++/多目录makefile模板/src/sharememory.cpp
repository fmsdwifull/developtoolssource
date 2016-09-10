/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename  sharememory.cpp
* Description
***************************************************************/
/**************************************************************
* Version?.0.0
* Original_Author zhangsan
* Date 2012-8-13
* Modified_Author 
* Modified_Description
* Modified_Date: 2012-11-17
***************************************************************/

#include "sharememory.h"

namespace pure_baselib
{
	sharememory::sharememory()
	{
		shmaddr = NULL;
		size = 0;
	}
	sharememory::~sharememory()
	{
		freeshm();
	}

	//******************************************************************
	//create memory ,parater shmsize is the size of share memory
	//date:2012-12-6
	//*******************************************************************
	int sharememory::creatsham(int shmsize)
	{
		size = shmsize;
		shm_id = shmget(IPCKEY, size, IPC_CREAT|0600 ) ;
		if ( shm_id < 0 )
		{
			perror("get shm ipc_id error") ;
	    	return -1 ;
		}

		shmaddr = (char *)shmat( shm_id, NULL, 0 ) ;
		if ( (int)shmaddr == -1 )
		{
			perror("shmat addr error") ;
			return -1 ;
		}
		strcpy( shmaddr, "Hi, welcome to CHINA!\n") ;   
    	return 0 ;
	}

	//******************************************************************
	//free the share memory
	//date:2012-12-7
	//*******************************************************************
	int sharememory::freeshm()
	{
		shmdt( shmaddr );
		if( shmctl(shm_id, IPC_RMID, NULL) == -1)
	   	{
		   perror("shmctl error") ;
		   printf("shmctl error");
		   return -1;
	  	}
		return 0 ;
	}

	//******************************************************************
	//disconnect with share momery
	//date:2012-12-7
	//**********************************************************************************************************************************
	int  sharememory::disconnectshm()
	{
		if(shmdt( shmaddr ) == -1)    //是用来断开与共享内存附加点的地址，禁止本进程访问此片共享内存
      	{
			perror("shmadt");
		 	return  -1;
	  	}
		return 0;
	}

	//******************************************************************
	//show the address of share momery
	//date:2012-12-7
	//*******************************************************************
	void  sharememory::display()
	{
		printf("%s\n", shmaddr) ;
	}
	
	//******************************************************************
	//write  share momery
	//date:2012-12-7
	//*******************************************************************
	void sharememory::write_tese()
	{
		strcpy( shmaddr, "write_tese\n") ;	
	}

} /* namespace pure_baselib */
