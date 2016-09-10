/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename：json.h
* Description：Json字符串的还原
***************************************************************/
/**************************************************************
* Version：1.0.0
* Original_Author：张乔骏
* Date: 2012年12月11日
* Modified_Author: chengzhip
* Modified_Description: 修改json文件名字，相关函数的功能重写，命名规范.
* 						添加pure_livegw命名空间
* Modified_Date: 2012-12-26
***************************************************************/

#ifndef _JSON_H_
#define _JSON_H_


#include "basic_type.h"

using namespace pure_baselib;


namespace pure_livegw
{
	typedef struct Json_node JSON_S;

	typedef enum Type
	{
		Null,
		String,
		Number,
		Bool,
		Array,
		Object
	} JSON_TYPE_E;

	struct Json_node
	{
		s8			*p_name;
		u8			value_type;
		JSON_S		*pre;
		JSON_S		*up;
		JSON_S		*chd;
		JSON_S		*bro;
		
		s8			*p_value;
	};

	class CJson
	{
	private:

		JSON_S		*root;
		JSON_S		*node;
		JSON_S		*active_node;		//用于表示活跃节点

		//JSON_S		*temp;
		
		//JSON_S		*temp_node;
		
		s32			dir;
		s8			buff[4096];
		
		//for m_newbuff
		s8*			m_newbuff;
		s32			m_bufflen;
		
		s32			nsize;
		s32			npos;
		Type			bracket_type;
		Type			type_list[256];
		s32			list_pos;
		int 			comma;	
		//end add

		s32			size;
		s32			pos;
		JSON_S *		stack[256];	//堆栈用于存储上一级
		s32			stack_pos;	//堆栈位置

		void reduction(JSON_S *str,s32 value_type); //Json字串的输出
		void destroy(JSON_S *dnode); //销毁数据结构

	public:

		CJson();
		CJson(s8 * i_buf,s32 i_len);

		virtual ~CJson();

		void init(); //初始化

		void clear(); //结束调用

		void add_null(s8 *name); //添加NULL类型

		void add_string(s8 *name, s8 *value); //添加字符串类型

		void add_number(s8 *name, s8 *value); //添加数字

		void add_bool(s8 *name, s8 *value); //添加Bool值

		void add_array(s8 *name, s8 *value); //添加数组

		void add_object(s8 *name, s8 *value); //添加对象

		void json_travel(); //遍历所有数据

		void back_top(); //返回上一级

		s8 *get_buff();

		s8 *get_immedibuff();
	};
};

#endif
