/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename��json.h
* Description��Json�ַ����Ļ�ԭ
***************************************************************/
/**************************************************************
* Version��1.0.0
* Original_Author�����ǿ�
* Date: 2012��12��11��
* Modified_Author: chengzhip
* Modified_Description: �޸�json�ļ����֣���غ����Ĺ�����д�������淶.
* 						���pure_livegw�����ռ�
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
		JSON_S		*active_node;		//���ڱ�ʾ��Ծ�ڵ�

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
		JSON_S *		stack[256];	//��ջ���ڴ洢��һ��
		s32			stack_pos;	//��ջλ��

		void reduction(JSON_S *str,s32 value_type); //Json�ִ������
		void destroy(JSON_S *dnode); //�������ݽṹ

	public:

		CJson();
		CJson(s8 * i_buf,s32 i_len);

		virtual ~CJson();

		void init(); //��ʼ��

		void clear(); //��������

		void add_null(s8 *name); //���NULL����

		void add_string(s8 *name, s8 *value); //����ַ�������

		void add_number(s8 *name, s8 *value); //�������

		void add_bool(s8 *name, s8 *value); //���Boolֵ

		void add_array(s8 *name, s8 *value); //�������

		void add_object(s8 *name, s8 *value); //��Ӷ���

		void json_travel(); //������������

		void back_top(); //������һ��

		s8 *get_buff();

		s8 *get_immedibuff();
	};
};

#endif
