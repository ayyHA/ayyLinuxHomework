#include "./ch1-22.h"
int main(){
	int stayopen = 1;
	struct servent* sp;			/* serve process 服务进程 */
	setservent(stayopen);
	while(1){
		sp = getservent();
		if(sp != NULL){
			printf("server name = %12s, port = %6d, proto = %4s\n",sp->s_name,ntohs(sp->s_port),sp->s_proto);
		}
		else 
			break;
	}
	endservent();

	sp = getservbyname("telnet","tcp");
	if(sp != NULL)
		printf("telnet's port is %d\n",ntohs(sp->s_port));
	else 
		printf("ERROR : getservbyname call failed!\n");
	return 0;
}
