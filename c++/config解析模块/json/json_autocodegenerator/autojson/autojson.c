#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "autojson.h"

//#define DEBUG
#ifdef DEBUG
#define JSON_printf(fmt,args...)   printf("%s(%d)%s "fmt,__FILE__,__LINE__,__FUNCTION__,##args);   
#else
#define JSON_printf		   printf
#endif 


static char *ep = NULL;
static uint32_t a_levels=0;
static uint32_t o_levels=0;
const unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };


const char *parse_value(JSON_NODE *item, const char *value);
static const char *skip(const char *p_in);


#define JSON_malloc 		malloc
#define JSON_free			free
#define TMPBUF_SIZE			512
#define MAXBUF_SIZE			65535

char gbuf[MAXBUF_SIZE];
int json_parse_flag, json_create_flag, json_readfile_flag, json_string_flag;
char *pfilename, *pstring;


JSON_NODE *JSON_New_Item(void)
{
	JSON_NODE* node = (JSON_NODE*)JSON_malloc(sizeof(JSON_NODE));
	if (node) 
	{		
		memset(node,0,sizeof(JSON_NODE));
	}
	return node;
}

//--------string----------------
char *parse_string(JSON_NODE *item, const char *str)
{
	char *ptr = (char *)str + 1;
	char *ptr2;
	char *out;
	int len = 0;
	uint32_t uc, uc2;



	if (*str != '\"') 
	{
		ep = (char *)str;
		return 0;
	}	
	
	while (*ptr!='\"' && *ptr && ++len)    //统计字符个数
	{
		if (*ptr++ == '\\')		ptr++;	//跳过转意字符
	}
	
	out = (char*)JSON_malloc(len+1);	
	if (out == NULL)
	{ 	
		printf("alloc memory failed\n");
		return 0;
	}

	ptr = (char *)str + 1;
	ptr2 = out;
	while (*ptr!='\"' && *ptr)
	{
		if (*ptr != '\\') 
		{
			*ptr2++ = *ptr++;
		}
		else
		{
			ptr++;
			switch (*ptr)
			{
				case 'b': *ptr2++='\b';		break;
				case 'f': *ptr2++='\f';		break;
				case 'n': *ptr2++='\n';		break;
				case 'r': *ptr2++='\r';		break;
				case 't': *ptr2++='\t';		break;
				case 'u':	 
					sscanf(ptr+1,"%4x",&uc);
					ptr += 4;	
					if ((uc>=0xDC00 && uc<=0xDFFF) || uc==0)	
						break;	
					
					if (uc>=0xD800 && uc<=0xDBFF)	
					{
						if (ptr[1]!='\\' || ptr[2]!='u')	
							break;	
						sscanf(ptr+3,"%4x",&uc2);
						ptr += 6;
						if (uc2<0xDC00 || uc2>0xDFFF)		
							break;	
						uc = 0x10000 + (((uc&0x3FF)<<10) | (uc2&0x3FF));
					}

					len = 4;
					if (uc < 0x80) 
					{
						len=1;
					}
					else if (uc<0x800) 
					{
						len=2;
					}
					else if (uc<0x10000) 
					{
						len=3; 
					}	
					ptr2 += len;
					
					switch (len) 
					{
						case 4: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 3: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 2: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 1: *--ptr2 =(uc | firstByteMark[len]);
					}
					ptr2 += len;
					break;
				default:  *ptr2++ = *ptr; 
						break;
			}
			ptr++;
		}
	}
	*ptr2=0;
	if (*ptr=='\"') 
		ptr++;
	item->value = out;
	item->type = JSON_String;
	
		
	return ptr;
}


//--------number-----------------
const char *parse_number(JSON_NODE *item, const char *num)
{
	float n=0, sign=1,scale=0, *pd;
	int subscale=0,signsubscale=1;

	if (*num=='-') sign=-1,num++;	
	if (*num=='0') num++;			
	if (*num>='1' && *num<='9')	
		do	
		{
			n=(n*10.0)+(*num++ -'0');	
		}
		while(*num>='0' && *num<='9');	
	if (*num=='.' && num[1]>='0' && num[1]<='9') 
	{	
		num++;		
		do	
		{
			n=(n*10.0)+(*num++ -'0'),scale--; 
		}
		while (*num>='0' && *num<='9');
	}	
	if (*num=='e' || *num=='E')		
	{	
		num++;
		if (*num=='+') 	
			num++;	
		else if (*num=='-') 
		{
			signsubscale=-1,num++;		
		}
		while(*num>='0' && *num<='9') 
		subscale = (subscale*10)+(*num++ - '0');	
	}

	n=sign*n*powf(10.0,(scale+subscale*signsubscale));	

	pd = (float *)&item->value;	
	*pd = n;
	item->type=JSON_Number;
	return num;
} 


