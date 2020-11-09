#include "../ch8.h"
#include <dlfcn.h> 
int array[20];

int main(int argc,char* argv[]){
	void* dlib = dlopen("./libdlib.so",RTLD_NOW);
	if(!dlib){
		perror("dlopen failed!\n");
		exit(1);
	}
	
	for(int i=1;i<argc;i++){
		array[i-1]=atoi(argv[i]);
	}

	void(*dsort)(int*,int)=dlsym(dlib,"mySort");
	if(!dsort){
		perror("dlsym failed");
		exit(1);
	}

	void(*doutput)(int*,int)=dlsym(dlib,"myOutput");
	if(!doutput){
		perror("dlsym failed");
		exit(1);
	}
	
	if(argc==1){
		void(*drand)(int*)=dlsym(dlib,"myRand");	
		if(!drand){
			perror("drand failed!\n");
		}
		drand(array);
		dsort(array,10);
		doutput(array,10);
	}
	else{
		dsort(array,argc-1);
		doutput(array,argc-1);
	}
	dlclose(dlib);
	return 0;
}
