#include "./ch12.h"
int main(){
	pid_t pid1;	
	int fd1[2],f1;
	char buf1[100];
	memset(buf1,0,sizeof(buf1));
	if(pipe(fd1)<0){
		perror("fd1 pipe failed!\n");
		exit(-1);
	}
	
	pid1=fork();
	if(pid1<0){
		perror("pid1 fork failed!\n");
		exit(-1);
	}
	else if(pid1==0){
		printf("%d:Start\n",getpid());
		close(fd1[0]);
		close(1);		// 关闭stdout;
		dup(fd1[1]);		// 复制管道输出
	//	printf("%d:Start\n",getpid());
		// 执行execl()
		execl("./test","Hello","World","2020","12","07",NULL);
	}
	else{
		int s1;
		waitpid(pid1,&s1,0);
		printf("Parent : %d get the INPUT!\n",getpid());
		close(fd1[1]);
		f1=read(fd1[0],buf1,sizeof(buf1));
		if(f1<=0){
			printf("Parent read failed!\n");
		}
		else{
			fprintf(stdout,"%s",buf1);
		}
		return 0;
	}
}
