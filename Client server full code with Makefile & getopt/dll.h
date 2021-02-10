#include<stdio.h>
#include<stdlib.h>

struct Node 
{
    struct Node *previous;
    int data;
    struct Node *next;
}*first=NULL;


void create(int payload[], int size)
{
	int i;
	struct Node *t,*last;
	first=(struct Node *)malloc(sizeof(struct Node));
	first->data=payload[0];
	first->next=NULL;
	first->previous=NULL;
	last=first;
	for(i=1;i<size;i++)
	{
		t=(struct Node*)malloc(sizeof(struct Node));
		t->data=payload[i];
		t->next=NULL;
		t->previous=last;
		last->next=t;
		last=t;
	}

}

void Display(struct Node *p)
{
	printf("The Linked List is:\n");
	while(p!=NULL)
	{
		printf("%d \n",p->data);
		p=p->next;
	}
}

void insertAtBeginning(struct Node *first, int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = value;
    newNode -> previous = NULL;
    if(first == NULL)
    {
       newNode -> next = NULL;
       first = newNode;
    }
    else
    {
       newNode -> next = first;
       first = newNode;
    }
    printf("\nInsertion success!!!");
}

void insertAtEnd(struct Node *first, int value)
{
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode -> data = value;
   newNode -> next = NULL;
   if(first == NULL)
   {
      newNode -> previous = NULL;
      first = newNode;
   }
   else
   {
      struct Node *temp = first;
      while(temp -> next != NULL)
         temp = temp -> next;
      temp -> next = newNode;
      newNode -> previous = temp;
   }
   printf("\nInsertion success!!!");   
}

void deleteBeginning(struct Node *first)
{
   if(first == NULL)
      printf("List is Empty!!! Deletion not possible!!!");
   else
   {
      struct Node *temp = first;
      if(temp -> previous == temp -> next)
      {
         first = NULL;
         free(temp);
      }
      else{
         first = temp -> next;
         first -> previous = NULL;
         free(temp);
      }
      printf("\nDeletion success!!!");
   }
}
void deleteEnd(struct Node *first)
{
   if(first == NULL)
      printf("List is Empty!!! Deletion not possible!!!");
   else
   {
      struct Node *temp = first;
      if(temp -> previous == temp -> next)
      {
         first = NULL;
         free(temp);
      }
      else{
         while(temp -> next != NULL)
            temp = temp -> next;
         temp -> previous -> next = NULL;
         free(temp);
      }
      printf("\nDeletion success!!!");
   }
}


int dll(int payload[], int size)
{
   printf("It is a Linked List Operation\n");
   create(payload, size);
   int choice1, choice2, value;

   while(1)
   {
      printf("\n*********** MENU *************\n");
      printf("1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter your choice: ");
      scanf("%d",&choice1);

      switch(choice1)
      {
         case 1: printf("Enter the value to be inserted: ");
         		 scanf("%d",&value);
                 while(1)
                 {
                 	printf("\nSelect from the following Inserting options\n");
                 	printf("1. At Beginning\n2. At End\n3. Cancel\nEnter your choice: ");
                    scanf("%d",&choice2);

                    switch(choice2)
                    {
                       case 1: 	insertAtBeginning(first,value);
                       		break;
                       case 2: 	insertAtEnd(first,value);
                       		break;
                       case 3: 	goto EndSwitch;
                       default: printf("\nPlease select correct Inserting option!!!\n");
                    }
                 }

         case 2: while(1)
                 {
                 	printf("\nSelect from the following Deleting options\n");
                 	printf("1. At Beginning\n2. At End\n3. Cancel\nEnter your choice: ");
                    scanf("%d",&choice2);

                    switch(choice2)
                    {
                       case 1: 	deleteBeginning(first);
                       		break;
                       case 2: 	deleteEnd(first);
                       		break;
                       case 3:	goto EndSwitch;
                       default: printf("\nPlease select correct Deleting option!!!\n");
                    }
                 }
                 EndSwitch: break;
         case 3: Display(first);
         	 break;
         case 4: exit(0);
		
         default: printf("\nPlease select correct option!!!");
      }
   }
}
