#include "ch3.h"
int main(){
	int fd;
	fd=open("./turtle.txt",O_CREAT|O_TRUNC|O_WRONLY,0644);
	int fd2;
	fd2=fcntl(fd,F_DUPFD,4);
	printf("fd=%d fd2=%d \n",fd,fd2);
	write(fd2,"haha",4);
	close(fd);
	close(fd2);
	return 0;
}
