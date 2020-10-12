#include "ch2.h"
int main(int argc,char* argv[]){
	int fd;
	FILE* fp;
	fd = open("./text6.txt",O_RDWR | O_CREAT);
	fp = fdopen(fd,"w+");
	for(int i=1;i<argc;i++){
		fwrite(argv[i],1,strlen(argv[i]),fp);
	}

//	fprintf(fp,"test my data %s","hello world second times");
	
	fclose(fp);
	close(fd);
	printf("Test Success\n");
	return 0;
}
