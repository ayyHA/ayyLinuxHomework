#include "./1-22.h"
int main(){
	int msgid;
	msgid = msgget(IPC_PRIVATE,IPC_CREAT|IPC_EXCL|0660);
	printf("%d\n",msgid);
	
}
