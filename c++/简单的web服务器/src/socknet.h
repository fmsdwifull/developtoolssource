#ifndef  SOCK_N_H
#define  SOCK_N_H


//namespace baselib
//{
extern "C" {
	#include    <stdio.h>
	#include    <unistd.h>
	#include    <sys/types.h>
	#include    <sys/socket.h>
	#include    <netinet/in.h>
	#include    <netdb.h>
	#include    <sys/stat.h>
	#include    <time.h>
	#include    <string.h>
	#include    <error.h>
	#include    <errno.h>
	#include    <string.h>
	#include    <stdlib.h>
	#include    <arpa/inet.h>

}
#include <iostream>


#define   HOSTLEN  256
#define   BACKLOG  1
#define   SERVER_IP "192.168.19.223"


int make_server_socket(int portnum);
void read_til_crnl(FILE *fp);
void do_cat(char *f, int fd);
void  response(int fd);

int process_rq( char *rq, int fd );
void header( FILE *fp, char *content_type );
void cannot_do(int fd);
void do_404(char *item, int fd);
int isadir(char *f);
int not_exist(char *f);
void do_ls(char *dir, int fd);
char *file_type(char *f);
int ends_in_cgi(char *f);
void do_exec( char *prog, int fd );
//}

#endif
