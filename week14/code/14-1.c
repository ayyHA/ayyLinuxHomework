#include "./ch14.h"
int main(int argc,char* argv[]){
	struct stat stat_buf;
	if(argc!=2){
		fprintf(stderr,"Usage : ftok <pathname>");
		return 1;
	}
	stat(argv[1],&stat_buf);
	key_t key = ftok(argv[1],0x1234);
	printf("st_dev = %lx, st_inode = %lx, key = %lx\n",stat_buf.st_dev,stat_buf.st_ino,key);
	return 0;
}
