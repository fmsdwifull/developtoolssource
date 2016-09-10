/* webserv.c - a web server 

 *      build: gcc webserv.c -o webserv

 */

#include    <stdio.h>
#include    <unistd.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <netdb.h>
#include    <sys/stat.h>
#include    <time.h>
#include    <string.h>

#define   HOSTLEN  256
#define      BACKLOG  1
#define  SERVER_IP "192.168.19.223"


int make_server_socket(int portnum);
int make_server_socket_q(int portnum, int backlog);
void read_til_crnl(FILE *fp);
void do_cat(char *f, int fd);
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






int main(int ac, char *av[])
{
    int     sock, fd;
    FILE    *fpin;
    char    request[BUFSIZ];

    if ( ac == 1 )
	{
        fprintf(stderr,"usage: ws portnum\n");
        return -1;
    }
    sock = make_server_socket( atoi(av[1]) );
    if ( sock == -1 )
	 return -1;
    /* main loop here */
    while(1)
    {
        /* take a call and buffer it */
        fd = accept( sock, NULL, NULL );
	printf("fd:%d\n",fd);
        fpin = fdopen(fd, "r" );
		
        /* read request */
        fgets(request,BUFSIZ,fpin);
        printf("got a call: request = %s", request);
        read_til_crnl(fpin);

		/* do what client asks */
        process_rq(request, fd);
        fclose(fpin);
    }
	return 0;
}



/* ------------------------------------------------------ *
   make_server_socket(int portnum)
   创建一个服务器套接字,并调用listen监听
   ------------------------------------------------------ */
int make_server_socket(int portnum)
{
    return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog)
{
    struct  sockaddr_in   saddr;   /* build our address here */
    struct    hostent        *hp;   /* this is part of our    */
    char    hostname[HOSTLEN];     /* address              */
    int    sock_id;           /* the socket             */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);  /* get a socket */
    if ( sock_id == -1 ) 
        return -1;
    /** build address and bind it to socket **/
    bzero((void *)&saddr, sizeof(saddr));   /* clear out struct     */
    gethostname(hostname, HOSTLEN);         /* where am I ?         */
    hp = gethostbyname(hostname);           /* get info about host  */
   
    printf("xxxxxxxxxxxxxx:%d-%s\n",portnum,hp->h_addr);                                         /* fill in host part    */
    //bcopy( (void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
    //saddr.sin_addr.s_addr=INADDR_ANY;
    saddr.sin_addr.s_addr=inet_addr(SERVER_IP);
    saddr.sin_port = htons(portnum);        /* fill in socket port  */
    saddr.sin_family = AF_INET ;            /* fill in addr family  */

    if ( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0 )
           return -1;

    /** arrange for incoming calls **/
    if ( listen(sock_id, backlog) != 0 ) 
        return -1;
    return sock_id;
}





/* ------------------------------------------------------ *

   read_til_crnl(FILE *)

   skip over all request info until a CRNL is seen

   ------------------------------------------------------ */
void read_til_crnl(FILE *fp)

{
    char    buf[BUFSIZ];
    while( fgets(buf,BUFSIZ,fp) != NULL && strcmp(buf,"\r\n") != 0 )
        ;
}

void do_cat(char *f, int fd)
{
    char    *extension = file_type(f);
    char    *content = "text/plain";
    FILE    *fpsock, *fpfile;
    int    c;
    if ( strcmp(extension,"html") == 0 )
        content = "text/html";
    else if ( strcmp(extension, "gif") == 0 )
        content = "image/gif";
    else if ( strcmp(extension, "jpg") == 0 )
        content = "image/jpeg";
    else if ( strcmp(extension, "jpeg") == 0 )
        content = "image/jpeg";
    fpsock = fdopen(fd, "w");
    fpfile = fopen( f , "r");
    if ( fpsock != NULL && fpfile != NULL )
    {
        header( fpsock, content );
        fprintf(fpsock, "\r\n");
        while( (c = getc(fpfile) ) != EOF )
            putc(c, fpsock);
        fclose(fpfile);
        fclose(fpsock);
    }
}

/* ------------------------------------------------------ *
   process_rq( char *rq, int fd )
   分析客户端的请求，分析然后做出相应的应答
   rq is HTTP command:  GET /foo/bar.html HTTP/1.0
   ------------------------------------------------------ */

int process_rq( char *rq, int fd )
{
    char    cmd[BUFSIZ], arg[BUFSIZ];
    /* create a new process and return if not the child */
    if ( fork() != 0 )
        return;
    strcpy(arg, "./");        /* precede args with ./ */
    if ( sscanf(rq, "%s%s", cmd, arg+2) != 2 )
        return;
    if ( strcmp(cmd,"GET") != 0 )
        cannot_do(fd);
    else if ( not_exist( arg ) )
        do_404(arg, fd );
    else if ( isadir( arg ) )
        do_ls( arg, fd );
    else if ( ends_in_cgi( arg ) )
        do_exec( arg, fd );
    else
        do_cat( arg, fd );
}



/* ------------------------------------------------------ *
   the reply header thing: all functions need one
   if content_type is NULL then don't send content type
   ------------------------------------------------------ */
void header( FILE *fp, char *content_type )
{
    fprintf(fp, "HTTP/1.0 200 OK\r\n");
    if ( content_type )
        fprintf(fp, "Content-type: %s\r\n", content_type );
}

/* ------------------------------------------------------ *
   simple functions first:
        cannot_do(fd)       unimplemented HTTP command
    and do_404(item,fd)     no such object
   ------------------------------------------------------ */
void cannot_do(int fd)
{
    FILE    *fp = fdopen(fd,"w");
    fprintf(fp, "HTTP/1.0 501 Not Implemented\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp, "That command is not yet implemented\r\n");
    fclose(fp);
}

void do_404(char *item, int fd)
{
    FILE    *fp = fdopen(fd,"w");
    fprintf(fp, "HTTP/1.0 404 Not Found\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");
    fprintf(fp, "The item you requested: %s\r\nis not found\r\n", item);
    fclose(fp);
}



/* ------------------------------------------------------ *
   the directory listing section
   isadir() uses stat, not_exist() uses stat
   do_ls runs ls. It should not
   ------------------------------------------------------ */
int isadir(char *f)
{
    struct stat info;
    return ( stat(f, &info) != -1 && S_ISDIR(info.st_mode) );
}



int not_exist(char *f)
{
    struct stat info;
    return( stat(f,&info) == -1 );
}

void do_ls(char *dir, int fd)
{
    FILE    *fp ;
    fp = fdopen(fd,"w");
    header(fp, "text/plain");
    fprintf(fp,"\r\n");
    fflush(fp);
    dup2(fd,1);
    dup2(fd,2);
    close(fd);
    execlp("ls","ls","-l",dir,NULL);
    perror(dir);
}

/* ------------------------------------------------------ *
   the cgi stuff.  function to check extension and
   one to run the program.
   ------------------------------------------------------ */

char *file_type(char *f)
/* returns 'extension' of file */
{
    char    *cp;
    if ( (cp = strrchr(f, '.' )) != NULL )
        return cp+1;
    return "";
}



int ends_in_cgi(char *f)
{
    return ( strcmp( file_type(f), "cgi" ) == 0 );
}



void do_exec( char *prog, int fd )
{
    FILE    *fp ;
    fp = fdopen(fd,"w");
    header(fp, NULL);
    fflush(fp);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    execl(prog,prog,NULL);
    perror(prog);
}



