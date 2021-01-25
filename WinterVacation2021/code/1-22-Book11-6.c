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
	key_t key;
	int new,msqid,msgflg;
	struct msqid_ds buf;
	msgflg = IPC_CREAT|IPC_EXCL|0660;
	printf("Please input the key(long int):");
	scanf("%ld",&key);
	if((msqid = msgget(key,msgflg))>0)				//返回值为消息队列标识ID，大于0表示是新的消息队列ID
		new = 1;	
	else if(errno == EEXIST){
		new = 0;
		msqid = msgget(key,IPC_CREAT|0660);
	}	
	else{
		perror("The msgget failed!\n");
	}

	if(msgctl(msqid,IPC_STAT,&buf) == -1)				//获取msqid_ds,以查看状态
		perror("msgctl IPC_STAT failed!\n");
	show_msq_stat(&buf);
	if(new)
		msgctl(msqid,IPC_RMID,NULL);
	return 0;
}
