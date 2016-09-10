/*msgserver.c*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#define   MSG_FILE "msgserver.c"
#define   BUFFER 255
#define   PERM S_IRUSR|S_IWUSR
/* ����˴�������Ϣ�������û��ɾ��,����Ҫʹ��ipcrm������ɾ���� */
/* ipcrm -q <msqid> */

struct msgtype {
    long mtype;
    char buffer[BUFFER+1];
};

int main()
{
    struct msgtype msg;
    key_t key;
    int msgid;
   
    if((key=ftok(MSG_FILE,'a'))==-1)
    {
        fprintf(stderr,"Creat Key Error:%s/n", strerror(errno));
        exit(1);
    }

    if((msgid=msgget(key, PERM|IPC_CREAT|IPC_EXCL))==-1)
    {
        fprintf(stderr, "Creat Message Error:%s/n", strerror(errno));
        exit(1);
    }
    printf("msqid = %d/n", msgid);
    while(1)
    {
        msgrcv(msgid, &msg, sizeof(struct msgtype), 1, 0);
        fprintf(stderr,"Server Receive:%s/n", msg.buffer);
        msg.mtype = 2;
        msgsnd(msgid, &msg, sizeof(struct msgtype), 0);
    }
    exit(0);
}