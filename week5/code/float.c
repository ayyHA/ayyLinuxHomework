#include "ch4.h"
int main(){
	int i = 0xffffffff;
	printf("max unsigned int = %u ,min unsigned int = %u \n",i,i+1);
	int j = 0x7fffffff;
	printf("max signed int  = %d ,min signed int = %d \n",j,j+1);
	float* fltMax = (float*)malloc(sizeof(float));
	char* cMax =(char*)fltMax;
	*cMax = 0xff;
	*(cMax+1) = 0xff;
	*(cMax+2) = 0x7f;
	*(cMax+3) = 0x7f;

	printf("fltMax=%f\n",*fltMax);
	free(fltMax);

	float* fltMin = (float*)malloc(sizeof(float));
	char* cMin = (char*)fltMin;
	*cMin = 0xff;
	*(cMin+1) = 0xff;
	*(cMin+2) = 0x7f;
	*(cMin+3) = 0xff;

	printf("fltMin=%f\n",*fltMin);
	free(fltMin);

	double* dblMax = (double*)malloc(sizeof(double));
	double* dblMin = (double*)malloc(sizeof(double));
	
	cMax = (char*)dblMax;
	cMin = (char*)dblMin;

	*cMax = 0xff;
	*(cMax+1) =0xff;	
      	*(cMax+2) =0xff;
 	*(cMax+3) =0xff;
 	*(cMax+4) =0xff;	
      	*(cMax+5) =0xff;
	*(cMax+6) =0xef;
	*(cMax+7) =0x7f;
	
	 *cMin = 0xff;
        *(cMin+1) =0xff;
        *(cMin+2) =0xff;
        *(cMin+3) =0xff;
        *(cMin+4) =0xff;
        *(cMin+5) =0xff;
        *(cMin+6) =0xef;
        *(cMin+7) =0xff;


	printf("dblMax=%lf\n",*dblMax);
	printf("dblMin=%lf\n",*dblMin);
	free(dblMax);
	free(dblMin);
	//printf("FLT_MAX=%lf\n",FLT_MAX);
	//printf("FLT_MIN=%lf\n",FLT_MIN);
	//printf("DBL_MAX=%lf\n",DBL_MAX);
	//printf("DBL_MIN=%lf\n",DBL_MIN);
	return 0;
}
