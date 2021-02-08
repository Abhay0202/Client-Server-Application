// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define buffer_size 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[buffer_size]; 
	//char *hello = "Hello from client"; 
	struct sockaddr_in servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
        { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	while(1)
     {
	int n, len; 

        bzero(buffer,buffer_size);//clears the buffer
	fgets(buffer,buffer_size,stdin);// reads the string to be sent

	sendto(sockfd, buffer, buffer_size, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 

	//printf("Hello message sent.\n"); 
		
	n = recvfrom(sockfd, (char *)buffer, buffer_size, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Server : %s\n", buffer); 

	int cmp = strncmp("Bye" , buffer , 3); //compares the string
        if(cmp == 0)
               break;
     }
	close(sockfd); 
	return 0; 
} 

