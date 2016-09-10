/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename  sharememory.h
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

#ifndef SHAREMEMORY_H_
#define SHAREMEMORY_H_

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include <sys/shm.h>
#include <error.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>	
#define IPCKEY 0x366378    

//name space
namespace pure_baselib
{
class sharememory
{
public:
	//constructor function
	sharememory();
	~sharememory();

    //create share memory
	int creatsham(int shmsize);
        
	//disconnect with share memory
	int disconnectshm();
        
	//free memory
	int freeshm();

	//show the addree of share momery
	void display();  
	void write_tese(); 
protected:
	 //the id of share memory
     int shm_id;    
	
	 //the address of share memory
     char *shmaddr ;  
        
	 //the size of memorys
	 int  size;

};

} 
#endif /* SHAREMEMORY_H_ */
