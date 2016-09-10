
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
	#include    <fcntl.h> 

}
#include <iostream>


#define SERVER_ADDR "192.168.18.144"
#define PORT  21

#define BUF_SIZE 1024

#define USERNAME  "root"
#define PASSWORD   "123456"


char DIRNAME[256];
char FILENAME[256];


using namespace std;

main(int argc,char *argv[]) 
{

	//printf("path is :%s--%s\n",argv[1],argv[2]);

	sprintf(DIRNAME,"%s\0",argv[1]);	
	sprintf(FILENAME,"%s\0",argv[2]);
	
	
    cout<< DIRNAME <<FILENAME <<endl;
	

	char read_buf[BUF_SIZE];
	char send_buf[BUF_SIZE];
	
	int control_sock;
	//struct hostent *hp;
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	
	/* 初始化socket */
	control_sock = socket(AF_INET, SOCK_STREAM, 0);
	//hp = gethostbyname(server_name);
	//memcpy(&server.sin_addr, hp->h_addr, hp->h_length);

	server.sin_addr.s_addr=inet_addr(SERVER_ADDR);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	
	
	/* 连接到服务器端 */
	connect(control_sock,(struct sockaddr *)&server, sizeof(server));
	/* 客户端接收服务器端的一些欢迎信息 */

	int len=-1;
	if((len=read(control_sock, read_buf, BUF_SIZE))==-1)
	{
		perror("read error");
		return -1;
	}

	cout<<" "<<read_buf<<endl;

	
	/* 命令 ”USER username\r\n” */
	sprintf(send_buf,"USER %s\r\n",USERNAME);
	/*客户端发送用户名到服务器端 */
	write(control_sock, send_buf, strlen(send_buf));
	/* 客户端接收服务器的响应码和信息，正常为 ”331 User name okay, need password.” */
	read(control_sock, read_buf, BUF_SIZE);

	
	//cout<<" "<<read_buf<<endl;


	/* 命令 ”PASS password\r\n” */
	sprintf(send_buf,"PASS %s\r\n",PASSWORD);
	/* 客户端发送密码到服务器端 */
	write(control_sock, send_buf, strlen(send_buf));
	/* 客户端接收服务器的响应码和信息，正常为 ”230 User logged in, proceed.” */
	read(control_sock, read_buf, BUF_SIZE);

	
	//cout<<" "<<read_buf<<endl;

	
	/* 命令 ”PASV\r\n” */
	sprintf(send_buf,"PASV\r\n");
	/* 客户端告诉服务器用被动模式 */
	write(control_sock, send_buf, strlen(send_buf));
	/*客户端接收服务器的响应码和新开的端口号，
	* 正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
	read(control_sock, read_buf, BUF_SIZE);


	//cout<<" "<<read_buf<<endl;


    //获取服务器数据端口号
    char *tok=strtok(read_buf,").\r\n");
	char *dststr=strchr(tok,'(');
    char *str;
	int fir,sec,thir,four,five,six;
    if((str=strtok(dststr+1,","))!=NULL)
        fir=atoi(str);
    if((str=strtok(NULL,","))!=NULL)
        sec=atoi(str);
    if((str=strtok(NULL,","))!=NULL)
        thir=atoi(str);	
    if((str=strtok(NULL,","))!=NULL)
        four=atoi(str);
    if((str=strtok(NULL,","))!=NULL)
        five=atoi(str);	
	if((str=strtok(NULL,","))!=NULL)
		six=atoi(str);

	
	//cout<<five<<six<<endl;


	int data_sock;
	struct sockaddr_in server_data;
	memset(&server_data, 0, sizeof(struct sockaddr_in));
	
	data_sock= socket(AF_INET, SOCK_STREAM, 0);
	server_data.sin_addr.s_addr=inet_addr(SERVER_ADDR);
	server_data.sin_family = AF_INET;
	server_data.sin_port = htons(five*256+six);

	
	/* 连接服务器新开的数据端口 */
	connect(data_sock,(struct sockaddr *)&server_data, sizeof(server_data));
	
	/* 命令 ”CWD dirname\r\n” */
	sprintf(send_buf,"CWD %s\r\n", DIRNAME);
	
	/* 客户端发送命令改变工作目录 */
	write(control_sock, send_buf, strlen(send_buf));
	/* 客户端接收服务器的响应码和信息，正常为 ”250 Command okay.” */
	read(control_sock, read_buf, BUF_SIZE);


	
	//cout<<" "<<read_buf<<endl;



	/* 命令 ”SIZE filename\r\n” */
	sprintf(send_buf,"SIZE %s\r\n",FILENAME);
	/* 客户端发送命令从服务器端得到下载文件的大小 */
	write(control_sock, send_buf, strlen(send_buf));
	/* 客户端接收服务器的响应码和信息，正常为 ”213 <size>” */
	read(control_sock, read_buf, BUF_SIZE);
	

	//cout<<" "<<read_buf<<endl;


	/* 命令 ”RETR filename\r\n” */
	sprintf(send_buf,"RETR %s\r\n",FILENAME);
	/* 客户端发送命令从服务器端下载文件 */
	write(control_sock, send_buf, strlen(send_buf));
	/* 客户端接收服务器的响应码和信息，正常为 ”150 Opening data connection.” */
	read(control_sock, read_buf, BUF_SIZE);

	
	//cout<<" "<<read_buf<<endl;
	

   char cmdbuf[256];
   sprintf(cmdbuf,"touch ./%s",FILENAME);
   system(cmdbuf);


	sprintf(cmdbuf,"./%s",FILENAME);

	//cout<<"222222222222222222"<<cmdbuf<<endl;
	/* 客户端创建文件 */
	int file_handle = open(cmdbuf, O_RDWR);
	if(file_handle==-1)
	{
		perror("open error");
		return -1;
	}
	
	int read_len=0;
	for( ; ; ) 
	{
		//... ...
		/* 客户端通过数据连接 从服务器接收文件内容 */
		if(!(read_len=read(data_sock, read_buf, BUF_SIZE)))
			break;
		//cout << read_buf;
		/* 客户端写文件 */
		write(file_handle, read_buf, read_len);
	}



	return 0;
}
