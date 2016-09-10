/* webserv.c - a web server 

 *      build: gcc webserv.c -o webserv

 */



#include "task_queue.h"
#include "socknet.h"
#include "probeth.h"

using namespace baselib;

char	request[BUFSIZ];
int     commu_fd;




int main(int ac, char *av[])
{
    //main para 
    if ( ac == 1 )
    {
        fprintf(stderr,"usage: ws portnum\n");
        return -1;
    }
	//init queue
	queue<int> *dq = new queue<int>;

    //create pthread
    Probeth _pb(dq);

	//receive data
	struct sockaddr_in from;
    memset(&from, 0, sizeof(struct sockaddr));
    socklen_t   len = sizeof(struct sockaddr);
    int sock = make_server_socket(atoi(av[1]) );
    if ( sock == -1 )
	 	return -1;
	
    //main loop here 
    while(1)
    {
    	/* take a call and buffer it */
		commu_fd = accept( sock,(struct sockaddr *)&from, &len );
		std::cout<<"ip="<<inet_ntoa(from.sin_addr)<<std::endl;
		//printf("xxxxxxxxxxx:%d\n",commu_fd);
        FILE *fpin = fdopen(commu_fd, "r" );
		
        /* read request */
        fgets(request,BUFSIZ,fpin);
        printf("got a call: request = %s", request);


		//Èë¶Ó		
		dq->en_queue(commu_fd);

		/* do what client asks */
        //process_rq(request, commu_fd);
        fclose(fpin);
    }
	return 0;
}


