/**
 * @file ini.h
 * @author richard <richard.yao2010@gmail.com>
 * @date 2009-12-31
 */

#ifndef _INI_H_2009_12_31
#define _INI_H_2009_12_31

int ini_init();
int ini_add_file(const char *p_file_name);
int ini_get_string(const char *p_name, char **pp_value);
int ini_uninit();

#endif 
