/******************************************************************************

#Implementation of Singly Linked List
@Auhtor :	Yash Gupte
@Dated	:	31/12/2018

*******************************************************************************/
#include <stdio.h>
#define SIZE 4	
struct linkedlist{
    int val;
    struct linkedlist* next;
};

typedef struct linkedlist node;
typedef enum{Success,Error}errtypes;
char* errors[]={"Success\n","Error\n"};
const char* functions[]={"Add\n","Disp\n","Del\n","Free\n"};

node* AddElement(node*);
errtypes Disp(void);
errtypes Del(void);
errtypes Add(void);
errtypes Free(void);

errtypes (*function_pointer[SIZE])(void);
node* head,*first,*temp,*tail;
int total_count=0;

int main()
{	
	static int i=0;
	char buff[10];
	errtypes status=Success;
	function_pointer[0]=Add;
	function_pointer[1]=Disp;
	function_pointer[2]=Del;
	function_pointer[3]=Free;

	while(1)
	{
		printf("Enter the function to execute\n");
		for(i=0;i<SIZE;i++)
		{
			if(strcmp(functions[i],(const*)fgets(buff,10,stdin))==0){status=function_pointer[i]();break;}
		}
	}
    return 0;
}


errtypes Disp()
{
	temp=first;
	while(temp!=NULL)
	{
		printf("%d==>",temp->val);
		temp=temp->next;
	}
	printf("NULL\n");
	return Success;
}

errtypes Del()
{	
	int count=1,location=0;
	printf("Enter the location to delete\n");
	scanf("%d",&location);
	printf("%d\n",location);
	temp=first;
	while(temp!=NULL)
	{	
		if(location==0)
		{
			first=temp->next;
			break;
		}
		if(count==location)
		{	
			temp->next = temp->next->next;
		}
		if(count+1 == location && temp->next->next==NULL)
		{
			tail=temp;
			temp->next=NULL;
			break;
		}
		temp=temp->next;
		count+=1;
	}
	return Success;
	
}

node* AddElement(node* local_head)
{	
	int input=1;
	while(input)
	{	
		local_head = (node*)malloc(sizeof(node));
		scanf("%d",&local_head->val);
		total_count+=1;
		if(first==0)
		{
			tail=first=temp=local_head;
		}
		else
		{
			temp=tail;
			temp->next = local_head;
			temp = local_head;
			tail=temp;
		}
		printf("Enter 1 to continue to 0 to delete elements\n");
		scanf("%d",&input);
	}
	
	return local_head;
}

errtypes Add(void)
{
	head=AddElement(head);
	if(head==NULL)return Error;
	return Success;
}

errtypes Free()
{
	temp=first;
	while(temp!=NULL)
	{
		free(temp);
		temp=temp->next;
	}
	printf("Freed All Memory\n");
	return Success;
}