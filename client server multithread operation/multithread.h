#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

/* function to be executed by the new thread */
void* do_loop(void* data)
{
    int i;			/* counter, to print numbers */
    int j;			/* counter, for delay        */
    int me = *((int*)data);     /* thread identifying number */

    for (i=0; i<5; i++) 
    {
	for (j=0; j<500000; j++) /* delay loop */
	    ;
        printf("'%d' - thread\n", me);
    }
}



int multithread()

{
    int        thr_id;         /* thread ID for the newly created thread */
    pthread_t  p_thread;       /* thread's structure                     */
    int        a         = 1;  /* thread 1 identifying number            */
    int        b         = 2;  /* thread 2 identifying number            */
    int choice;

	//printf("It is a Multithreading operation\n");
	while(1)
	{
		printf("\n*********** MENU *************\n");
      		printf("1. Create & Display\n2. Delete\n3. Exit\nEnter your choice: "); 
      		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
			/* create a new thread that will execute 'do_loop()' */
    			thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)&a);
			/* run 'do_loop()' in the main thread as well */
    			do_loop((void*)&b);
			break;
			
			case 2:
			
			/* terminate the thread */
    			pthread_exit(NULL);
			break;
		
			case 3:
			default:
			exit(0);
		}
		
	}   
    /* NOT REACHED */
    return 0;
}
