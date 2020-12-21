#include "./ch13.h"
void write_data(FILE *stream){
	int i;
	for(i=0;i<50;i++){
		fprintf(stream,"line %2d\n",i);
	}
	if(ferror(stream))
		perror("Output to stream failed!\n");
}
int main(){
	FILE* output;
	output=popen("more -10","w");
	if(!output)
		perror("could not run more!\n");

	write_data(output);
	pclose(output);
	return EXIT_SUCCESS;
}
