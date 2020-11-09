#include "../ch8.h"
#include <dlfcn.h>
int main(){
	void* fpt = dlopen("./libdlib.so",RTLD_NOW);
	if(!fpt){
		perror("dlopen failed!\n");
		exit(1);
	}
	void(*fp)(void) = dlsym(fpt,"dynamic_lib_fun_call");
	if(!fp){
		perror("dlsym failed!\n");
		exit(1);
	}
	fp();
	dlclose(fpt);
	return 0;
}
