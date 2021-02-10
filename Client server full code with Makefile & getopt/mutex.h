#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

pthread_t tid[2]; //thread's structure for creating thread variables
int counter; 
pthread_mutex_t lock; //variable to create mutex

void* trythis() 
{ 
	pthread_mutex_lock(&lock); //function to lock the mutex

	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for (i = 0; i < (0xFFFFFFFF); i++) 
		; 

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); //function to free the mutex

	return NULL; 
} 

int multithread(void) 
{ 
	int i = 0; 
	int error; 
        int choice;
	while(1)
	{
		printf("\n*********** MENU *************\n");
      		printf("1. Create & Display\n2. Delete\n3. Exit\nEnter your choice: "); 
      		scanf("%d",&choice);

		switch(choice)
		{
		 case 1: 
			if (pthread_mutex_init(&lock, NULL) != 0)
			{ 
				printf("\n mutex init has failed\n"); 
				return 1; 
       			} 

			while (i < 2) 
			{ 
				error = pthread_create(&(tid[i]), NULL, &trythis,NULL); 
				if (error != 0) 
				printf("\nThread can't be created :[%s]", 
					strerror(error)); 
				i++; 
			} 

			pthread_join(tid[0], NULL); //waiting process
			pthread_join(tid[1], NULL); 
			break;
			
			case 2:
			
			/* terminate the thread */
    			pthread_exit(NULL);
			pthread_mutex_destroy(&lock); //destroying the mutex
			break;
		
			case 3:
			default:
			exit(0);
		}
		
	}
   
	return 0; 
} 

