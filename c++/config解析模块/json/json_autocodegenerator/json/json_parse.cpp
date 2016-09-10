#include "json_parse.h"

namespace pure_livegw
{
	CJson_parse::CJson_parse(s8 *string)
	{
		src = string;
		len = strlen(src) +1;
		stack_lvl = 0;
		json_tree = NULL;
	}

	/*
	 *	creat new node;
	 */
	JSON_TREE_NODE_S* CJson_parse::new_json_node(void)
	{
		JSON_TREE_NODE_S *tmp = new JSON_TREE_NODE_S;
		if(tmp)
			memset(tmp,0,sizeof(JSON_TREE_NODE_S));
		return tmp;
	}

	void CJson_parse::init(s8 *string)
	{
		src = string;
		len = strlen(src) +1;
		stack_lvl =0;
	}
	
	
	/*
	*	parse process;
	*	0 means successful, -1 means failed;
	*/
	s32 CJson_parse::do_parse(void)
	{
		json_tree_node *tmp;	
		json_tree = new_json_node();	
		if (!json_tree)
		{
			return -1;
		}
		s8 * pos = src;
		switch(*pos)
		{
		case '{':
			json_tree->value_type = OBJECT;
			json_tree->chd = tmp = new_json_node();
			if(!tmp)
			{
				return -1;
			}
			stack_lvl++;
			pos = json_parse_object(src+1,tmp);
			if(pos == NULL)
			{
				printf("parse error!\n");
				return -1;
			}
			break;
		
		default:
			printf("not start with { \n");
			return -1;
		}
		return 0;

	}

	/*
	*in: 
	*	pos = the start parse string pos.
	*out:
	*	function return: s8 * next s8 to parse
	*	dest_string = value string
	*/
	s8* CJson_parse::json_parse_string(s8 *pos,s8 **dest_string)
	{
		s8 * pbuf = new s8[256];
		s32 pbuflen = 256;
		memset(pbuf,0,256);
		s32 dp = 0;
		u32 c=0;
		while(pos<src+len)
		{
			switch(*pos)
			{
				case '\\':
					if(pos+1<src+len)
					{
						pos++;
						if(dp >= pbuflen-1)
						{
							s8 * tmpbuf = new s8[pbuflen+256];
							if(tmpbuf==NULL)
							{
								printf("alloc tmpbuf failed\n");
								goto failed;
							}
							pbuflen += 256;
							strcpy(tmpbuf,pbuf);
							delete [] pbuf;
							pbuf = tmpbuf;
						}

						switch(*pos)
						{
						case '"':
							pbuf[dp] = '"';
							dp++;
							break;
						case '\\':
							pbuf[dp] = '\\';
							dp++;
							break;
						case '/':
							pbuf[dp] = '/';
							dp++;
							break;
						case 'b':
							pbuf[dp] = '\b';
							dp++;
							break;
						case 'f':
							pbuf[dp] = '\f';
							dp++;
							break;
						case 'n':
							pbuf[dp] = '\n';
							dp++;
							break;
						case 'r':
							pbuf[dp] = '\r';
							dp++;
							break;
						case 't':
							pbuf[dp] = '\t';
							dp++;
							break;
						case 'u':
							/*4 hexademical digit,now unsupport*/
							printf("4 hexademical digit,now unsupport\n");
						
							for(s32 i =0;i<4;i++)
							{
								pos++;
								if(pos>=src+len)
								{
									printf("uncompleted \"\\u\"\n");
									goto failed;
								}
								else
								{
									if((*pos >='0')&&(*pos <='9'))
									{
										c = (c<<4) + (*pos-'0');
									}
									else if( (*pos >= 'a') && (*pos <= 'f'))
									{
										c = (c<<4) + 10 + (*pos - 'a');
									}
									else if((*pos >= 'A') && (*pos <= 'F'))
									{
										c = (c<<4) + 10 + (*pos - 'A');
									}
									else
									{
										printf("invalid s8 after \\u \n");
										goto failed;
									}
								}
							}
							pbuf[dp] = c;
							dp++;
							break;
						default:
							printf("\\%c unsopport \n",*pos);
							goto failed;
						}
					}
					else
					{
						printf("NULL string");
						goto failed;
					}
					pos++;
					break;
				case '"':
					/*end*/
					*dest_string = pbuf;
					pbuf[dp] = '\0';
					return pos+1;
				default:
					if(dp >= pbuflen-1)
					{
						s8 * tmpbuf = new s8[pbuflen+256];
						if(tmpbuf == NULL)
						{
							printf("alloc tmpbuf failed\n");
							goto failed;
						}
						pbuflen += 256;
						strcpy(tmpbuf,pbuf);
						delete [] pbuf;
						pbuf = tmpbuf;
					}
					pbuf[dp] = *pos;
					dp++;
					pos++;
					break;
			}
		}

failed:
		*dest_string = NULL;
		delete [] pbuf;
		return NULL;
	}