//--------array------------------
char *parse_array(JSON_NODE *item, const char *value)
{
	static uint32_t levels = 0;
	levels ++;
	a_levels++;

	JSON_NODE *child;
	if (*value != '[')	
	{
		ep = (char *)value;
		return 0;
	}

	item->type = JSON_Array;
	value = skip(value+1);
	if (*value == ']') 
	{
		return (char *)value+1;	
	}

	item->child=child=JSON_New_Item();
	if (!item->child) 
	{	
		printf("alloc memory failed\n");
		return 0;	
	}

	value = skip(parse_value(child,skip(value)));	
	if (!value)
	{ 
		return 0;
	}

	while (*value == ',')
	{
		JSON_NODE *new_item;
		if (!(new_item=JSON_New_Item())) 
		{			
			printf("alloc memory failed\n");
			return 0; 	
		}
		child->next = new_item;
		new_item->prev = child;
		child = new_item;
		value = skip(parse_value(child,skip(value+1)));
		if (!value) 
		{
			return 0;	
		}
	}

	levels--;				//-----------------add
	a_levels--;

	if (*value==']') 
	{
		return (char *)value+1;	
	}	
	ep = (char *)value;
	return 0;	
}

//--------object----------------
char *parse_object(JSON_NODE *item, const char *value)
{
	JSON_NODE *child;

	o_levels++;

	if (*value != '{')	
	{
		ep = (char *)value;
		return 0;
	}	
	
	item->type = JSON_Object;
	value = skip(value+1);
	if (*value == '}') 
	{
		return (char *)value + 1;	
	}	
	
	item->child=child=JSON_New_Item();

	if (!item->child) 
	{
		printf("alloc memory failed\n");
		return 0;		
	}
	value = skip(parse_string(child,skip(value)));
	if (!value) 
	{
		return 0;
	}
	child->name = child->value;
	child->value = 0;
	if (*value!=':') 
	{
		ep = (char *)value;
		return 0;
	}
	value = skip(parse_value(child,skip(value+1)));
	if (!value) 
	{
		return 0;
	}
	
	while (*value==',')
	{
		JSON_NODE *new_item;
		if (!(new_item=JSON_New_Item()))	
		{
			printf("alloc memory failed\n");
		 	return 0; 
		}
		child->next = new_item;
		new_item->prev = child;
		child = new_item;
		value = skip(parse_string(child,skip(value+1)));
		if (!value) 
		{
			return 0;
		}
		child->name = child->value;
		child->value = 0;
		if (*value!=':') 
		{
			ep = (char *)value;
			return 0;
		}
		value = skip(parse_value(child,skip(value+1)));	
		if (!value) 
		{		
			return 0;
		}
	}
		
	o_levels--;

	if (*value=='}') 
	{	
		return (char *)value+1;	
	}	
	ep = (char *)value;
	return 0;	
}

const char *parse_value(JSON_NODE *item, const char *value)
{
	if (value == NULL)						
	{
		return 0;	
	}
	if (*value == '\"')				
	{ 
		return parse_string(item,value); 
	}
	if (*value=='-' || (*value>='0' && *value<='9'))	
	{ 
		return parse_number(item,value); 
	}
	if (*value == '[')				
	{ 
		return parse_array(item,value); 
	}
	if (*value == '{')				
	{ 	
		return parse_object(item,value); 
	}

	if (strncmp(value,"null",4) == 0)	
	{ 
		item->type = JSON_NULL;  
		return value + 4; 
	}
	if (strncmp(value,"false",5) == 0)	
	{ 
		item->type = JSON_False; 
		item->value = (char *)0;
		return value + 5; 
	}
	if (strncmp(value,"true",4) == 0)	
	{ 
		item->type = JSON_True; 
		item->value = (char *)1;	
		return value + 4; 
	}
	ep = (char *)value;
	return 0;	
}

static const char *skip(const char *p_in)   // 判断字符是不是空格或者回车换行
{
	while (p_in && *p_in && (unsigned char)*p_in<=32) 
	{
		p_in++; 
	}
	return p_in;
}

void JSON_Delete(JSON_NODE *c)
{
	JSON_NODE *next;
	while (c)
	{
		next = c->next;
		if (!(c->type&JSON_IsReference) && c->child) 
		{		
			JSON_Delete(c->child);
		}			
		if (!(c->type&JSON_IsReference) && c->value) 
		{
			JSON_free(c->value);
		}		
		if (c->value)
		{ 
			JSON_free(c->name);
		}		
		JSON_free(c);
		c = next;
	}
}

