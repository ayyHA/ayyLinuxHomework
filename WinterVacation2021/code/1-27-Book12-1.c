#include "./ch1-22.h"
#define DATA1 "Fine,thanks."
#define DATA2 "Hello,how are you?"

/*
 *	父进程套接字描述字用sockets[1]
 *	子进程套接字描述字用sockets[0]
 * */
int main(){
	int sockets[2],child;
	char buf[1024];
	memset(buf,0,sizeof(buf));
	/* 创建套接字偶对 */
	if(socketpair(AF_UNIX,SOCK_STREAM,0,sockets)<0){
		perror("socketspair error!\n");
		exit(EXIT_FAILURE);
	}
	/* 创建子进程 */
	if((child=fork())==-1){
		perror("fork error!\n");
		exit(EXIT_FAILURE);
	}
	else if(child==0){
		/* 关闭父进程的套接字 */
		close(sockets[1]);
		/* 写消息给父进程 */
		if(write(sockets[0],DATA2,sizeof(DATA2))<0){
			perror("write error!\n");
			exit(EXIT_FAILURE);
		}
		/* 读父进程消息 */
		if(read(sockets[0],buf,sizeof(buf))<0){
			perror("read error!\n");
			exit(EXIT_FAILURE);
		}
		printf("chiled %d received response : %s\n",getpid(),buf);
		/* 关闭子进程的套接字 */
		close(sockets[0]);
	}
	else{
		/* 关闭子进程的套接字 */
		close(sockets[0]);
		/* 读子进程消息 */
		if(read(sockets[1],buf,sizeof(buf))<0){
			perror("read error!\n");
			exit(EXIT_FAILURE);
		}
		printf("parent %d received request : %s\n",getpid(),buf);
		/* 写消息给子进程 */
		if(write(sockets[1],DATA1,sizeof(DATA1))<0){
			perror("write error!\n");
			exit(EXIT_FAILURE);
		}
		/* 关闭父进程套接字描述字 */
		close(sockets[1]);
	}
}