	/*in:
	*	s =  parse_string_pos
	*	node = the node object and 
	*out:
	*	s8 * next s8 to parse.NULL means failed.
	*/
	s8* CJson_parse::json_parse_object(s8 *string,json_tree_node *node)
	{
		s8 * pos = string;
		/*expect " name*/
		
		
		while(pos < src+len)
		{

			/*expect '" }' vlaue*/
			switch(*pos)
			{
			case '"':
				pos  = json_parse_string(pos+1,&(node->name));
				if(pos == NULL)
				{
					printf("parse string failed. \n");
					return NULL;
				}
				break;
			case '}':
				return pos +1;
			default:
				printf("parse object failed. expect \" or } ,at %d \n",pos-src);
				return NULL;
			}
			
			if(pos >= src+len)
			{
				printf("none completed json string \n");
				return NULL;
			}

			/*expect :*/
			if(*pos != ':')
			{
				printf("expect s8 ':', the pos = %d s8\n",pos-src);
				return NULL;
			}
			
			pos = json_parse_value(pos+1,node);
			if(pos == NULL)
			{
				return NULL;
			}

			if(pos >= src+len)
			{
				printf("none completed json string \n");
				return NULL;
			}

			
			switch(*pos)
			{
			case ',':
				node->bro = new_json_node();
				if(!node->bro)
				{
					printf("alloc memory failed \n");
					return NULL;
				}
				node = node->bro;
				pos++;
				break;
			case '}':
				return pos +1;
			default:
				printf("error object completed , pos = %d,c= %c\n",pos-src,*pos);
				return NULL;
			}
		}

		return pos;

	}
	/*in:
	*	s = pos to parse
	*	node = first unit in array
	*out:
	*	s8 * ret_val = next pos to parse
	*	
	*/
	s8* CJson_parse::json_parse_array(s8 *string,json_tree_node *node)
	{
		s8 * pos = string;
		while(pos < src+len)
		{
			switch(*pos)
			{
				case ']':
					return pos+1;
			
				default:
					pos = json_parse_value(pos,node);
					if(pos == NULL)
					{
						return NULL;
					}
					break;
			}

			
			if(pos >= src+len)
			{
				printf("Not completed json string\n");
				return NULL;
			}

			switch(*pos)
			{
			case ',':
				node->bro = new_json_node();
				if(!node->bro)
				{
					printf("alloc memory failed\n");
					return NULL;
				}
				node= node->bro;
				pos++;
				break;
			case ']':
				return pos+1;
			}
		}
		return pos;
	}

	/*
	*in:
	*	s = pos to parse
	*	node = which the vlaue belong to
	*out:
	*	s8 * ret_val= next pos to parse
	*/
	s8* CJson_parse::json_parse_value(s8 *string,json_tree_node *node)
	{
		
		s8 * pos =string;
		if(pos >= src+len)
		{
			return pos;
		}
		switch(*pos)
		{
		case '{':
			/*child object*/
			node->value_type = OBJECT; 
			node->chd = new_json_node();
			if(!node->chd)
			{
				printf("alloc memory failed \n");
				return NULL;
			}
			pos = json_parse_object(pos+1,node->chd);
			break;
		case '"':
			/*string*/
			node->value_type = STRING;
			pos = json_parse_string(pos+1,&node->value);
			break;
		case '[':
			/*array*/
			node->value_type = ARRAY;
			node->chd = new_json_node();
			if(!node->chd)
			{
				printf("alloc memory failed \n");
				return NULL;
			}
			pos = json_parse_array(pos+1,node->chd);
			break;
		case 't':
			if(strncmp(pos,"true",4) == 0)
			{
				/*true*/
				node->value_type = BOOL;
				node->value = (s8 *)1;
				pos += 4;
				break;
			}
			else
			{
				printf("invalid value pos = %d,c = %c\n",pos-src,*pos);
				return NULL;
			}
			break;
		case 'f':
			if(strncmp(pos,"false",5) == 0)
			{
				/*false*/
				node->value_type = BOOL;
				node->value = (s8 *)0;
				pos += 5;
				break;
			}
			else
			{
				printf("invalid value pos = %d.\n",pos-src);
				return NULL;
			}
			break;
		case 'n':
			if(strncmp(pos,"null",4) == 0)
			{
				/*null*/
				node->value_type = NULL_VALUE;
				node->value = NULL;
				pos += 4;
				break;
			}
			else
			{
				printf("invalid value pos = %d.\n",pos-src);
				return NULL;
			}
			break;
		default:
			if((*pos>='0'&&*pos<='9')||*pos == '-')
			{
				/*number*/
				node->value_type = NUMBER;
				pos = json_parse_number(pos,&node->value);
			}
			else
			{
				printf("invalid value pos = %d.\n",pos-src);
				return NULL;	
			}
			break;
		}

		return pos;

	}


