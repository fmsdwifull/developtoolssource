/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename：json.cpp
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
//#define TRACE
//#include "log/pure_log.h"
#include "json.h"
#include "sys_headers.h"
#include <iostream>
using namespace std;

namespace pure_livegw
{
	CJson::CJson()
	{
		//buff[]={};
		memset(stack,0,sizeof(JSON_S *) * 256);
		stack_pos = 0;
		active_node = NULL;
		size=0;
		pos=0;
		root =NULL;
		//for m_newbuff
		m_newbuff = NULL;
		memset(type_list,0,sizeof(u8 *) * 256);
		list_pos = 0;
		nsize=0;
		npos=0;
		comma=1;
	}

	CJson::CJson(s8 * i_buf,s32 i_len)
	{
		//buff[]={};
		memset(stack,0,sizeof(JSON_S *) * 256);
		stack_pos = 0;
		active_node = NULL;
		size=0;
		pos=0;
		root = NULL;
		//for m_newbuff
		m_newbuff = i_buf;
		m_bufflen = i_len;
		memset(type_list,0,sizeof(u8 *) * 256);
		list_pos = 0;
		nsize=0;
		npos=0;
		comma=0;
	}

	CJson::~CJson()
	{
		clear();
	}

	void CJson::init()
	{
		root = NULL;
		dir = 1;
	}

	void CJson::clear()
	{
		destroy(root);
		root = NULL;
	}

	void CJson::reduction(JSON_S *str,s32 value_type)
	{
		switch(str->value_type)
		{

			case Null:

				if(value_type == Array)
				{
					//cout<<"\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s","null");
					pos = pos+size;

				}
				else
				{
					//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s%s%s","\"",str->p_name,"\":null");
					pos = pos+size;
				}
				
				if(str->bro != NULL)
				{
					//cout<<",";
					size = sprintf(buff+pos,"%s",",");
					pos = pos+size;
					reduction(str->bro,value_type);
				}
				break;

			case String:

				if(str->p_value)
				{
					if(value_type == Array)
					{
						//cout<<"\""<<str->p_value<<"\"";
						size = sprintf(buff+pos,"%s%s%s","\"",str->p_value,"\"");
						pos = pos+size;

					}
					else
					{
						//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
						size = sprintf(buff+pos,"%s%s%s%s%s","\"",str->p_name,"\":\"",str->p_value,"\"");
						pos = pos+size;
					}
					
					if(str->bro != NULL)
					{
						//cout<<",";
						size = sprintf(buff+pos,"%s",",");
						pos = pos+size;
						reduction(str->bro,value_type);
					}
				}
				else
				{
					if(value_type == Array)
					{
						//cout<<"\""<<str->p_value<<"\"";
						size = sprintf(buff+pos,"%s","null");
						pos = pos+size;

					}
					else
					{
						//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
						size = sprintf(buff+pos,"%s%s%s","\"",str->p_name,"\":null");
						pos = pos+size;
					}
					
					if(str->bro != NULL)
					{
						//cout<<",";
						size = sprintf(buff+pos,"%s",",");
						pos = pos+size;
						reduction(str->bro,value_type);
					}
				}
				break;

			case Number:

				if(value_type == Array)
				{
					//cout<<"\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s",str->p_value);
					pos = pos+size;

				}
				else
				{
					//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s%s%s%s","\"",str->p_name,"\":",str->p_value);
					pos = pos+size;
				}

				if(str->bro != NULL)
				{
					//cout<<",";
					size = sprintf(buff+pos,"%s",",");
					pos = pos+size;
					reduction(str->bro,value_type);
				}
				break;

			case Bool:

				if(value_type == Array)
				{
					//cout<<"\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s",str->p_value?"true":"false");
					pos = pos+size;

				}
				else
				{
					//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
					size = sprintf(buff+pos,"%s%s%s%s","\"",str->p_name,"\":",str->p_value?"true":"false");
					pos = pos+size;
				}

				if(str->bro != NULL)
				{
					//cout<<",";
					size = sprintf(buff+pos,"%s",",");
					pos = pos+size;
					reduction(str->bro,value_type);
				}
				break;

			case Array:

				if(value_type == Object)
				{
					//cout<<"\""<<str->p_name<<"\":";
					size = sprintf(buff+pos,"%s%s%s","\"",str->p_name,"\":");
					pos = pos+size;
				}
				

				//cout<<"[";
				size = sprintf(buff+pos,"%s","[");
				pos = pos+size;

				if(str->chd != NULL)
				{
					reduction(str->chd,Array);
				}

				//cout<<"]";
				size = sprintf(buff+pos,"%s","]");
				pos = pos+size;

				if(str->bro != NULL)
				{
					//cout<<",";
					size = sprintf(buff+pos,"%s",",");
					pos = pos+size;
					reduction(str->bro,value_type);
				}

				break;

			case Object:

				//cout<<"{";
				if(value_type == Object)
				{
					//cout<<"\""<<str->p_name<<"\":";
					size = sprintf(buff+pos,"%s%s%s","\"",str->p_name,"\":");
					pos = pos+size;
				}
				
				
				size = sprintf(buff+pos,"%s","{");
				pos = pos+size;

				if(str->chd != NULL)
				{
					reduction(str->chd,Object);
				}

				//cout<<"}";
				size = sprintf(buff+pos,"%s","}");
				pos = pos+size;

				if(str->bro != NULL)
				{
					//cout<<",";
					size = sprintf(buff+pos,"%s",",");
					pos = pos+size;
					reduction(str->bro,value_type);
				}
				break;
		}

	}

