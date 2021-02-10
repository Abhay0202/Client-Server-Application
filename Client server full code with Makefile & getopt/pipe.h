// C program to illustrate pipe system call in C 

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

#define MSGSIZE 16 

void msg_pipe() 
{ 
	char* msg1 = "Abhay"; 
	char* msg2 = "Good Morning"; 
	char* msg3 = "hello"; 
	char inbuf[MSGSIZE]; 
	int msg[2], index; 

	if (pipe(msg) < 0) 
		exit(1); 

	/* continued */
	/* write pipe */

	write(msg[1], msg1, MSGSIZE); 
	write(msg[1], msg2, MSGSIZE); 
	write(msg[1], msg3, MSGSIZE); 

	for (index = 0; index < 3; index++) { 
		/* read pipe */
		read(msg[0], inbuf, MSGSIZE); 
		printf("%s\n", inbuf); 
	} 
} 