	/*
	*in:
	*	s = the pos where to parse; 
	*	pvalue = the value point;
	*	point to double 64bit. 
	*out:
	*	the pos next to parse,
	*/
	s8 * CJson_parse::json_parse_number(s8 *string,s8 **pvalue)
	{
		float number = 0;
		s32 expnum = 0;
		float dotnum = 0;
		s8 * pos = string;

		u8 negativeflag = 0;
		s32 dotlvl = 0;
		u8 dotflag = 0;

		u8 expflag = 0;
		u8 expnegativeflag =0;

		switch(*pos)
		{
		case '-':
			negativeflag =1;
			pos++;
			break;
		case '0':
			
			pos++;
			if(pos < src+len)
			{
				switch(*pos)
				{
				case '.':
					dotflag = 1;
					pos++;
					break;
				default:
					*pvalue = 0;
					return pos;
				}
			}
			break;
		default:
			if((*pos >= '1' )&&(*pos <= '9'))
			{
				number += *pos-'0';
				pos++;
				break;
			}
			else
			{
				printf("invalid number ,at %d \n",pos - src);
				return NULL;
			}
		}

		while(pos < src+len)
		{
			switch(*pos)
			{
			case '.':
				if(dotflag==0)
					dotflag = 1;
				else
				{
					printf("not expect '.' at %d \n",pos-src);
					return NULL;
				}
				pos++;
				break;
			case 'e':
			case 'E':
				if(expflag == 0)
				{
					expflag = 1;
					pos++;
					if(pos < src+len)
					{
						switch(*pos)
						{
						case '-':
							expnegativeflag = 1; 
							pos ++;
							break;
						case '+':
							pos ++;
							break;
						default:
							if((*pos >= '1' )&&(*pos <= '9'))
							{
								
								expnum += *pos - '0';
								pos++;
								break;
							}
							else
							{
								printf("except '+', '-'or 1-9 ,at %d \n",pos-src);
								return NULL;
							}

						}
					}
					else
					{
						printf("none completed json string\n");
						return NULL;
					}
				}
				else
				{
					printf("not expect 'e' or 'E',at %d \n ",pos - src);
					return NULL;
				}
				break;
			default:
				if((*pos >= '0' )&&(*pos <= '9'))
				{
					if(expflag == 1)
					{
						expnum = expnum*10 + (*pos-'0');
					}
					else if(dotflag)
					{
						dotlvl++;
						dotnum = (*pos - '0');
						for(s32 i=0;i<dotlvl;i++)
						{
							dotnum /= 10; 
						}
						number += dotnum;

					}
					else
					{
						number = number*10 + (*pos -'0');
					}
					pos ++;
				}
				else
				{
					if(negativeflag == 1)
					{
						number = 0 - number;
					}
					if(expflag == 1)
					{
						if(expnegativeflag == 1)
						{
							number = number * pow((float)10,0-expnum);
						}
						else
						{
							number = number * pow((float)10,expnum);
						}
					}
					float * pd = (float *)pvalue;
					*pd = number;
					return pos;
				}
				break;
			}
		}
		return pos;
	}
	/*
	*in: n = value name,dest = the value point.
	*out: if value type == string ,then value = s8 *.
	*		value type == number, value = double 
	*		value type == bool ,value = 1 true,value =0 false
	*		value type == NULL, value =0;
	*		0 means succesful,-1 means failed.
	*t.b.d:not suport recursion search,now only can search the element at root.
	*/
	s32 CJson_parse::get_value_by_name(s8 * n,/*out*/s8 ** dest)
	{
		JSON_TREE_NODE_S * tmp = json_tree;
		while(tmp)
		{
			if(tmp->value_type != OBJECT && tmp->value_type != ARRAY)
			{
				if(strcmp(tmp->name,n) == 0)
				{
					*dest = tmp->value;
					return 0;
				}
			}
			tmp = tmp->bro;
		}

		return -1;
	}

