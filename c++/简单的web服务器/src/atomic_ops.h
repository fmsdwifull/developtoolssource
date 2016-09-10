/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename：atomic_ops.h
* Description：原子操作的定义
***************************************************************/
/**************************************************************
* Version：1.0.0
* Original_Author：chengzhip
* Date：2013-05-14
* Modified_Author：
* Modified_Description：
* Modified_Date: 
***************************************************************/

#ifndef _ATOMIC_OPS_H_
#define _ATOMIC_OPS_H_

namespace baselib
{
	#define CAS(_ptr, _old_value, _new_value)	\
		__sync_bool_compare_and_swap(_ptr, _old_value, _new_value)

	#define ATOMIC_ADD(_ptr, value)	\
		__sync_add_and_fetch(_ptr, value)

	#define ATOMIC_SUB(_ptr, value)	\
		__sync_sub_and_fetch(_ptr, value)

};



#endif /* _ATOMIC_OPS_H_ */

