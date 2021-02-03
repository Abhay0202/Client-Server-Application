/* A simple server in the internet domain using TCP. The port number is passed as an argument */

#include <stdio.h>   //input-output functions
#include <stdlib.h>  //inbuilt functions & several macros
#include <string.h>  //inbuilt string functions
#include <unistd.h>  //provides access to POSIX s/m API
#include <sys/types.h>   //definitions of different data types used in s/m calls
#include <sys/socket.h>  //definitions of structures needed for sockets
#include <netinet/in.h>  //constants & structures for internet domain address
#include "args.h"
//#include "dll.h"
//#include "multithread.h"
#include "mutex.h"

#define connections 5
#define buffer_size 255

int main(int argc, char *argv[])     //2 arguments- filename & port no
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;            
     char buffer[buffer_size];            //buffer for storing data/msg
     struct sockaddr_in serv_addr, cli_addr;       //structures
     int channel;

     if (argc < 2) 
     {          //Throws error if port no is not mentioned in CLI
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);     //socket creation
     if (sockfd < 0)
     {                         //socket not created
        error("ERROR opening socket");
	exit(1);
     }
 
     bzero((char *) &serv_addr, sizeof(serv_addr));//clears  data in structure
     portno = atoi(argv[1]);      

     //filling the required data into the server structures

     serv_addr.sin_family = AF_INET;          //IPv4-domain
     serv_addr.sin_addr.s_addr = INADDR_ANY;  //IP address of local host
     serv_addr.sin_port = htons(portno);      //passing port no 
     
     //bind function-used for checking whether address has been assigned or not

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
     {         error("ERROR on binding");
	       exit(1);
     }

     //listen function-listens for the connection request from client

     listen(sockfd, connections); // no of connections s/m can handle at a time
     
     clilen = sizeof(cli_addr);    //structure for client
	
     //accept function- used for accepting the request from the client side

     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
     {     error("ERROR on accept");
	  exit(1);
     }

     //read & write b/w client & server
     printf("Server:");

while(1)
     {    	   
           bzero(buffer, buffer_size);    //clears buffer for receiving the msg
		
           channel = read(newsockfd,buffer,buffer_size);  //server reads the buffer
           if (channel < 0)
	   { 
		error("ERROR reading from socket");
		exit(1);
	   }
           printf("\n"); 
	  
	char sequence_no;
	char type[4];
	char op_type[4];
	int payload;
	int count=0;
	int pos=0;

	sequence_no = buffer[count];

	for(count=1;count<4;count++)
	{
		type[pos]=buffer[count];
		pos++;
	}
	type[pos]='\0';

	int msg_code=buffer[4];
	
	pos=0;
	for(count=5;count<8;count++)
	{
		op_type[pos]=buffer[count];
		pos++;
	}
	op_type[pos]='\0';
	
	pos=0;
	
/*	for(count=9;count<14;count++)
	{
		payload[pos]=buffer[count];
		printf("the data i.e. payload is %d\n", payload[pos]);
		pos++;
	}	
*/
	
	//payload=buffer[8];

	switch(msg_code)
	{
		case 1:/*
			int n=5;
			dll(payload, n);
			break;
		*/
		case 2: //thread();
			multithread();
			break;
	}

	


	printf("sequence no of the frame is %c\n", sequence_no);
	
        printf("the input type of the socket is %s\n", type);	
	
	printf("the msg code chosen is: %d\n", msg_code);
	
        printf("the output type of the socket is %s\n", op_type);	
        
        bzero(buffer, buffer_size);   //clears buffer for receiving the msg
		
        channel = read(newsockfd,buffer,buffer_size);  //server reads the buffer
           
	   if (channel < 0) 
	   {
		error("ERROR reading from socket");
		exit(1);
           }

	   printf("Client: %s\n",buffer); //printing client msg to screen

          bzero(buffer,buffer_size);        //clears buffer for writing the msg

          fgets(buffer,buffer_size,stdin);                   //reads a line 
     
          //writing to the buffer
          channel = write(newsockfd,buffer,strlen(buffer));
           if (channel < 0) 
     	   {
		error("ERROR writing to socket");
		exit(1);
	   }

           int cmp=strncmp("Bye" , buffer, 3);  //compares the string
           if(cmp == 0)
               break;
     }
     close(newsockfd);   //ends the network
     close(sockfd);      //ends the socket
     return 0; 
}