	/*
	*in:
	*	n = array name.
	*	index = array index,dest is a the array element struct. 
	*		the struct must be defined as follow disciption:
	*					string : s8 * ,64bit
	*					number : double
	*					bool   : double
	*					NULL   : double 0
	*					object : will be recursion
	*out:
	*	0 means successful, -1 means failed.
	*/

	s32 CJson_parse::get_array_unit_by_name_and_index(s8 * n,s32 index,s8** dest,s32 destlen)
	{
		s32 i =0;
		JSON_TREE_NODE_S * tmp = json_tree;
		JSON_TREE_NODE_S * tmp_unit;
		s8 ** dest_pos = dest;
		while(tmp)
		{
			if(tmp->value_type == ARRAY)
			{
				if(strcmp(tmp->name,n) == 0)
				{
					if(tmp->chd)
					{
						tmp_unit = tmp->chd;
						while(tmp_unit)
						{
							if(i == index)
							{
								/*form the dest struct*/
								
								dest_pos = form_element_node(tmp_unit,dest,destlen);
								if(dest_pos == NULL)
								{
									return -1;
								}
								else
								{
									return 0;
								}
							}
							tmp_unit = tmp_unit->bro;
							i++;
						}
					}
					else
					{
						return -1;
					}
				}
			}
			tmp = tmp->bro;
		}
		return -1;
	}
	/*
	*in:
	*	node = tree_node;
	*	dest = out value;
	*	destlen = dest buf length;
	*out:
	*	return dest_pos;
	*
	*/

	s8** CJson_parse::form_element_node(JSON_TREE_NODE_S *node, s8** dest, s32 destlen)
	{
		s32 point_len = sizeof(s8 *);
		s32 rem_len = destlen;
		s8 ** dest_pos = dest;
		JSON_TREE_NODE_S * subnode;
		if(!node->chd)
		{
			printf("this element is NULL");
			return NULL;
		}
		subnode = node->chd;
		while(subnode)
		{
			switch(subnode->value_type)
			{
			case STRING:
			case NUMBER:
			case BOOL:
			case NULL_VALUE:
				if(rem_len < point_len)
				{
					printf("the struct size too small");
					return NULL;
				}
				*dest_pos = subnode->value;
				dest_pos += 1;
				rem_len -= point_len;
				break;
			case OBJECT:
				/*recursion */
				dest_pos = form_element_node(subnode,dest_pos,rem_len);
				if(dest_pos == NULL)
				{
					return NULL;
				}
				rem_len = destlen - (dest_pos - dest);
				break;
			case ARRAY:
				/*ignore array*/
				printf("get struct ignore array!\n");
				break;
			default:
				printf("error value type \n");
				return NULL;
			}
			subnode = subnode->bro;
		}
		return dest_pos;
	}

	/*
	*in:
	*	n = the type element name
	*	node = the start node
	*	i_type = what type want to find	
	*out:
	*	the node which matches the name and i_type
	*warning:the name can not be used repeated. 
	*/

	JSON_TREE_NODE_S * CJson_parse::find_node_by_name_and_type(JSON_TREE_NODE_S* node,s8 * n, u8 i_type)
	{

		JSON_TREE_NODE_S * obj = NULL;
		if(node->chd)
		{
			if(obj = find_node_by_name_and_type(node->chd,n,i_type))
			{
				return obj;
			}
		}
		if(node->bro)
		{
			if(obj = find_node_by_name_and_type(node->bro,n,i_type))
			{
				return obj;
			}
		}
		if(node->value_type == i_type)
		{
			if(node->name)
			{
				if(strcmp(node->name,n) == 0)
				{
					return node;
				}
			}
		}

		return NULL;
		
	}
		
