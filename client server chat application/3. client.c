//Client program. Server IP address & port no needs to be passed as arguments

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)     //error function
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;   //gives info related to host-host name, ip address

    char buffer[256];   //buffer for storing data
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);//creating socket for communication
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]); //storing server's IP address

    if (server == NULL) {     
        fprintf(stderr,"ERROR, no such host\n");
        exit(0); //terminates if server's IP address is not passed
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); 

	//server structure
    serv_addr.sin_family = AF_INET;  //IPv4 Domain address
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
         server->h_length); 

    serv_addr.sin_port = htons(portno);  //port no

    //connect function
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Client: ");

    while(1)
    {
        bzero(buffer,256);//clears the buffer
        fgets(buffer,255,stdin);// reads the string to be sent
        n = write(sockfd,buffer,strlen(buffer));//client writes into the buffer

        if (n < 0) 
             error("ERROR writing to socket");

        bzero(buffer,256); //clears buffer
        n = read(sockfd,buffer,255);//reads from the buffer

        if (n < 0) 
             error("ERROR reading from socket");

        printf("Server : %s\n",buffer);
        int i = strncmp("Bye" , buffer , 3); //compares the string
        if(i == 0)
               break;
    }
    close(sockfd);  //closes the socket
    return 0;
}
