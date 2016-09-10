#include "pconf.h"
#include "sys_headers.h"

#include "string/p_string.h"

using namespace p_base;


bool bvalidname[128]=
{
/*0*/0,0,0,0,0,0,0,0,
/*1*/0,0,0,0,0,0,0,0,
/*2*/0,0,0,0,0,0,0,0,
/*3*/0,0,0,0,0,0,0,0,
/*4*/0,0,0,0,0,0,0,0,
/*5*/0,0,0,0,0,0,0,0,
/*6*/1,1,1,1,1,1,1,1,
/*7*/1,1,1,0,0,0,0,0,
/*8*/1,1,1,1,1,1,1,1,
/*9*/1,1,1,1,1,1,1,1,
/*A*/1,1,1,1,1,1,1,1,
/*B*/1,1,1,0,0,0,0,1,
/*C*/0,1,1,1,1,1,1,1,
/*D*/1,1,1,1,1,1,1,1,
/*E*/1,1,1,1,1,1,1,1,
/*F*/1,1,1,0,0,0,0,0	
};

bool bvalidvalue[128]=
{
/*0*/0,0,0,0,0,0,0,0,
/*1*/0,0,0,0,0,0,0,0,
/*2*/0,0,0,0,0,0,0,0,
/*3*/0,0,0,0,0,0,0,0,
/*4*/0,1,1,1,1,1,1,1,
/*5*/1,1,1,1,0,1,1,1,
/*6*/1,1,1,1,1,1,1,1,
/*7*/1,1,1,0,1,1,1,1,
/*8*/1,1,1,1,1,1,1,1,
/*9*/1,1,1,1,1,1,1,1,
/*A*/1,1,1,1,1,1,1,1,
/*B*/1,1,1,0,1,0,1,1,
/*C*/1,1,1,1,1,1,1,1,
/*D*/1,1,1,1,1,1,1,1,
/*E*/1,1,1,1,1,1,1,1,
/*F*/1,1,1,1,1,1,1,0
};

const char * keyword_list[] = 
{
	"proc",
	NULL
};

static CNT_E check_keyword(char * name,int len)
{
	for(int i =0;keyword_list[i]!= NULL;i++)
	{
		if(len == strlen(keyword_list[i]) && memcmp(name,keyword_list[i],len) == 0)
		{
			return CNT_E(proc_mod_t + i);
		}
	}
	return char_t;
}


static bool validname(char *p)
{
	if(*p > 127)
	{
		return false;
	}
	else
	{
		return bvalidname[*p];
	}
}

static bool validvalue(char * p)
{
	if(*p > 127)
	{
		return false;
	}
	else
	{
		return bvalidvalue[*p];
	}
}

/*
*read file fd to buffer
*/
//读取文件到内存中
int pconf::readfile()
{
	off_t total = 0;
	off_t block_size = 1024;	
	off_t bytes_read = 0;
	
	while((bytes_read = read(cfd,buf+total,block_size))>0)
	{	
		if(bytes_read == 1024)
		{
			buf = (char *)realloc(buf,buflen+1024);
			memset(buf+total+1024,0,1024);
		}
		total += bytes_read;
	}
	if(bytes_read < 0)
	{
		perror("read error: ");
		return bytes_read;
	}
	end = buf+total;
	linenum = 1;
	level = 0;
	isparsed =false;
	return 0;		
}

//跳过"#"，返回指针位置
char * pconf::jumpcomment(char *p)
{

	while(*p == '#')
	{

		while((p < end) && (*p != '\n'))
		{
			p++;
		}
		if(p >=end)
		{
			return p;
		}
		p++; 
		linenum++;
	}
	return p;
}

//跳过一些特殊符号，返回指针位置
char * pconf::jumpspace(char * p)
{
	char ch;
	while(p<end)
	{
		ch = *p;
		switch (ch)
		{
			case ' ':
			case '\t':
			case '\r':
				p++; 
				break;
			case '\n':
				p++; 
				linenum++;
				break;
			case '#':
				p = jumpcomment(p);
				break;
			default:
				return p;
		}
		
	}
	return p;
}

