# Client_Server_Application
It is a client server chat application which is used for interacting & for sending messages between client & server. Moreover it can also be used for creating a network between 2 nodes and then transmitting data in the form of frames.

DESCRIPTION RELATED TO FILES:

"Client Server full code with Makefile & getopt" --> This is the folder that contains final code that needs to be run.

First server.c file needs to be run and then client.c file needs to be run.


These 2 files are mainly responsible for creating the client server chat & Data Transfer application on the same pc.


client.c file needs to be given command line arguments from the user. First argument has to be '-t' or '-u' indicating TCP or UDP operation. Second argument that needs to be given is the message code and third argument that needs to be given is the sequence number of the frame.

server.c file requires no command line arguments.


The Client here can opt between 4 operations namely: 1. Doubly Linked List Operation  2. Multi-threading Operation  3. Fork Operation  4. IPC Mechanism 


The Server then performs these operations & then send the output back to the user.
