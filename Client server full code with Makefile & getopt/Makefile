cc=gcc      
MAKE=make
RM =rm

#targets .
all: client.c server.c
	$(cc) client.c -o c	
	$(cc) server.c -lpthread
	$(MAKE) server_target
	$(MAKE) client_target	


#another target for client
client_target:
	./c -t 1 2

server_target:
	./a.out

