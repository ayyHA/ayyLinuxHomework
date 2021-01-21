#include "./ch14.h"
int main(){
	int running = 1,msgid;
	struct my_msg msgbuf;
	long int msg_type = -57;
	if(msgid=msgget((key_t)1234,0666|IPC_CREAT)==-1)
		perror("msgget failed!\n");
	while(running){
		if(msgrcv(msgid,(void*)&msgbuf,BUFSIZ,-57,IPC_NOWAIT)!=-1)
			printf("You wrote %s",msgbuf.text);
		else if(errno==ENOMSG&&msgrcv(msgid,(void*)&msgbuf,BUFSIZ,0,0)!=-1)
			printf("You wrote %s ",msgbuf.text);
		else
			perror("msgrcv failed!\n");
		if(strncmp(msgbuf.text,"end",3)==0)
		break;
	}
	if(msgctl(msgid,IPC_RMID,0)==-1)
		perror("msgrmv failed!\n");
	return 0;
}
