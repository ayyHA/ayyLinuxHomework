#include "../ch8.h"
void dynamic_lib_fun_call(void){
	printf("Dynamic Lib Function Called!\n");
}

int myCompare(const void* p1,const void* p2){
	int* a =(int*)p1;
	int* b =(int*)p2;
        return *a - *b;
}


void mySort(int* array,int len){
	qsort(array,len,sizeof(array[0]),myCompare);
}

void myOutput(int* array,int len){
	for(int i=0;i<len;i++)
                printf("array[%d]=%d\n",i,array[i]);

}

void myRand(int* array){
	srand((unsigned)(time(0)));
	for(int i=0;i<10;i++){
		array[i]=rand()%100;
	}
}

