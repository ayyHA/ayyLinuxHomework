#include "ch3.h"

int recordNo=0;
int* recordSize=NULL;

bool setRecordNo(void);

int main(){
	FILE* fp=fopen("./testForBinary.txt","r");
	OperateFile(fp);
	fclose(fp);
	return 0;
}

bool setRecordNo(void){

}