/*
*return the char to parse,arg2: the valid name string arg3: length;
*/
char * pconf::find_valid_name(char * p,char ** o,int * len)
{
	p = jumpspace(p);
	if(p>=end)
	{
		return p;
	}

	if(!validname(p))
	{
		printf("include an illegal char,line:%d char %c\n",linenum,*p);
		*o = NULL;
		*len = 0;
		return p;
	}

	char * name = p;
	
	while(p<end && validname(p))
	{
		p++; 	
	}

	*o = name;
	*len = p-name;
	return p;

}

char * pconf::find_valid_value(char * p,char ** o,int * len)
{
	p = jumpspace(p);
	if(p>=end)
	{
		return p;
	}

	if(!validvalue(p))
	{
		printf("include an illegal char  ,line:%d char %c\n",linenum,*p);
		*o = NULL;
		*len = 0;
		return p;
	}

	char * name = p;
	
	while(p<end && validvalue(p))
	{
		p++; 	
	}

	*o = name;
	*len = p-name;

	p = jumpspace(p);

	if(*p != ';')
	{
		printf("expect a ';',line:%d char %c\n",linenum,*p);
		*o = NULL;
		*len = 0;
		return p;	
	}
	
	p++;
	return p;

}

char * pconf::find_valid_array_value(char * p,char ** o,int * len)
{
	p = jumpspace(p);
	if(p>=end)
	{
		return p;
	}

	if(!validvalue(p))
	{
		printf("include an illegal char  ,line:%d char %c\n",linenum,*p);
		*o = NULL;
		*len = 0;
		return p;
	}

	char * name = p;
	
	while(p<end && validvalue(p))
	{
		p++; 	
	}

	*o = name;
	*len = p-name;

	p = jumpspace(p);

	return p;

}



