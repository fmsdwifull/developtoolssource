#ifndef _PCONF_H_
#define _PCONF_H_
/*
 *pconf 1.2.0
 *	parse conf
 *editor: pxh
 *date: 2013/07/16 16:05
 *tag:support array; ',' is not a valid value char.
 *
 */


/*
 *pconf 1.1.1
 *	parse conf
 *editor: pxh
 */
 
#include "basic_type.h"
namespace p_base
{

#define CONF_NAMEL 64
#define CONF_VARL 128

	typedef enum conf_node_type
	{
	empty_t = 0,
	char_t = 1,
	subnode_t,
	proc_mod_t,
	array_t,
	array_ele,
	cmd_t
	}CNT_E;
	
	typedef struct conf_node
	{
		char modn[CONF_NAMEL];
		char var[CONF_VARL];
		conf_node_type ntype;
		conf_node * smodlh;
		conf_node * next;
	}CN_S;

class pconf
{

private:

	char * buf;
	unsigned int buflen;
	int cfd;

	char* end;

	bool isparsed;
	int linenum;
	int level;
	
	int readfile();
	char * find_valid_name(char * p,char ** o,int * len);
	char * find_valid_value(char * p,char ** o,int * len);
	char * find_valid_array_value(char * p,char ** o,int * len);
		
	bool is_sub_node(char * p);
	bool is_array_node(char * p);

	char * jumpspace(char * p);
	char * jumpcomment(char * p);
	char * parse_main(char * p,CN_S * mc);
	char * parse_smodlh(char * p, CN_S * mc);
	char * parse_arraylh(char * p, CN_S * mc);
		

	static CN_S * delete_node(CN_S * node);
	
public:


	~pconf();
	int readconf(char *);
	int parse(CN_S * mch);

	static CN_S * new_node();
	static CN_S * get_proc_mod(CN_S * i_mc);
	static char * get_value_from_node(CN_S  * i_mc,const char * vn);
	static CN_S * get_submod_from_node(CN_S * i_mc,const char *mn);

	
	static CN_S * get_array_from_node(CN_S * i_mc,const char *mn);
	static s32 get_size_from_array(CN_S * i_mc);
	static char * get_value_from_array_by_index(CN_S * i_mc,int index);
		
	static void destroy(CN_S * i_head);
	
};


}
#endif
