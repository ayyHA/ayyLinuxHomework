#include "./ch1-22.h"
int main(){
	int running = 1,msgid;
	struct my_msg msgbuf;
	long int msg_type = -57;
	
	if((msgid = msgget((key_t)1234,0666|IPC_CREAT)) == -1)
		perror("msgget failed!\n");
	while(running){
		if(msgrcv(msgid,(void*)&msgbuf,BUFSIZ,-57,IPC_NOWAIT)!=-1)
			printf("Receive:%s\n",msgbuf.text);
		else if(errno =ENOMSG&&msgrcv(msgid,(void*)&msgbuf,sizeof(msgbuf.text),0,0))
			printf("Receive:%s\n",msgbuf.text);
		else
			perror("msgrcv failed!\n");
		if(strncmp(msgbuf.text,"886",3) ==0 )
			break;
	}

	if(msgctl(msgid,IPC_RMID,0) == -1)
		perror("msgctl failed!\n");
	printf("RECEIVE SAY BYE!\n");
	exit(EXIT_SUCCESS);

}
