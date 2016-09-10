#ifndef _JSON_PARSE_H_
#define _JSON_PARSE_H_

#include "basic_type.h"
#include "sys_headers.h"

using namespace pure_baselib;

namespace pure_livegw
{

	#define JSON_NULL				0
	#define STRING					1
	#define NUMBER					2
	#define OBJECT					3
	#define ARRAY					4
	#define BOOL					5
	#define NULL_VALUE				6

	typedef struct json_tree_node	JSON_TREE_NODE_S;

	struct json_tree_node
	{
		s8					*name;
		u8					value_type;
		JSON_TREE_NODE_S	*chd;
		JSON_TREE_NODE_S	*bro;
		s8					*value;
	};

	class CJson_parse
	{
	public :
		CJson_parse(s8 *string);
		~CJson_parse();
	private:
		s8					*src;
		s32					len;
		JSON_TREE_NODE_S	*json_tree;
		s32					stack_lvl;

		JSON_TREE_NODE_S* new_json_node(void);
	
		s8* json_parse_object(s8 *string,json_tree_node *node);

		s8* jumpspace(s8 *);

		s8* json_parse_string(s8 *pos,s8 **dest_string);

		s8* json_parse_value(s8 *string,json_tree_node *node);

		s8* json_parse_array(s8 *string,json_tree_node *node);

		s8* json_parse_number(s8 *string,s8 **pvalue);

		s8** form_element_node(JSON_TREE_NODE_S *node, s8** dest, s32 destlen);

		JSON_TREE_NODE_S * find_node_by_name_and_type(JSON_TREE_NODE_S* node,s8 * n, u8 i_type);

		JSON_TREE_NODE_S* delete_node(JSON_TREE_NODE_S * jtn);
		
	public:
	
		void init(s8 *string);
		s32 do_parse(void);

		//s32 xget_element_by_name_and_index(void * node,s32 index,s8 * element_name,void** dest);
		void * xget_sub_object_by_name(void * node,s8 * n);
		s32 xget_value_by_name(void * node,s8 * n,s8 ** dest);
		s32 xget_array_size(void * node);
				
		s32 get_array_unit_by_name_and_index(s8 *,s32,s8**,s32);
		s32 get_value_by_name(s8 * n,s8 ** dest);
		s32 get_array_size_by_name(s8 *);
		s32 get_element_by_name_and_index(s8 * array_name,s32 index,s8 * element_name,void** dest);
		s32 xget_element_by_index(void * node,s32 index,void** dest);
		
		s32 xget_object_element_by_name(void * node,s8 * element_name,void** dest);
		const JSON_TREE_NODE_S* GetRootNode();
		
	};
};
#endif
