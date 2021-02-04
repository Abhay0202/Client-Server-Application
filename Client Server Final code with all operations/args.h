//This is client side.....Here info has to be taken from the user

void error(const char *msg)    //error function
{
    perror(msg);        //inbuilt error function
    exit(1);            //terminates the program
}

enum operation {Doubly_LL=1, Multi_Threading=2, Fork=3, IPC=4 };
struct frame
{
	char sequence_no[9];         //frame no.
	char type[4];               //tcp or udp
	enum  operation msg_code;   //operation that neeeds to be performed
	char o_p_type[4];           //tcp or udp
	int payload;           //payload
	int payload1[100];
	int payload_size;           //size of payload
};

struct frame* arguments()
{
	int count, choice;
	int ll[5];
	struct frame *ptr;
    	ptr = (struct frame *)malloc(sizeof(struct frame));

	while(1)
	{
		printf("Enter Sequence No of the frame\n");
		scanf("%s", (ptr)->sequence_no);
	
		printf("Enter i/p socket type\n");
		scanf("%s", (ptr)->type);
	
		printf("Enter msg code\n");
		scanf("%u", &(ptr)->msg_code);         

		printf("Enter o/p socket type\n");
		scanf("%s", (ptr)->o_p_type);

		switch(ptr->msg_code)
	       {
		case 1: 
			printf("Enter the data\n");

	        	for(count=0; count<5; count++)
			{
				scanf("%d", &ll[count]);
				ptr->payload1[count]=ll[count];
			}  
			break;
		 
		case 2: printf("It is a Multithreading operation\n");
			break;
		
		case 3: printf("It is a fork operation\n");
			printf("Enter the no of processes to be formed:\n");
			scanf("%d", &(ptr->payload));
			break;
		
		case 4: printf("It is IPC Mechanism operation\n");
			printf("chose whether\n 1.Msg Queue\n 2.Pipe\n");			
			scanf("%d", &choice);
			ptr->payload = choice;
			break;
       	       }

		(ptr)->payload_size=sizeof((ptr)->payload);
		printf("The size of payload is %x\n",(ptr)->payload_size);
return ptr;
       }

}
