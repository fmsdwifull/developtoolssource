#ifndef __AUTOJSON_H
#define __AUTOJSON_H

#define JSON_False 		0
#define JSON_True		1
#define JSON_NULL		2
#define JSON_Number		3
#define JSON_String		4
#define JSON_Array		5
#define JSON_Object   	6

#define JSON_IsReference 256

typedef struct json_node
{
	struct json_node *next, *prev;
	struct json_node *child;
	
	uint8_t  type;   	//类型
	
	char *name;		//名字


	char *value;	 //值

}JSON_NODE;

#endif
