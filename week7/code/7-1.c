#include "ch7.h"
static void __attribute__((constructor)) before_main(){			//构造函数
	printf("---------------Before Main---------------\n");
}

static void __attribute__((destructor)) after_main(){			//析构函数
	printf("---------------After Main----------------\n");
}
									//调用顺序:构造->Main->析构
int main(){
	printf("--------------Main Function-------------\n");
	return 0;
}
