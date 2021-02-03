#include <stdio.h> 
#include <unistd.h>
#include<wait.h> 
#include<signal.h> 

multiple_process(int number) 
{ 
	int i, choice;
	pid_t pid;//declaring process id variable

	printf("\n*********** MENU *************\n");
        printf("1. create child processes\n2. kill child processes\n3. child processes with IDs\n4. Exit\nEnter your choice: ");
	
while(1)
   {
      
      scanf("%d",&choice);

      switch(choice)
      {
         case 1: 
      		for(i=0;i<number;i++)  
		{ 
			if((pid = fork()) == 0) 
			{ 
				printf("child process %d\n", i+1); 
			 
			} 
		}
		break;

	case 2: kill(pid, SIGINT); 
		break; 

	case 3:
		for(i=0;i<number;i++)
		{ 
			if((pid = fork()) == 0) 
			{ 
				printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 	 
			} 
		}
		break;

	case 4: exit(0);
		break;
      }

}
 
} 