JSON_NODE *JSON_ParseWithOpts(const char *value,const char **return_parse_end,int require_null_terminated)
{
	const char *end=0;
	JSON_NODE *root = JSON_New_Item();
	ep = NULL;
	if (root == NULL) 
	{
		printf("alloc memory failed\n");
		return 0;       
	}

	end = parse_value(root,skip(value));


	if (!end)	
	{
		JSON_Delete(root);
		printf("json string error\n");
		return 0;
	}	

	if (require_null_terminated) 
	{
		end = skip(end);
		if (*end) 
		{
			JSON_Delete(root);
			ep = (char *)end;
			return 0;
		}
	}
	if (return_parse_end) 
	{	
		*return_parse_end = end;
	}	
	return root;
}


JSON_NODE *JSON_Parse(const char *value) 
{
	return JSON_ParseWithOpts(value,0,0);
}



int traveral_array(JSON_NODE *node,int depth,int num,char *str)
{
	static uint32_t arr_count=0;	
	int numentries=0,child_num=0,i;
	char tmp_str[50];
	JSON_NODE *child = node->child;

	while(child)
	{
		numentries++;
		child = child->next;
	}

	arr_count++;
	child = node->child;
	while (child != NULL)
	{
		printf("\n");
		printf("json.xget_element_by_index(%s,%d,(void **)&parray);\n", str, child_num);
		memset(tmp_str, 0, sizeof(tmp_str));	
		sprintf(tmp_str,"%s","parray");	
		find_type(child,depth,child_num,tmp_str);
		child = child->next;
		child_num++;
	}
}

int traveral_object(JSON_NODE *node,int depth,int num, char *str)
{
	int numentries=0,child_num=0,i;
	static uint32_t obj_count=0;
	JSON_NODE *child = node->child;
	JSON_NODE *pnode;
	char tmp_str[50];
	char *var_name,(*pname)[50];

	while(child)
	{
		printf("s8 *var_%s;\n",child->name);
		numentries++;
		child = child->next;
	}		
	var_name = (char *)malloc(sizeof(50*numentries));
	memset(var_name, 0, sizeof(50*numentries));
	pname = var_name;

	pnode = node->child;
	for (i=0; i<numentries; i++)
	{
		if (pnode->name != NULL)
		{	
			if (depth == 1)
			{
				snprintf((char*)pname[i],50,"var_%s",pnode->name);
				printf("json.xget_object_element_by_name(NULL,(s8*)\"%s\",(void **)&%s);\n",pnode->name,(char *)pname[i]);
				
			}
			else
			{
				snprintf((char *)pname[i],50,"var_%s",pnode->name);
				printf("json.xget_object_element_by_name((void *)%s,(s8*)\"%s\",(void **)&%s);\n",str,pnode->name,(char *)pname[i]);
			}
		}
		pnode = pnode->next;
	}
	free(var_name);

	obj_count++;
	child = node->child;
	while (child != NULL)
	{
		memset(tmp_str, 0, sizeof(tmp_str));	
		sprintf(tmp_str, "var_%s",child->name);	
		find_type(child,depth,child_num,tmp_str);
		child = child->next;
		child_num++;
	}
}

int find_type(JSON_NODE *node,int depth,int num,char *str)
{
	switch ((node->type)&255)
	{
		case JSON_NULL:					
					break;
		case JSON_False:				
					break;
		case JSON_True:		 			
					break;
		case JSON_Number:				
					break;
		case JSON_String:			
					break;
		case JSON_Array:	
						traveral_array(node,depth+1,num,str);		
					break;
		case JSON_Object:	
						traveral_object(node,depth+1,num,str);		
					break;
	}
	return 0;
}

//--------------------------------------add
int add_array(JSON_NODE *node,int depth)
{
	static uint32_t arr_count=0;	
	char buf1[50],buf2[50];
	int numentries=0,child_num=0;
	JSON_NODE *child = node->child;

	while(child)
	{
		numentries++;
		child = child->next;
	}
		
	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));
	if (node->name != NULL)
	{
		sprintf(buf1,"(s8*)\"%s\"",node->name);
	}	
	else
	{
		strcpy(buf1,"NULL");
	}
	if (node->value != NULL)
	{
		sprintf(buf2,"(s8*)\"%s\"",node->value);
	}	
	else
	{
		strcpy(buf2,"NULL");
	}
		
	printf("\njs->add_array(%s,%s);\n",buf1, buf2);

	arr_count++;
	child = node->child;
	while (child != NULL)
	{
		add_type(child,depth);
		child = child->next;
		child_num++;
	}
		printf("js->back_top();\n");
}


