#include "my.h"

int main(){
	/*
	input();
	save(user);
	printf("Save success!\n");
	printf("How to sort your address book? 1-Ascend 2-Descend\n");
	int option;
	scanf("%d",&option);
	//printf("Your address book become like this:\n");
	mySort(option);
	randdat();
	*/
	//setUserList();	
	input();
	if(user!=NULL)
		save(user);
	mySort();
	output();
	randdat();
	output();
	
	//资源释放
	free(user);
	for(int i=0;i<countOfRecord;i++)
		free(userList[i]);
	free(userList);
	return 0;
}
