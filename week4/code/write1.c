#include "ch3.h"
int main(){
	int n,i,fd;
	char buf;
	fd=open("./test.dat",O_CREAT|O_WRONLY,0644);
	for(i=0;i<2;i++){
		srand(time(0));
		n=rand()%26;
		buf=(char)('a'+n);
		printf("n=%c:",buf);
		write(fd,&buf,1);
		lseek(fd,10,SEEK_SET);
		sleep(50);
	}
	close(fd);
}
