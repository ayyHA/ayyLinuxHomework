#include "ch2.h"
// 自定义ch2.h

int main(){
	int fd;
	fd = open("./test.txt",O_CREAT,0644);
	printf("file fd = %d\n ",fd);
	close(fd);
	return 0;
}
