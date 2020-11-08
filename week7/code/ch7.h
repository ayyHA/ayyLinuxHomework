#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <dlfcn.h>
void err_exit(char* s){
	printf("USAGE: %s is failed!\n",s);
	exit(0);
}