	/*
	*in:
	*	n = name;
	*out:
	*	the array size;
	*t.b.d:not suport recursion search,now only can search the element at root. HAVE DONE
	*/
	s32 CJson_parse::get_array_size_by_name(s8 * n)
	{
		s32 size =0;
		JSON_TREE_NODE_S * tmp = json_tree;
		JSON_TREE_NODE_S * tmp_unit;
		tmp = find_node_by_name_and_type(tmp,n,ARRAY);
		
		if(tmp)
		{
			if(tmp->name == 0)
			{
				return 0;
			}
			if(strcmp(tmp->name,n) == 0)
			{
				if(tmp->chd)
				{
					tmp_unit = tmp->chd;
					if(tmp_unit->value_type == 0)
					{
						return 0;
					}
					size++;
					while(tmp_unit->bro)
					{
						tmp_unit = tmp_unit->bro;
						size++;
					}
					return size;
				}
			}
		}
		
		return 0;
	}



	s32 CJson_parse::get_element_by_name_and_index(s8 * array_name,s32 index,s8 * element_name,void** dest)
	{
		s32 i =0;
		JSON_TREE_NODE_S * tmp = json_tree;
		JSON_TREE_NODE_S * tmp_unit,*subnode;

		while(tmp)
		{
			if(tmp->value_type == ARRAY)
			{
				if(strcmp(tmp->name,array_name) == 0)
				{
					if(tmp->chd)
					{
						tmp_unit = tmp->chd;
						while(tmp_unit)
						{
							if(i == index)
							{
								subnode = tmp_unit->chd;
								while(subnode)
								{
									if(strcmp(subnode->name,element_name) == 0)
									{
										switch(subnode->value_type)
										{
										case STRING:
										case NUMBER:
										case BOOL:
										case NULL_VALUE:
											*dest = subnode->value;
											return 0;
											break;
										case OBJECT:
											/*recursion */
											printf("this function doesn't support sub-object!");
											*dest = NULL;
											return -1;
											break;
										case ARRAY:
											/*ignore array*/
											printf("get struct ignore array!\n");
											return -1;
											break;
										default:
											printf("error value type \n");
											return -1;
										}
									}
									subnode = subnode->bro;
								}
								
							}
							tmp_unit = tmp_unit->bro;
							i++;
						}
					}
					else
					{
						printf("No found this index in the array\n");
						return -1;
					}
				}
			}
			tmp = tmp->bro;
		}
		printf("No found this name array\n");
		return -1;
	}

	CJson_parse::~CJson_parse()
	{
		if(json_tree)
			delete_node(json_tree);

	}

	JSON_TREE_NODE_S * CJson_parse::delete_node(JSON_TREE_NODE_S * node)
	{
		if(node->chd)
		{
			node->chd = delete_node(node->chd);
		}
		if(node->bro)
		{
			node->bro = delete_node(node->bro);
		}
		if(node->value_type == STRING)
		{
			delete[] node->value;
		}
		if(node->name)
		{
			delete[] node->name;
		}
		delete node;
		return NULL;
	}

	void * CJson_parse::xget_sub_object_by_name(void * node,s8 * n)
	{
		if(node == NULL)
		{
			node = json_tree;
		}
		
		JSON_TREE_NODE_S * tmp = (JSON_TREE_NODE_S *)node;

		if(tmp && tmp!=json_tree)
			tmp = tmp->chd;
		
		while(tmp)
		{
			if(tmp->value_type == OBJECT || tmp->value_type == ARRAY)
			{
				if(strcmp(tmp->name,n) == 0)
				{
					return tmp;
				}
			}
			tmp = tmp->bro;
		}
		
	}
	
