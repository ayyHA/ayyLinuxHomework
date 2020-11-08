#include "../week7/code/ch7.h"
#define N 10
int a[N],i;
int main(){
	for(i=0;i<N;i++)
		a[i]=i+1;
	a[N]=123456789;
	printf("i = %d\n",i);//a与i均为未赋值的全局变量，则都会被存储到bss段，而其地址是连续的，a索引为10的地址对应为i的地址，故值被赋给了i
	printf("%d\n",a[N]);//原样：printf("%d\n",a[i]);
	return 0;
}
