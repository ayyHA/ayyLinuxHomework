#include "ch2.h"
int main(int argc,char* argv[]){
	FILE* fp;
	fp = fdopen(1,"w+");
	fprintf(fp,"test data %s\n","hello world");
	fclose(fp);
	return 0;
}
