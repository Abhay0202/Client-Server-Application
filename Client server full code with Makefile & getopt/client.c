//Client program. Server IP address & port no needs to be passed as arguments

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "args.h"

#define buffer_size 255

int main(int argc, char* argv[])
{	    
    int sockfd, portno, channel,count,pos;
    struct sockaddr_in serv_addr;
    struct hostent *server;   //gives info related to host-host name, ip address

    char buffer[buffer_size];   //buffer for storing data

     portno=9999;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);//creating socket for communication
    if (sockfd < 0) 
    {
        error("ERROR opening socket");
	exit(1);
    }
     const char *name= "127.0.0.1";
    server = gethostbyname(name); //storing server's IP address
	
    if (server == NULL) 
    {     
        fprintf(stderr,"ERROR, no such host\n");
        exit(1); //terminates if server's IP address is not passed
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); 

	//server structure

    serv_addr.sin_family = AF_INET;  //IPv4 Domain address
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
         server->h_length); 

    serv_addr.sin_port = htons(portno);  //port no

    //connect function

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {    error("ERROR connecting");
	exit(1);
    }

//sending the frame

printf("Client: ");

    while(1)
    {
	struct frame *ptr=arguments(argc, argv);//calls arguments() from args.h

        bzero(buffer,buffer_size);//clears the buffer
	
	char *f1= ptr->sequence_no;      //passing sequence_no
	strcpy(buffer,f1);  //copying sequence no to buffer

	char *f2= ptr->type;      //passing type
	strcat(buffer,f2);

	int f3 = ptr->msg_code;      //passing msg_code
	buffer[4]=f3;

	char *f4= ptr->o_p_type;      //passing o_p_type
	strcat(buffer,f4);
	
	if(f3==1)
	{	
		pos=8;
		for(count=0; count<5; count++)
		{
			buffer[pos]=ptr->payload1[count];
			pos++;
		} 
	}
	
	else
	{
		int f5=ptr->payload;
		buffer[8]=f5;
	}

	channel = write(sockfd,buffer,strlen(buffer));//client writes into the buffer

	bzero(buffer,buffer_size);//clears the buffer
        fgets(buffer,buffer_size,stdin);// reads the string to be sent
	channel = write(sockfd,buffer,strlen(buffer));//client writes into the buffer
		
        if (channel < 0)
        { 
             error("ERROR writing to socket");
	     exit(1);
        }

        bzero(buffer,buffer_size); //clears buffer
        channel = read(sockfd,buffer,buffer_size);//reads from the buffer

        if (channel < 0) 
        {     error("ERROR reading from socket");
	     exit(1);
        }

	printf("\n");
        printf("Server : %s\n",buffer);
        int cmp = strncmp("Bye" , buffer , 3); //compares the string
        if(cmp == 0)
               break;
    }
    close(sockfd);  //closes the socket
    return 0;
}