	s32 CJson_parse::xget_object_element_by_name(void * node,s8 * element_name,void** dest)
	{
	
		s32 i =0;
		if(node == NULL)
		{
			node = json_tree;
		}
		JSON_TREE_NODE_S * tmp = (JSON_TREE_NODE_S *)node;
		JSON_TREE_NODE_S * tmp_unit,*subnode;

		if(tmp && tmp->value_type==OBJECT)
		{
			if(tmp->chd)
			{
				tmp_unit = tmp->chd;
				while(tmp_unit)
				{
					if(tmp_unit && strcmp(tmp_unit->name,element_name)==0)
					{
						switch(tmp_unit->value_type)
						{
						case STRING:
						case NUMBER:
						case BOOL:
						case NULL_VALUE:
							*dest = tmp_unit->value;
							return 0;
							break;
						case OBJECT:
							/*recursion */
							//printf("this function doesn't support sub-object!");
							*dest = tmp_unit;
							return 0;
							break;
						case ARRAY:
							/*ignore array*/
							//printf("get struct ignore array!\n");
							*dest = tmp_unit;
							return 0;
							break;
						default:
							printf("error value type \n");
							return -1;
						}
						
					}
					tmp_unit = tmp_unit->bro;
				}
			}
			else
			{
				printf("No found this index in the array\n");
				return -1;
			}
		}
		printf("No found this index element in the array\n");
		return -1;	
	}
	
#if 0
	s32 CJson_parse::xget_element_by_name_and_index(void * node,s32 index,s8 * element_name,void** dest)
	{
		s32 i =0;
		if(node == NULL)
		{
			node = json_tree;
		}
		JSON_TREE_NODE_S * tmp = (JSON_TREE_NODE_S *)node;
		JSON_TREE_NODE_S * tmp_unit,*subnode;

		if(tmp && tmp->value_type == ARRAY)
		{
			if(tmp->chd)
			{
				tmp_unit = tmp->chd;
				while(tmp_unit)
				{
					if(i == index)
					{
						subnode = tmp_unit->chd;
						while(subnode)
						{
							if(strcmp(subnode->name,element_name) == 0)
							{
								switch(subnode->value_type)
								{
								case STRING:
								case NUMBER:
								case BOOL:
								case NULL_VALUE:
									*dest = subnode->value;
									return 0;
									break;
								case OBJECT:
									/*recursion */
									//printf("this function doesn't support sub-object!");
									*dest = subnode;
									return 0;
									break;
								case ARRAY:
									/*ignore array*/
									//printf("get struct ignore array!\n");
									*dest = subnode;
									return 0;
									break;
								default:
									printf("error value type \n");
									return -1;
								}
							}
							subnode = subnode->bro;
						}
						
					}
				tmp_unit = tmp_unit->bro;
					i++;
				}
			}
			else
			{
				printf("No found this index in the array\n");
				return -1;
			}
		}
		printf("No found this name array\n");
		return -1;
	}
#endif
	
	
	s32 CJson_parse::xget_element_by_index(void * node,s32 index,void** dest)
	{
		s32 i =0;
		if(node == NULL)
		{
			node = json_tree;
		}
		JSON_TREE_NODE_S * tmp = (JSON_TREE_NODE_S *)node;
		JSON_TREE_NODE_S * tmp_unit,*subnode;

		if(tmp && tmp->value_type == ARRAY)
		{
			if(tmp->chd)
			{
				tmp_unit = tmp->chd;
				while(tmp_unit)
				{
					if(i == index)
					{
						switch(tmp_unit->value_type)
						{
						case STRING:
						case NUMBER:
						case BOOL:
						case NULL_VALUE:
							*dest = tmp_unit->value;
							return 0;
							break;
						case OBJECT:
							/*recursion */
							//printf("this function doesn't support sub-object!");
							*dest = tmp_unit;
							return 0;
							break;
						case ARRAY:
							/*ignore array*/
							//printf("get struct ignore array!\n");
							*dest = tmp_unit;
							return 0;
							break;
						default:
							printf("error value type \n");
							return -1;
						}
						
					}
					tmp_unit = tmp_unit->bro;
					i++;
				}
			}
			else
			{
				printf("No found this index in the array\n");
				return -1;
			}
		}
		printf("No found this index element in the array\n");
		return -1;
	}

	s32 CJson_parse::xget_value_by_name(void * node,s8 * n,/*out*/s8 ** dest)
	{
		if(node == NULL)
		{
			node = json_tree;
		}
		JSON_TREE_NODE_S * tmp = ((JSON_TREE_NODE_S *)node)->chd;
		while(tmp)
		{
			if(tmp->value_type != OBJECT && tmp->value_type != ARRAY)
			{
				if(strcmp(tmp->name,n) == 0)
				{
					*dest = tmp->value;
					return 0;
				}
			}
			tmp = tmp->bro;
		}

		return -1;
	}

	
	s32 CJson_parse::xget_array_size(void * node)
	{
		s32 size =0;
		
		JSON_TREE_NODE_S * tmp = (JSON_TREE_NODE_S *)node;
		JSON_TREE_NODE_S * tmp_unit;
	
		if(tmp->value_type == ARRAY)
		{
			if(tmp->name == 0)
			{
				return 0;
			}
			if(tmp->chd)
			{
				tmp_unit = tmp->chd;
				if(tmp_unit->value_type == 0)
				{
					return 0;
				}
				size++;
				while(tmp_unit->bro)
				{
					tmp_unit = tmp_unit->bro;
					size++;
				}
				return size;
			}
		}
		
		return 0;
	}
	
	const JSON_TREE_NODE_S* CJson_parse::GetRootNode()
	{
		 return json_tree;
	}
};