bool pconf::is_sub_node(char * p)
{
	p = jumpspace(p);
	if(p<end)
	{
		if(*p == '{')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

}

bool pconf::is_array_node(char * p)
{
	p = jumpspace(p);
	if(p<end)
	{
		if(*p == '[')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

}


/*in:arg1: buf position,arg2:CN_S * the last CN_S which had new
*out:buf postion
*/
char * pconf::parse_main(char * p,CN_S * mc)
{
	bool no_centent = true;
	for(;p<end && p != NULL;)
	{
		char * name;
		int name_len;
		
		p = find_valid_name(p,&name,&name_len);
		
		if(no_centent == true && name == NULL)
		{
			printf("empty configuration file\n");
			return NULL;
		}
		else
		{
			no_centent = true;
		}

		if(p>=end)
		{
			return p;
		}
	

		if(is_sub_node(p))
		{
			rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
			mc->ntype = subnode_t;
			mc->smodlh = new_node();
			assert(mc->smodlh!=NULL);
			p = jumpspace(p);
			p += 1;			//jump '{'
			p = parse_smodlh(p,mc->smodlh);
		}
		else if(is_array_node(p))
		{
			rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
			mc->ntype = array_t;
			mc->smodlh = new_node();
			assert(mc->smodlh!=NULL);
			p = jumpspace(p);
			p += 1;			//jump '{'
			p = parse_arraylh(p,mc->smodlh);
		}
		else
		{
			//not a submod,check keyword
			mc->ntype = check_keyword(name,name_len);
			char * value = NULL;
			int value_len = 0;
			
			char * mod_name = NULL;
			int mod_len = 0;
			switch(mc->ntype)
			{
			case char_t:
				rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
	
				p = find_valid_value(p,&value,&value_len);
				if(value == NULL || p>= end)
				{
					printf("except a value \n");
					return NULL;
				}
				
				rc_strncpy(mc->var,CONF_VARL,value,value_len);
		
				break;
			case proc_mod_t:
				p = find_valid_name(p,&mod_name,&mod_len);				
				if(mod_name == NULL)
				{
					printf("empty configuration file\n");
					return NULL;
				}
				
				if(p>=end)
				{
					printf("uncompleted line,line:%d\n",linenum);
					return NULL;
				}
				rc_strncpy(mc->modn,CONF_NAMEL,mod_name,mod_len);
				mc->smodlh = new_node();
				assert(mc->smodlh!=NULL);
				p = jumpspace(p);
				if(*p != '{')
				{
					printf("except '{' \n");
					return NULL;
				}
				p++;
				p = parse_smodlh(p,mc->smodlh);
				break;
			default:
				name[name_len] = '\0';
				printf("unsupport keyword:%s,line:%d\n",name,linenum);
				return NULL;
			}
			
		}
		mc->next = new_node();
		assert(mc->next != NULL);
		mc = mc->next;
	}
	return p;
}

//static new node
CN_S * pconf::new_node()
{
	CN_S * p =  new CN_S;
	memset(p,0,sizeof(CN_S));
	return p;
}

/*parse submod*/
char * pconf::parse_smodlh(char * p, CN_S * mc)
{
	level++;
	for(;p<end && p != NULL;)
	{
		char * name;
		int name_len;
		p = jumpspace(p);

		if(p>=end)
		{
			printf("except \'}\' \n");
			return NULL;
		}
		if(*p == '}')
		{
			p++;
			level --;
			return p;
		}
		
		p = find_valid_name(p,&name,&name_len);
		if(name == NULL)
		{
			printf("uncompleted configuration file\n");
			return NULL;
		}
		
		if(p>=end)
		{
			printf("uncompleted line,line:%d\n",linenum);
			return NULL;
		}
		
		if(is_sub_node(p))
		{
			
			rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
			mc->ntype = subnode_t;
			mc->smodlh = new_node();
			assert(mc->smodlh!=NULL);
			p = jumpspace(p);
			p += 1;			//jump '{'
			p = parse_smodlh(p,mc->smodlh);
		}
		else if(is_array_node(p))
		{
			rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
			mc->ntype = array_t;
			mc->smodlh = new_node();
			assert(mc->smodlh!=NULL);
			p = jumpspace(p);
			p += 1;			//jump '{'
			p = parse_arraylh(p,mc->smodlh);
		}
		else
		{
			//not a submod,check keyword
			mc->ntype = check_keyword(name,name_len);
			char * value = NULL;
			int value_len = 0;
			switch(mc->ntype)
			{
			case char_t:
				rc_strncpy(mc->modn,CONF_NAMEL,name,name_len);
		
				p = find_valid_value(p,&value,&value_len);
				if(value == NULL || p>= end)
				{
					printf("except a value \n");
					return NULL;
				}
				
				rc_strncpy(mc->var,CONF_VARL,value,value_len);
		
				break;
			case proc_mod_t:
				
			default:
				name[name_len] = '\0';
				printf("unsupport keyword:%s,line:%d\n",name,linenum);
				return NULL;
			}
			
		}
		mc->next = new_node();
		assert(mc->next != NULL);
		mc = mc->next;
	}
	return p;
}


/*parse array*/
char * pconf::parse_arraylh(char * p, CN_S * mc)
{
	level++;
	bool common_need = false;
	for(;p<end && p != NULL;)
	{
		char * value = NULL;
		int value_len;
		p = jumpspace(p);

		if(p>=end)
		{
			printf("except \']\' \n");
			return NULL;
		}
		if(*p == ']')
		{
			p++;
			level --;
			return p;
		}

		if(common_need)
		{
			if(*p != ',')
			{
				printf("except \',\' line:%d\n",linenum);
				return NULL;
			}
			p++;	//jump ','
		}

		
		
		p = find_valid_array_value(p,&value,&value_len);
		common_need = true;
		
		if(value == NULL)
		{
			printf("uncompleted configuration file\n");
			return NULL;
		}
		
		if(p>=end)
		{
			printf("uncompleted line,line:%d\n",linenum);
			return NULL;
		}

		if(value == NULL || p>= end)
		{
			printf("except a value \n");
			return NULL;
		}

		rc_strncpy(mc->var,CONF_VARL,value,value_len);
		mc->ntype = array_ele;
		
		mc->next = new_node();
		assert(mc->next != NULL);
		mc = mc->next;
	}
	return p;
}
	

/*
*in:conf file name 
*out: S/F
*/
int pconf::readconf(char * fn)
{
	if((cfd = open(fn,O_RDONLY)) == -1) 
	{
		printf("Open %s Error:%s\n",fn,strerror(errno));
		return -1;
	}

	buf = (char *)malloc(1024*256);
	memset(buf,0,1024*256);
	buflen = 1024*256;
	if(buf == NULL)
	{
		printf("buf new failed \n");
		return -1;
	}
	int ret = 0;
	if((ret = readfile()) < 0 )
	{
		return ret;
	}

	return 0;
	
}

int pconf::parse(CN_S * mch)
{
	char * p = parse_main(buf,mch);
	if(p == end && level == 0)
	{
		isparsed = true;
	}
	else if(level >0)
	{
		printf("unexcept '}',line:%d\n",linenum);
	}
	close(cfd);
	return isparsed?0:-1;
}

//static get proc mod_node
CN_S * pconf::get_proc_mod(CN_S * i_mc)
{
	
	while(i_mc != NULL)
	{
		if(i_mc->ntype == proc_mod_t)
		{
			return i_mc;
		}
		i_mc = i_mc->next;
	}

	return NULL;	
}

//static get char* from mod
char * pconf::get_value_from_node(CN_S  * i_mc,const char * vn)
{
	while(i_mc != NULL)
	{
		if(i_mc->ntype == char_t)
		{
			if(STRMATCH(vn,i_mc->modn))
			{
				return i_mc->var;
			}
		}
		i_mc = i_mc->next;
	}

	return NULL;	
}

//static get submod from node
CN_S * pconf::get_submod_from_node(CN_S * i_mc,const char *mn)
{
	while(i_mc != NULL)
	{
		if(i_mc->ntype == subnode_t)
		{
			if(STRMATCH(mn,i_mc->modn))
			{
				return i_mc->smodlh;
			}
		}
		i_mc = i_mc->next;
	}

	return NULL;	
}


CN_S * pconf::get_array_from_node(CN_S * i_mc,const char *mn)
{
	while(i_mc != NULL)
	{
		if(i_mc->ntype == array_t)
		{
			if(STRMATCH(mn,i_mc->modn))
			{
				return i_mc;
			}
		}
		i_mc = i_mc->next;
	}

	return NULL;	
}

s32 pconf::get_size_from_array(CN_S * i_mc)
{
	int size = 0;
	CN_S * psub = NULL;
	if(i_mc != NULL)
	{
		if(i_mc->ntype == array_t)
		{
			psub = i_mc->smodlh;
			while(psub->ntype == array_ele)
			{
				psub = psub->next;
				size++;
			}
			
		}
	}

	return size;
}

char * pconf::get_value_from_array_by_index(CN_S * i_mc,int index)
{
	int inpos = 0;
	CN_S * psub = NULL;
	if(i_mc != NULL)
	{
		if(i_mc->ntype == array_t)
		{

			psub = i_mc->smodlh;
			while(psub->ntype == array_ele)
			{
				if(index == inpos)
				{
					return psub->var;
				}
				psub = psub->next;
				inpos++;
			}		
		}
	}
	return NULL;
}



//static destroy
void pconf::destroy(CN_S * i_head)
{
	delete_node(i_head);
	return;
}

//static delete
CN_S * pconf::delete_node(CN_S * node)
{
	if(node == NULL)
		return NULL;
	
	if(node->smodlh)
	{
		node->smodlh = delete_node(node->smodlh);
	}
	if(node->next)
	{
		node->next = delete_node(node->next);
	}
	delete node;
	
	return NULL;
}

pconf::~pconf()
{

	if(buf)
	{
		free(buf);
		buf = NULL;
	}
}