int add_object(JSON_NODE *node,int depth)
{
	char buf1[50],buf2[50];
	int numentries=0,child_num=0,i;
	static uint32_t obj_count=0;
	JSON_NODE *child = node->child;
	JSON_NODE *pnode;

	while(child)
	{
		numentries++;
		child = child->next;
	}		

	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));
	if (node->name != NULL)
	{
		sprintf(buf1,"(s8*)\"%s\"",node->name);
	}	
	else
	{
		strcpy(buf1,"NULL");
	}
	if (node->value != NULL)
	{
		sprintf(buf2,"(s8*)\"%s\"",node->value);
	}	
	else
	{
		strcpy(buf2,"NULL");
	}
	printf("\njs->add_object(%s,%s);\n",buf1,buf2);

	obj_count++;
	child = node->child;
	while (child != NULL)
	{
		add_type(child,depth);
		child = child->next;
		child_num++;
	}
		printf("js->back_top();\n");
}
int add_type(JSON_NODE *node,int depth)
{
	switch ((node->type)&255)
	{
		case JSON_NULL:					
					break;
		case JSON_False:				
					break;
		case JSON_True:		 			
					break;
		case JSON_Number:				
					printf("js->add_number((s8*)\"\",(s8*)\"\")\n");
					break;
		case JSON_String:			
					printf("js->add_string((s8*)\"%s\",(s8*)\"%s\");\n",(node->name==NULL? "":node->name), (node->value==NULL?"":node->value));
					break;
		case JSON_Array:	
						add_array(node,depth+1);		
					break;
		case JSON_Object:	
						add_object(node,depth+1);		
					break;
	}
	return 0;
}


static int json_get_options(int argc, char **argv)
{
	unsigned char *p;
	int i;

	for (i=1; i<argc; i++)
	{
		p = (unsigned char *)argv[i];
		if (*p++ != '-')
		{
			printf("invalid option: \"%s\"",argv[i]);
			return -1;
		}
		
		while (*p)
		{
			switch (*p++)
			{
				case 'p':
					json_parse_flag = 1;		
					break;
				case 'c':
					json_create_flag = 1;
					break;
				case 'f':
					if (*p)
					{
						goto next;
					}
					if (argv[++i])
					{
						pfilename = (unsigned char *)argv[i];
						json_readfile_flag = 1;
						goto next;
					}
					printf("option \"-f\" requires file name\n");
					return -1;
					break;
				case 's':
					if (*p)
					{
						goto next;
					}
					if (argv[++i])
					{
						json_string_flag = 1;
						pstring = (unsigned char *)argv[i];
						goto next;
					}
					printf("option \"-s\" requires json string\n");
					return -1;
					
					break;
				default:
					printf("invalid options :\"%c\"\n",*p);
					return -1;
					break;
			}
		}
		next:
			continue;

	}

	return 0;

}

int readfile()
{
	int i;
	FILE *fd;
	char tmpbuf[TMPBUF_SIZE];

	fd = fopen(pfilename, "r");	
	if (fd == NULL)
	{
		printf("文件打开失败！\n");
		return -1;
	}
	
	memset(gbuf, 0, MAXBUF_SIZE);	
	while(fgets(tmpbuf,TMPBUF_SIZE,fd)!=NULL && tmpbuf[0]!='\0')
	{
		strcat(gbuf,tmpbuf);
	}
	fclose(fd);
	return 0;
}


int main(int argc, char *argv[])
{

	JSON_NODE *root;
	if (argc < 3)
	{
		printf("invalid option  missing json string\nUsage:command  json string\n");
		return -1;
	}


	if (json_get_options(argc,argv) != 0)
	{
		return -1;
	}
	
	if (json_readfile_flag == 1)
	{
		if (readfile() != 0)
		{
			return -1;
		}
		root = JSON_Parse(gbuf);
	}
	else if(json_string_flag == 1)
	{
		root = JSON_Parse(pstring);
	}
	else
	{
		printf("can't find json string\n");
		return -1;
	}
	
	if (root == NULL)
	{
		printf("parse json string error occurred int character \'%c\' \n",*ep);
		return -1;
	}
	if (json_parse_flag == 1)
	{
		printf("\n\n");
		printf("%s\n","CJson_parse json(response);");
		printf("%s\n","json.do_parse();");
		printf("%s\n","char *parray;");
		find_type(root,0,0,NULL);
		printf("\n\n");
	}
	if (json_create_flag == 1)
	{
		printf("\n\n");
		printf("s8* buf = new s8[16384];\n");		
		printf("memset(buf,0,16384);\n");
		printf("CJson *js = new CJson(buf,16384);\n");
		printf("if (NULL == js)\n");
		printf("{\n");
		printf("printf(\"[%%s, %%d] new json object error!\\n\", __FILE__, __LINE__);\n");
		printf("return FAILURE;\n");
		printf("}\n");
		printf("js->init();\n");
		add_type(root,0);
		printf("\n\n");
	}
	
	return 0;
}
