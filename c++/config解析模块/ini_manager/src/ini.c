/**
 * @file ini.c
 * @authro richard <richard.yao2010@gmail.com>
 * @date 2010-01-02
 */

#include "ini.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INI_NAME_LENGTH       128
#define MAX_INI_VALUE_LENGTH      1024
#define MAX_TOKEN_LENGTH          MAX_INI_VALUE_LENGTH
#define INI_INIT_SIZE             1
#define INI_INCREMENT             1

typedef struct {
	char name[MAX_INI_NAME_LENGTH];
	char value[MAX_INI_VALUE_LENGTH];
} ini_item_t;

typedef struct {
	ini_item_t *p_item_list;
	unsigned long current_item_count;
	unsigned long max_item_count;
} ini_t;

static ini_t g_ini = {0};

static int get_token(FILE *p_file, char *p_buffer, int buffer_size);

int ini_init()
{
	g_ini.p_item_list = (ini_item_t *)malloc(INI_INIT_SIZE * sizeof(ini_item_t));
	if (g_ini.p_item_list == NULL) {
		return -1;
	}
	memset(g_ini.p_item_list, 0, sizeof(INI_INIT_SIZE * sizeof(ini_item_t)));
	g_ini.current_item_count = 0;
	g_ini.max_item_count = INI_INIT_SIZE;
	return 0;
}

int ini_uninit()
{
	if (g_ini.p_item_list != NULL) {
		free(g_ini.p_item_list);
		g_ini.p_item_list = NULL;
	}
	return 0;
}

int ini_add_file(const char *p_file_name)
{
	FILE *p_file = fopen(p_file_name, "r");	
	char tokbuf[MAX_TOKEN_LENGTH] = {0};
	if (p_file == NULL) {
		return -1;
	}

	int ret_val;
	do {
		if (g_ini.current_item_count >= g_ini.max_item_count) {
			g_ini.p_item_list = (ini_item_t *)realloc(g_ini.p_item_list,
					(g_ini.max_item_count + INI_INCREMENT) * sizeof(ini_item_t));
			if (g_ini.p_item_list == NULL) {
				return -1;
			}
			g_ini.max_item_count += INI_INCREMENT;
		}

		memset(g_ini.p_item_list + g_ini.current_item_count, 0, sizeof(ini_item_t));

		ret_val = get_token(p_file, tokbuf, MAX_INI_NAME_LENGTH);
		if (ret_val == 0) {
			strcpy(g_ini.p_item_list[g_ini.current_item_count].name, tokbuf);

			ret_val = get_token(p_file, tokbuf, 2);
			if (ret_val == 0) {
				if (strcmp(tokbuf, "=") != 0) {
					return -1;
				}

				ret_val = get_token(p_file, tokbuf, MAX_INI_VALUE_LENGTH);
				if (ret_val == 0) {
					strcpy(g_ini.p_item_list[g_ini.current_item_count].value, tokbuf);
				}
				++g_ini.current_item_count;
			} else {
				return -1;
			}
		}
	} while (ret_val != EOF && ret_val != 1);
	if (ret_val == 1) {
		return -1;
	}

	return 0;
}

int ini_get_string(const char *p_name, char **pp_value)
{
	int i = 0;
	for (i = 0; i != g_ini.current_item_count; ++i) {
		if (strcmp(g_ini.p_item_list[i].name, p_name) == 0) {
			break;
		}
	}
	if (i == g_ini.current_item_count) {
		return -1;
	}
	else {
		*pp_value = g_ini.p_item_list[i].value;
		return 0;
	}
}

static int get_token(FILE *p_file, char *p_buffer, int buffer_size)
{
	int c = 0;
	char state = 1;
	char w = 0;
	int result = 0;
	int i = 0;

	do {
		if ((c = getc(p_file)) == EOF) {
			state = 0;
			w = 0;
			result = EOF;
		}
		switch (state) {
		case 1:
			switch (c) {
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				break;
			case '#':
				state = 2;
				break;
			case '=':
				state = 0;
				w = 1;
				break;
			case '"':
				state = 3;
				w = 0;
				break;
			default:
				state = 4;
				w = 1;
				break;
			}
			break;
		case 2:
			if (c == '\n') {
				state = 1;
			}
			break;
		case 3:
			if (c == '\\') {
				state = 5;
				w = 0;
			}
			else if (c == '"') {
				state = 0;
				w = 0;
			}
			else {
				w = 1;
			}
			break;
		case 4:
			switch (c) {
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					state = 0;
					w = 0;
					break;
				case '#':
				case '"':
				case '=':
					ungetc(c, p_file);
					state = 0;
					w = 0;
					break;
				default:
					w = 1;
					break;		
			}
			break;
		case 5:
			w = 1;
			state = 3;
			break;
		}
		if (w) {
			if (i + 1 <	buffer_size) {
				p_buffer[i++] = c;
			} else {
				state = 0;
				result = 1;
			}
		}
	} while(state != 0);
	p_buffer[i] = 0;
	return result;
}

