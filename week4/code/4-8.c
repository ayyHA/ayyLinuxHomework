#include "ch3.h"
int main(){
	FILE* fp;
	fp=fopen("./ch3.h","r");
	int fd;
	fd=fileno(fp);
	printf("fd=%d\n",fd);
	return 0;
}
