#include <float.h>
#include <stdio.h>
int main(){
	
	printf("FLT_MAX=%e\n",FLT_MAX);
	printf("FLT_MIN=%e\n",FLT_MIN);
	printf("DBL_MAX=%e\n",DBL_MAX);
        printf("DBL_MIN=%e\n",DBL_MIN);
	printf("LDBL_MAX=%Le\n",LDBL_MAX);
        printf("LDBL_MIN=%Le\n",LDBL_MIN);
	printf("INT_MAX=%ld\n",INT_MAX);
	printf("INT_MIN=%ld\n",INT_MIN);
	return 0;
}
