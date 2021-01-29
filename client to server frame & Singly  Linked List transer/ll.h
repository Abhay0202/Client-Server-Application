#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node *next;

}*first=NULL;

void create(int payload[], int n)
{
	int i;
	struct Node *t,*last;
	first=(struct Node *)malloc(sizeof(struct Node));
	first->data=payload[0];
	first->next=NULL;
	last=first;
	for(i=1;i<n;i++)
	{
		t=(struct Node*)malloc(sizeof(struct Node));
		t->data=payload[i];
		t->next=NULL;
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

void insertAtBeginning(struct Node *p, int value)
{

	struct Node *newNode;
	newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->next = first;
	first = newNode;
}

void insertAtEnd(struct Node *p, int value)
{
	struct Node *newNode;
	newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data = 98;
	newNode->next = NULL;

	struct Node *temp = first;
	while(temp->next != NULL)
	{
	  	temp = temp->next;
	}

temp->next = newNode;

}

void deleteBeginning(struct Node *p)
{

	first = first->next;
	printf("Element deleted\n");
}

void deleteEnd(struct Node *p)
{
	printf("Element deleted\n");
	struct Node* temp = first;
	while(temp->next->next!=NULL)
	{
		temp = temp->next;
	}
temp->next = NULL;
}

dll(int payload[], int n)
{
   printf("It is a Linked List Operation\n");
   create(payload,n);

   int choice1, choice2, value, location;
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
