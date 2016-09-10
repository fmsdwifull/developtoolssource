/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename  test.cpp
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

#include <iostream>
#include"sharememory.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
	using namespace pure_baselib;
	int shamsize;
	sharememory  sh1;
	printf("请输入需要开辟共享内存的大小!\n");
	scanf("%d",&shamsize);

	//create the share momery
	sh1.creatsham(shamsize);

	//show the address 
	//sh1.display();

	//use the share momery to write
	sh1.write_tese();
	sh1.display();
	//sh1.display();
	sh1.freeshm();

	return 0;
}
