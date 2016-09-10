#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<syslog.h>
#include <sys/stat.h>



int main()
{
	pid_t pid, sid;
	int i, fd;
	char *buf = "this is a daemon!\n";
	pid = fork();
	if(pid < 0)
	{
		printf("error fork!\n");
		exit(1);
	}
	else if(pid > 0)
	{
		exit(0);
	}

	//openlog("daemon_syslog", LOG_PID, LOG_DAEMON);

	openlog("Test", LOG_CONS | LOG_PID, LOG_USER );
        syslog(LOG_INFO,"This is a xxxxxxxx for test");

	if((sid = setsid()) < 0)
	{
		syslog(LOG_ERR, "%s\n", "setsid");
		exit(1);
	}
	if((sid = chdir("/tmp")) < 0)
	{
	    syslog(LOG_ERR, "%s\n", "chdir");
	    exit(1);
	}
	umask(0);

	for(i = 0; i < getdtablesize(); i++)
	{
		close(i);
	}
	while(1)
	{
		if((fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
		{
		     syslog(LOG_ERR, "open");
		     exit(1);
	    }
	   write(fd, buf, strlen(buf) + 1);
	   close(fd);
	   sleep(10);
	}
	closelog();//
	exit(0);
}

