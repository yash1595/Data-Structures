/****************************************************************************
#Implementation of Queue using Arrays
@Author : Yash Gupte
@Dated	: 31/12/2018
*****************************************************************************/


#include<stdio.h>
#include<stdlib.h>


struct queue{
	int front,rear,size,capacity,first;
	int* array;
	struct queue *node;
};

typedef struct queue Queue;
int count = 0;

Queue* CreateQueue(int);
void Enqueue(Queue*,int);
int Dequeue(Queue*);
void Display(Queue*);
int QueueEmpty(Queue*);
int QueueFull(Queue*);
int Front(Queue*);
int Rear(Queue*);

int main(void)
{
	struct Queue* queue = CreateQueue(5); 
  
    Enqueue(queue, 10); 
    Enqueue(queue, 20); 
    Enqueue(queue, 30); 
    Enqueue(queue, 40); 
    Enqueue(queue, 50);

    printf("%d dequeued from queue\n\n", Dequeue(queue)); 
  
    printf("Front item is %d\n", Front(queue)); 
    printf("Rear item is %d\n", Rear(queue));
    Display(queue);
	return 0;
}

Queue* CreateQueue(int capacity)
{
	Queue* node = (Queue*)malloc(sizeof(struct queue));
	if(node==NULL)return;
	node->capacity = capacity;
	node->rear = node->size = 0;
	node->first = 0;
	node->front = capacity-1;
	node->array = (int*)malloc(sizeof(int)*capacity);
	return node;
}

void Enqueue(Queue* node,int element)
{
	if(QueueFull(node))return;
	node->array[node->rear]=element;
	node->rear = (node->rear+1)%(node->capacity);
	node->size = node->size+1;
	printf("%d Enqueued\n",element);
	count++;
}

int Dequeue(Queue* node)
{
	if(QueueEmpty(node))return 0;
	int element = node->array[node->front];
	node->front = (node->front+1)%(node->capacity);
	node->size = node->size-1;
	return element;
}

void Display(Queue* node)
{
	if((QueueEmpty(node) || QueueFull(node))==1)return;
	while(node->first!=node->front)
	{
		printf("%d value\n",node->array[node->first]);
		node->first = (node->first+1)%node->capacity;
	}
	printf("%d value\n",node->array[node->first]);
}

int QueueEmpty(Queue* node)
{
	return(node->size == 0);
}

int QueueFull(Queue* node)
{
	return(node->size == node->capacity);
}

int Front(Queue* node)
{
	if(QueueEmpty(node))return 0;
	return node->array[node->front];
}

int Rear(Queue* node)
{
	if(QueueEmpty(node))return 0;
	return node->array[node->rear];
}