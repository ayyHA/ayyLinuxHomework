#include "../week7/code/ch7.h"

int main(int argc,char* argv[]){
	//void* dlib=dlopen("./libdlib.so",RTLD_NOW);//动态装载,RUNTIME LOAD NOW
	
	
	void* dlib = dlopen("./libdlib.so",RTLD_NOW);
	if(!dlib){
		printf("dlopen failed!\n");
		exit(-1);
	}
	

	//void(*dfunc)(void)=dlsym(dlib,"dynamic_lib_call");//声明一个函数指针
	
	void(*dfunc)(int)=dlsym(dlib,"dsum");
	if(!dfunc){
		printf("dfunc is failed!\n");
		exit(-1);
	}
	if(argc<2){
		perror("arguments failed!\n");
		exit(-1);
	}
	int a = atoi(argv[1]);
	dfunc(a);

	dlclose(dlib);
	return 0;
}