	void CJson::add_null(char *name)
	{
		node = new JSON_S;
		node->p_name = name;
	//	node->pre = temp;
	//	node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = NULL;
		node->value_type = Null;
		
		if(dir)
		{
			root ? active_node->bro = node :(root = node,active_node = root);
		}
		else
		{
			root ? active_node->chd = node :(root = node,active_node = root);
			dir = 1;
		}

		active_node = node;
		
		//add with m_newbuff
		if(!m_newbuff)
			return;
		
		if(comma)
		{
				nsize = sprintf(m_newbuff+npos,"%s",",");
				npos = npos+nsize;
		}
		comma = 1;
		
		if(bracket_type == Array)
		{
			//cout<<"\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s","\"","null","\"");
			npos = npos+nsize;

		}
		else
		{
			//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s%s%s","\"",name,"\":\"","null","\"");
			npos = npos+nsize;
		}
		//end add
	}

	void CJson::add_string(char *name,char *value)
	{
		node = new JSON_S;
		node->p_name = name;
//		node->pre = temp;
//		node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = value;
		node->value_type = String;

		if(dir)
		{
			root ? active_node->bro = node : (root = node,active_node = root);
		}
		else
		{
			root ? active_node->chd = node : (root = node,active_node = root);
			dir = 1;
		}

		active_node = node;
		
		/* Add to m_newbuff */

		if(!m_newbuff)
			return;

		if(comma)
		{
				nsize = sprintf(m_newbuff+npos,"%s",",");
				npos = npos+nsize;
		}
		comma = 1;
		
		if(value)
		{
			if(bracket_type == Array)
			{
				//cout<<"\""<<str->p_value<<"\"";
				nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",value,"\"");
				npos = npos+nsize;

			}
			else
			{
				//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
				nsize = sprintf(m_newbuff+npos,"%s%s%s%s%s","\"",name,"\":\"",value,"\"");
				npos = npos+nsize;
			}
			
		}
		else
		{
			if(bracket_type == Array)
			{
				//cout<<"\""<<str->p_value<<"\"";
				nsize = sprintf(m_newbuff+npos,"%s","\"null\"");
				npos = npos+nsize;

			}
			else
			{
				//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
				nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",name,"\":\"null\"");
				npos = npos+nsize;
			}
			
		}

		
		/* End add */
	}

	void CJson::add_number(char *name,char *value)
	{
		node = new JSON_S;
		node->p_name = name;
	//	node->pre = temp;
	//	node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = value;
		node->value_type = Number;

		if(dir)
		{
			root ? active_node->bro = node : (root = node,active_node = root);
		}
		else
		{
			root ? active_node->chd = node : (root = node,active_node = root);
			dir = 1;
		}

		active_node = node;
		
		//add with m_newbuff

		if(!m_newbuff)
			return;

		if(comma)
		{
				nsize = sprintf(m_newbuff+npos,"%s",",");
				npos = npos+nsize;
		}
		comma = 1;
		
		if(bracket_type == Array)
		{
			//cout<<"\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",value,"\"");
			npos = npos+nsize;

		}
		else
		{
			//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s%s%s","\"",name,"\":\"",value,"\"");
			npos = npos+nsize;
		}
		//end add
	}

	void CJson::add_bool(char *name,char *value)
	{
		node = new JSON_S;
		node->p_name = name;
	//	node->pre = temp;
	//	node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = value;
		node->value_type = Bool;

		if(dir)
		{
			root ? active_node->bro = node :(root = node,active_node = root);
		}
		else
		{
			root? active_node->chd = node : (root = node,active_node = root);
			dir = 1;
		}

		active_node = node;
		
		//add with m_newbuff
		if(!m_newbuff)
			return;

		if(comma)
		{
				nsize = sprintf(m_newbuff+npos,"%s",",");
				npos = npos+nsize;
		}
		comma = 1;
		
		if(bracket_type == Array)
		{
			//cout<<"\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",value,"\"");
			npos = npos+nsize;

		}
		else
		{
			//cout<<"\""<<str->p_name<<"\":\""<<str->p_value<<"\"";
			nsize = sprintf(m_newbuff+npos,"%s%s%s%s%s","\"",name,"\":\"",value,"\"");
			npos = npos+nsize;
		}
		//end add
	}

	void CJson::add_array(char *name,char *value)
	{

		node = new JSON_S;
		node->p_name = name;
		//node->pre = temp;
		//node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = value;
		node->value_type = Array;

		if(dir)
		{
			root ? active_node->bro = node : (root = node,active_node = root);
		}
		else
		{
			root ? active_node->chd = node : (root = node,active_node = root);
		}

		active_node = node;
		
		dir = 0;

		stack[stack_pos] = node;
		stack_pos++;		
		
		//add with m_newbuff
		if(!m_newbuff)
			return;

		if(list_pos == 0)
		{
			nsize = sprintf(m_newbuff+npos,"%s","[");
		}
		else
		{
			if(comma == 1)
			{
				nsize =  sprintf(m_newbuff+npos,"%s",",");
				npos += nsize;
			}
			if(bracket_type == Array)
			{
				nsize = sprintf(m_newbuff+npos,"%s","[");
				
			}
			else
			{
				nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",name,"\":[");
			}
		}
		npos = npos+nsize;
		comma=0;
		bracket_type = Array;
		type_list[list_pos] = Array;
		list_pos++;
		//end add
		
	}

	void CJson::add_object(char *name,char *value)
	{
		node = new JSON_S;
		node->p_name = name;
	//	node->pre = temp;
	//	node->up = temp_node;
		node->bro = NULL;
		node->chd = NULL;
		node->p_value = value;
		node->value_type = Object;

		if(dir)
		{
			root ? active_node->bro = node : (root = node,active_node = root);
		}
		else
		{
			root ? active_node->chd = node : (root = node,active_node = root);
		}
		
		active_node = node;
	
		dir = 0;//child direct

		stack[stack_pos] = node;
		stack_pos++;
		
		//add with m_newbuff
		if(!m_newbuff)
			return;

		if(list_pos == 0)
		{
			nsize = sprintf(m_newbuff+npos,"%s","{");
		}
		else
		{
			if(comma == 1)
			{
				nsize =  sprintf(m_newbuff+npos,"%s",",");
				npos += nsize;
			}
			
			if(bracket_type == Array)
			{
				nsize = sprintf(m_newbuff+npos,"%s","{");
				
			}
			else
			{
				nsize = sprintf(m_newbuff+npos,"%s%s%s","\"",name,"\":{");
				
			}
		}
		npos = npos+nsize;
		comma=0;
		bracket_type = Object;
		type_list[list_pos] = Object;
		list_pos++;
		//end add
	}


	void CJson::json_travel()
	{
		reduction(root,Array);
		//cout<<endl<<buff<<endl;
	}

	void CJson::back_top()
	{
	
		dir = 1;

		stack_pos--;
		active_node = stack[stack_pos];
		
		//add with m_newbuff
		
		if(!m_newbuff)
			return;
		
		if(bracket_type == Array)
		{
			nsize = sprintf(m_newbuff+npos,"%s","]");
			npos = npos+nsize;
		}
		else
		{
			nsize = sprintf(m_newbuff+npos,"%s","}");
			npos = npos+nsize;
		}
		
		list_pos--;
		bracket_type = type_list[list_pos-1];//	sign for bracket
		//cout<<bracket_type<<endl;
		comma=1;
		
		//end add
	
		
	}

	void CJson::destroy(JSON_S * dnode)
	{
		if(dnode != NULL)
		{
			if(dnode->chd != NULL)
			{
				destroy(dnode->chd);
				dnode->chd = NULL;
			}
			if(dnode->bro != NULL)
			{
				destroy(dnode->bro);
				dnode->bro = NULL;
			}
			delete dnode;
		}
		
	}

	s8 * CJson::get_buff()
	{
		//return buff;
		//cout<<m_newbuff<<endl;
		//return buff;
		return buff;
	}

	s8 * CJson::get_immedibuff()
	{
		//return buff;
		//NDEBUG("%s",m_newbuff);
		//return buff;
		return m_newbuff;
	}

};



