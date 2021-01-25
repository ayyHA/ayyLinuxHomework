#include "./ch1-22.h"

void show_msq_stat(struct msqid_ds* buf){
	printf("The userID = %d\n",buf->msg_perm.uid);
	printf("The groupID = %d\n",buf->msg_perm.gid);
	printf("The creator ID = %d\n",buf->msg_perm.cuid);
	printf("The creator ID = %d\n",buf->msg_perm.cgid);
	printf("The operation permission =%#o, ",buf->msg_perm.mode);
	printf("access permissions = %#o\n",buf->msg_perm.mode&0777);
	printf("msg_cbytes = %ld\n",buf->msg_cbytes);
	printf("msg_qbytes = %ld\n",buf->msg_qbytes);
	printf("msg_qnum = %ld\n",buf->msg_qnum);
	printf("msg_lspid = %d\n",buf->msg_lspid);
	printf("msg_lrpid = %d\n",buf->msg_lrpid);
	printf("msg_stime = %s",buf->msg_stime ? (char*)ctime(&(buf->msg_stime)):"Not Set\n");
	printf("msg_rtime = %s",buf->msg_rtime ? (char*)ctime(&(buf->msg_rtime)):"Not Set\n");
	printf("msg_ctime = %s\n",ctime(&(buf->msg_ctime)));
}

int main(){
	int msgid,running =1;
	struct my_msg msgbuf;
	struct msqid_ds buf;
	memset(&msgbuf,0,sizeof(struct my_msg));
	memset(&buf,0,sizeof(struct msqid_ds));
	msgid = msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid ==-1)
		perror("msgget failed!\n");
	while(running){
		printf("Enter some text to send:");
		fgets(msgbuf.text,BUFSIZ,stdin);
		msgbuf.my_msg_type = (long int)msgbuf.text[0];
		if(msgsnd(msgid,(void *)&msgbuf,sizeof(msgbuf.text),0)==-1)
			perror("msgsnd failed!\n");
		/*msgctl(msgid,IPC_STAT,&buf);*/
		/*show_msq_stat(&buf);*/
		if(strncmp(msgbuf.text,"886",3) ==0)
			running =0;
	}
	printf("SEND SAY BYE!\n");
	exit(EXIT_SUCCESS);
}
