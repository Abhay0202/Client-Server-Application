//Frame that needs to be sent

#include<stdio.h>
#include<stdlib.h>

enum operation {Doubly_LL=1, Multi_Threading=2, Fork=3, IPC=4 };
struct frame
{
	char sequence_no[8];  //frame no.
	char type[4];      //tcp or udp
	enum  operation msg_code;   //operation that neeeds to be performed
	char o_p_type[4];  //tcp or udp
	char payload[50];     //payload
	int payload_size;      //size of payload
};

int main()
{
	int j, no_of_frames;
    	printf("Enter the number of frames: ");
    	scanf("%d", &no_of_frames);
	
	struct frame *ptr;
    	ptr = (struct frame *)malloc( no_of_frames * sizeof(struct frame));
	
	for(j=0; j<no_of_frames; j++)
	{
		printf("Enter Sequence No of the frame\n");
		scanf("%s", (ptr+j)->sequence_no);
	
		printf("Enter i/p type\n");
		scanf("%s", (ptr+j)->type);
	
		printf("Enter msg code\n");
		scanf("%u", &(ptr+j)->msg_code);         //unsigned integer

		printf("Enter o_p_type\n");
		scanf("%s", (ptr+j)->o_p_type);

		printf("Enter the payload\n");
		scanf("%s", (ptr+j)->payload);
		
		(ptr+j)->payload_size=sizeof((ptr+j)->payload);
		printf("The size of payload is %x\n",(ptr+j)->payload_size);

	}	
	
		
return 0;
}
