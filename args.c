//This is client side.....Here info has to be taken from the user

#include<stdio.h>
int main()
{
	printf("Which socket to be used?");
	char socket[4]; //tcp or udp
	scanf("%s", socket);

	printf("What will be the type of Message?");
	char msg[10];   //DLL or Multi thread or Fork or IPC
	scanf("%s", msg);

	printf("What will be the type of socket in response?");	
	char op_socket[4];   //tcp or udp
	scanf("%s", op_socket);

	printf("Data field which are required for selected Message code ?");  
	char data[50];     //payload
	scanf("%s", data);	
	
	return 0;
}
