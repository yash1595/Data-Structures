#include <stdio.h>

struct doublelinked{
	struct doublelinked* next;
	struct doublelinked* prev;
	int key;
	int data;
};
typedef struct doublelinked node;
typedef enum{False=0,True=1}Bool;

node* head=NULL;
node* tail=NULL;

int GetLength(void);
void AddElementFirst(int key,int data);
void AddElementLast(int key,int data);
void AddElementIndex(int key,int data);
void DelElementFirst(void);
void DelElementLast(void);
void DelElementIndex(int key);
void DisplayNormal(void);
void DisplayRev(void);



int main(void)
{
   AddElementFirst(1,10);
   AddElementFirst(2,20);
   AddElementFirst(3,30);
   AddElementFirst(4,1);
   AddElementFirst(5,40);
   AddElementFirst(6,56); 

   printf("\nList (First to Last): ");  
   DisplayNormal();
	
   printf("\n");
   printf("\nList (Last to first): "); 
   DisplayRev();

   printf("\nList , after deleting first record: ");
   DelElementFirst();        
   DisplayNormal();

   printf("\nList , after deleting last record: ");  
   DelElementLast();
   DisplayNormal();

   printf("\nList , insert after key(4) : ");  
   AddElementIndex(4,7, 13);
   DisplayNormal();

   printf("\nList  , after delete key(4) : ");  
   DelElementIndex(4);
   DisplayNormal();

	return 0;
}

Bool isEmpty()
{
	return head==NULL;
}

int GetLength()
{
	int len=0;
	node* current=head;
	while(current!=NULL)
	{
		++len;
		current=current->next;
	}
	return len;
}

void AddElementFirst(int key, int data)
{
	node* first = (node*)malloc(sizeof(node));
	if(first==NULL)return;
	first->key=key;
	first->data=data;
	if(isEmpty())
	{
		tail=first;
	}
	else head->prev=first;
	
	first->next=head;
	first->prev=NULL;	//Check
	head=first;
}

void AddElementLast(int key,int data)
{
	node* link = (node*)malloc(sizeof(node));
	if(link==NULL)return;
	link->key=key;
	link->data=data;
	if(isEmpty())
		tail=link;
	else
	{
			tail->next=link;
			link->prev=tail;
			tail=link;
	}
	
}

void AddElementIndex(int index,int key,int data)
{
	node* link=(node*)malloc(sizeof(node));
	node* current=head;
	if(link==NULL)return;
	link->data=data;
	link->key=key;
	while(current->key!=index)
	{
		if(current==NULL)return NULL;
		current=current->next;
	}
	link->next=current->next;
	current->next=link;
	link->prev=current;
}

void DelElementFirst()
{
	//node* temp=head;
	if(isEmpty())return NULL;
	if(head->next==NULL)head=NULL;	//LAST AND HEAD ARE EQUAL.
	else
	{
		head=head->next;
		head->prev=NULL;
	}
	//return head;

}

void DelElementLast()
{
	if(tail->prev==NULL)tail=NULL;
	else
	{
		tail=tail->prev;
		tail->next=NULL;
	}
	//return last;
}

void DelElementIndex(int key)
{
	node*current=head;
	while(current->key!=key)
	{
		if(current==NULL)return NULL;
		current=current->next;
	}
	current->prev->next=current->next;
	current->next->prev = current->prev;

}

void DisplayNormal()
{
	node* current=head;
	while(current!=NULL)
	{
		printf("[%d:%d]=>",current->key,current->data);
		current=current->next;
	}
	printf("NULL\n");
}

void DisplayRev()
{
	node*current=tail;
	printf("NULL");
	while(current!=NULL)
	{
		printf("<=[%d:%d]",current->key,current->data);
		current=current->prev;
	}
	printf("\n");
}