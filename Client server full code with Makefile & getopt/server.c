/* A simple server in the internet domain using TCP. The port number is passed as an argument */

#include <stdio.h>   //input-output functions
#include <stdlib.h>  //inbuilt functions & several macros
#include <string.h>  //inbuilt string functions
#include <unistd.h>  //provides access to POSIX s/m API
#include <sys/types.h>   //definitions of different data types used in s/m calls
#include <sys/socket.h>  //definitions of structures needed for sockets
#include <netinet/in.h>  //constants & structures for internet domain address
#include "args.h"
#include "dll.h"
#include "mutex.h"
#include "fork.h"
#include "writer.h"
#include "reader.h"
#include "pipe.h"

#define connections 5
#define buffer_size 255
#define portno 9999

int main()     
{
     int sockfd, newsockfd;
     int payload1[1000];
     int payload,count=0,pos=0, msg_code,size,cmp;
     socklen_t clilen;            
     char buffer[buffer_size];            //buffer for storing data/msg
     struct sockaddr_in serv_addr, cli_addr;       //structures
     int channel;


     sockfd = socket(AF_INET, SOCK_STREAM, 0);     //socket creation
     if (sockfd < 0)
     {                         //socket not created
        error("ERROR opening socket");
	exit(1);
     }
 
     bzero((char *) &serv_addr, sizeof(serv_addr));//clears  data in structure
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
        
	msg_code=buffer[4];
	
	if(msg_code==1)
	{
		for(count=9;count<14;count++)
		{
			payload1[pos]=buffer[count];
			printf("the data i.e. payload is %d\n", payload1[pos]);
			pos++;
		}		
	}
	
	else
	{
		payload=buffer[8];
	}	

	size=5;

	switch(msg_code)
	{
		case 1: //doubly linked list operation
			dll(payload1, size);
			break;
		
		case 2: //threading;
			multithread();
			break;

		case 3: //fork process
			multiple_process(payload);
			break;

		case 4: if (payload==1)
			{	writer();
				reader();
			}

			else
			{
				msg_pipe();
			}
			break;
	}
	      
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
	      
           cmp=strncmp("Bye" , buffer, 3);  //compares the string
           if(cmp == 0)
               break;
    }
     close(newsockfd);   //ends the network
     close(sockfd);      //ends the socket
     return 0; 
}
