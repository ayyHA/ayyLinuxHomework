#include "./ch14.h"
int main(){
	int running = 1, msgid;
	struct my_msg msgbuf;		// 报文，有类型和正文部分
	struct msqid_ds buf;
	
	if(msgid=msgget((key_t)1234,0666|IPC_CREAT)==-1)
		perror("msgget failed!\n");
	while(running){
		printf("Enter some text:\t");
		fgets(msgbuf.text,BUFSIZ,stdin);
		msgbuf.my_msg_type = (long int)msgbuf.text[0];
		if(msgsnd(msgid,(void*)&msgbuf,sizeof(msgbuf.text),IPC_NOWAIT)==-1)
			perror("msgsnd failed!\n");
		if(strncmp(msgbuf.text,"end",3)==0)
			break;
	}
	return 0;
}
