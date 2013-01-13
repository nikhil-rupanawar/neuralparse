#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include"queue.h"

int queue_initialize(queue* q1)
{
	q1->front=NULL;
	q1->rear=NULL;
	q1->ne=0;	
}
int queue_add(queue* q1, char* key,int weight,int no, int x1, int x2, int y1, int y2)
{
	queue_node* tmp = malloc(sizeof(queue_node));
	tmp->key=malloc(sizeof(strlen(key)*sizeof(char)));
	strcpy(tmp->key,key);
	tmp->weight=weight;
	tmp->no=no;
	tmp->x1=x1;	
	tmp->x2=x2;	
	tmp->y1=y1;	
	tmp->y2=y2;
	if (q1->front==NULL)
	{
		q1->ne=1;
		q1->rear=tmp;
		q1->front=tmp;
		q1->rear->next=NULL;
		return 1;
		//printf("Key:- %s\n",q1->front->key);
		//printf("x1: %d\tx2: %d\ty1: %d\ty2: %d\n",q1->front->x1,q1->front->x2,q1->front->y1,q1->front->y2);
	}
	else // if (q1->front == q1->rear)
	{
		q1->ne++;
		q1->rear->next=tmp;
		q1->rear=tmp;
		q1->rear->next=NULL;
	}
	//tmp->next=q1->node;
}

int queue_display(queue* q1)
{
	queue_node* tmp;
	tmp=q1->front;
	printf("No Of elemets in queue : %d\n",q1->ne);
	printf("-----------------Queue Elements---------------------\n");
	while(q1->front != NULL)
	{
		printf("Key:- %s\nWeight: %d\tNodes: %d\n",q1->front->key,q1->front->weight,q1->front->no);
		printf("x1: %d\tx2: %d\ty1: %d\ty2: %d\n",q1->front->x1,q1->front->x2,q1->front->y1,q1->front->y2);
		q1->front=q1->front->next;
	}
	q1->front=tmp;
	printf("-----------------------------------------------------\n");
}

queue_node* queue_remove(queue* q1)
{
	if (q1->front == NULL) return NULL;	
	queue_node* tmp = q1->front;
	if (q1->front->next ==NULL)
	{
		q1->front =NULL;
		q1->rear=NULL;
	}
	else 
	{
		q1->front = q1->front->next;
	}
	q1->ne--;
	return tmp;	
}
queue_node* queue_get(queue* q1,int pos)
{
	int i=1;	
	queue_node* tmp = q1->front;
	while(tmp != NULL && i != pos)
	{			
		tmp=tmp->next;
		i++;
	}
	if ( i != pos)
	{
		printf("Failure: get_node\n");
		return NULL;
	}
	return tmp;
}
int queue_update(queue* q1,int pos,char* key,int weight, int no, int x1, int x2, int y1, int y2)
{
	int i=1;	
	queue_node* tmp;
	tmp=q1->front;
	while(q1->front != NULL && i != pos)
	{			
		q1->front=q1->front->next;
		i++;
	}
	if ( i == pos)
	{
		free(q1->front->key);
		free(q1->front);
		queue_node* tmp = malloc(sizeof(queue_node));
		tmp->key=malloc(sizeof(strlen(key)*sizeof(char)));
		strcpy(tmp->key,key);
		tmp->weight=weight;
		tmp->no=no;
		tmp->x1=x1;	
		tmp->x2=x2;	
		tmp->y1=y1;	
		tmp->y2=y2;
		q1->front=tmp;			
	}
	else 
	{
		printf("Failure: update_node\n");
		return 0;
	}
	q1->front=tmp;
	return 1;
}
/*
int main()
{
	queue q1;
	queue_initialize(&q1);
	queue_add(&q1,"My name",12,1,0,1,1,2);
	queue_add(&q1,"My name",13,1,0,1,1,2);
	queue_add(&q1,"is",1233,0,1,1,1,2);
	queue_add(&q1,"TRY",33,0,1,1,1,2);
	queue_display(&q1);
	queue_node* n1 = (queue_node*)queue_remove(&q1);
	printf("R1 %s",n1->key);	
	queue_update(&q1,2,"TRYless",23232,0,1,212,12,2111);
	queue_display(&q1);	
	queue_node* n2 = (queue_node*)queue_get(&q1,3);
	printf("GET Name:- %s\n",n2->key);
	printf("x1: %d\tx2: %d\ty1: %d\ty2: %d\n",n2->x1,n2->x2,n2->y1,n2->y2);
	queue_display(&q1);	
}*/
