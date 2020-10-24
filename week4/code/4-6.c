#include "ch3.h"
int main(){
	int d1;
	d1=open("./out.info",O_CREAT|O_TRUNC|O_WRONLY,0644);
	//dup2(d1,1);

	
	d1 = dup(STDOUT_FILENO);
	write(d1,"I am an alien \n",15);

	printf("Redirect stdout file!\n");
	return 0;
	
}
