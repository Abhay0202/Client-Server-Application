/* A simple server in the internet domain using TCP. The port number is passed as an argument */

#include <stdio.h>   //input-output functions
#include <stdlib.h>  //inbuilt functions & several macros
#include <string.h>  //inbuilt string functions
#include <unistd.h>  //provides access to POSIX s/m API
#include <sys/types.h>   //definitions of different data types used in s/m calls
#include <sys/socket.h>  //definitions of structures needed for sockets
#include <netinet/in.h>  //constants & structures for internet domain address

void error(const char *msg)    //error function
{
    perror(msg);        //inbuilt error function
    exit(1);            //terminates the program
}

int main(int argc, char *argv[])     //2 arguments- filename & port no
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;            
     char buffer[255];                       //buffer for storing data/msg
     struct sockaddr_in serv_addr, cli_addr;       //structures
     int n;

     if (argc < 2) {          //Throws error if port no is not mentioned in CLI
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);     //socket creation
     if (sockfd < 0) //socket not created
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));//clears  data in structure
     portno = atoi(argv[1]);      

     //filling the required data into the server structures
     serv_addr.sin_family = AF_INET;          //IPv4-domain
     serv_addr.sin_addr.s_addr = INADDR_ANY;  //IP address of local host
     serv_addr.sin_port = htons(portno);      //passing port no 
     
     //bind function-used for checking whether address has been assigned or not
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     //listen function-listens for the connection request from client
     listen(sockfd,5); //5 here tells no of connections s/m can handle at a time
     
     clilen = sizeof(cli_addr);    //structure for client
	
     //accept function- used for accepting the request from the client side
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     //read & write b/w client & server
     printf("Server:");

while(1)
     {    
	   
           bzero(buffer,256);              //clears buffer for receiving the msg
		
           n = read(newsockfd,buffer,255);  //server reads the buffer
           if (n < 0) error("ERROR reading from socket");
           printf("\n"); 
	  
	char sequence_no;
	char type[4];
	char op_type[4];
	char payload[100];
	int k=0;
	int j=0;

	sequence_no = buffer[k];

	for(k=1;k<4;k++)
	{
		type[j]=buffer[k];
		j++;
	}
	type[j]='\0';

	int msg_code=buffer[4];

	j=0;
	for(k=5;k<8;k++)
	{
		op_type[j]=buffer[k];
		j++;
	}
	op_type[j]='\0';

	j=0;
	for(k=8;k<strlen(buffer);k++)
	{
		payload[j]=buffer[k];
		j++;
	}
	payload[j]='\0';

	printf("sequence no of the frame is %c\n", sequence_no);
	
        printf("the input type of the socket is %s\n", type);	
	
	printf("the msg code chosen is: %d\n", msg_code);
	
        printf("the output type of the socket is %s\n", op_type);	
        
	printf("the data i.e. payload is %s\n", payload);	


           bzero(buffer,256);            //clears buffer for receiving the msg
		
           n = read(newsockfd,buffer,255);  //server reads the buffer
           
	   if (n < 0) error("ERROR reading from socket");
           
	   printf("Client: %s\n",buffer); //printing client msg to screen

          bzero(buffer,256);              //clears buffer for writing the msg

          fgets(buffer,255,stdin);                   //reads a line 
     
          //writing to the buffer
          n = write(newsockfd,buffer,strlen(buffer));
           if (n < 0) error("ERROR writing to socket");

           int i=strncmp("Bye" , buffer, 3);  //compares the string
           if(i == 0)
               break;
     }
     close(newsockfd);   //ends the network
     close(sockfd);      //ends the socket
     return 0; 
}
