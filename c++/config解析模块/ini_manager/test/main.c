#include "ini.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if (ini_init() != 0) {
		printf("ERROR: ini_init().\n");
		return -1;
	}

	if (ini_add_file("./config.ini") != 0) {
		printf("ERROR: ini_add_file.\n");
		ini_uninit();
		return -1;
	}
	
	char *p_value;
	if (ini_get_string("port", &p_value) != 0) {
		printf("ERROR: ini_get_value.\n");
		ini_uninit();
		return -1;
	}
	printf("port = %s\n", p_value);
	if (ini_get_string("path", &p_value) != 0) {
		printf("ERROR: ini_get_value.\n");
		ini_uninit();
		return -1;
	}
	printf("path = %s\n", p_value);

	if (ini_uninit() != 0) {
		printf("ERROR: ini_uninit().\n");
		return -1;
	}

	return 0;
}
