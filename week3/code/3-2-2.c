#include "ch2.h"
int main(){
	FILE* fp;
	fp = fopen("./test.txt","w");
	printf("file fp = %d\n",fp->_fileno);
	fclose(fp);
	return 0;
}
