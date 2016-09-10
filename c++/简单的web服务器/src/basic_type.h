/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename：basic_type.h
* Description：定义基础数据类型
***************************************************************/
/**************************************************************
* Version：1.0.0
* Original_Author：chengzhip
* Date：2012-8-13
* Modified_Author：pxh
* Modified_Description：更改了命名空间
* Modified_Date: 2012-11-17
***************************************************************/

#ifndef _BASIC_TYPE_H_
#define _BASIC_TYPE_H_

namespace baselib
{

	typedef struct pure_string_s					PURE_STRING_S;

	#define __WORD_SIZE 	64
	
	/**************************************
		type definition for platform 32
	**************************************/
	#if	__WORD_SIZE == 32
	
		typedef char 								s8;
		typedef unsigned char 						u8;
		typedef signed short int 					s16;
		typedef unsigned short int 					u16;
		typedef signed int 							s32;
		typedef unsigned int 						u32;
		typedef float								f32;
		typedef u8 									boolean;
		typedef double								d64;
		typedef signed long 						sl32;
		typedef unsigned long 						ul32;
		typedef signed long long 					sl64;
		typedef unsigned long long 					ul64;
		typedef long double							ld96;
		
	#endif


	
	/**************************************
		type definition for platform 64
	**************************************/
	#if	__WORD_SIZE == 64
	
		typedef char 								s8;
		typedef unsigned char 						u8;
		typedef signed short int 					s16;
		typedef unsigned short int 					u16;
		typedef signed int 							s32;
		typedef unsigned int 						u32;
		typedef float								f32;
		typedef u8 									boolean;
		typedef double								d64;
		typedef signed long 						sl64;
		typedef unsigned long						ul64;
		typedef signed long long 					sll64;
		typedef unsigned long long 					ull64;
		typedef long double							ld128;
		
	#endif


	/************************ 
		struct definition 
	************************/
	struct pure_string_s
	{
		s8		*str_name;	//string的内容
		u32		str_len;	//string的长度
	};


	/****************************  
		bool value definition  
	****************************/
	#define true									(1 == 1)
	#define false   								!true

	
	/**************************************** 
		points definition for platform 32 
	****************************************/
	#if	__WORD_SIZE == 32
	
		typedef s8*									pS8;
		typedef u8*									pU8;
		typedef s16*								pS16;
		typedef u16*								pU16;
		typedef s32*								pS32;
		typedef u32*								pU32;
		typedef f32*								pF32;
		typedef d64*								pD64;
		typedef sl32*								pSl32;
		typedef ul32*								pUl32;
		typedef sl64*								pSl64;
		typedef ul64*								pUl64;
		typedef ld96								pLd96;
		typedef void*								pVoid;
		typedef boolean*							pBoolean;
		
	#endif


	/**************************************** 
		points definition for platform 32 
	****************************************/
	#if	__WORD_SIZE == 64

		typedef s8*									pS8;
		typedef u8*									pU8;
		typedef s16*								pS16;
		typedef u16*								pU16;
		typedef s32*								pS32;
		typedef u32*								pU32;
		typedef f32*								pF32;
		typedef d64*								pD64;
		typedef sl64*								pSl64;
		typedef ul64*								pUl64;
		typedef sll64*								pSll64;
		typedef ull64*								pUll64;
		typedef ld128								pLd128;
		typedef void*								pVoid;
		typedef boolean*							pBoolean;
		
	#endif
	
};

#endif /* _BASIC_TYPE_H_ */
