#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"node2.h"
int expected;

int initialize_node2(struct node2* node_obj)
{
	node_obj->ne_node=0;
	node_obj->alloted=0;
}
 
int add_element_node2(struct node2* node_obj,char* element_name,int extra)
{
	if (node_obj->ne_node==0 && node_obj->alloted==0)
	{
		//printf("-------------Initializing Memory Allotment to Element----------------\n");
		node_obj->element_obj=(element2*)malloc(sizeof(element2)*1);
		node_obj->alloted=1;
		node_obj->ne_node=0;
	}
	if(node_obj->ne_node==node_obj->alloted)		//If the pool is full reallocate the pool
		reallot_node2(node_obj);
	int len = strlen(element_name);
	//printf("Creating At pos %d\t::\tElement Name:%s\t::\t",node_obj->ne_node,element_name);
	node_obj->element_obj[node_obj->ne_node].name = (char*)malloc(sizeof(char)*len+1);	//Allocate memory to name pointer
	//Copy Node name to name pointer in struct node
	strcpy(node_obj->element_obj[node_obj->ne_node].name,element_name);			
	node_obj->element_obj[node_obj->ne_node].extra = extra;
	node_obj->element_obj[node_obj->ne_node].sno_elem=node_obj->ne_node;
	node_obj->ne_node++;
	//printf("No of Elements: %d\n",node_obj->ne_node);
	return 1;
}

int reallot_node2(struct node2* node_obj)
{
	int i;
	struct node2 node_tmp;
	struct node2* node_obj2;
	node_obj2=&node_tmp;
	node_obj2->ne_node=0;
	node_obj2->alloted=node_obj->alloted*2;
	//printf("Realotted Elements  %d\n",node_obj2->alloted);
	node_obj2->element_obj=(element2 *)malloc(sizeof(element2) * node_obj2->alloted);
	for(i=0;i<node_obj->ne_node ;i++)					//Copying the old valueof node_obj into new node_obj
	{
		add_element_node2(node_obj2,node_obj->element_obj[i].name,node_obj->element_obj[i].extra);	
	}

	element2 *element_tmp=node_obj->element_obj;
	node_obj->element_obj=node_obj2->element_obj;
	node_obj->alloted=node_obj2->alloted;
	free(element_tmp);
	return 1;
}

int display_element_node2(struct node2* node_obj)
{
	int i;
	printf("Name: %s\n",node_obj->name);
	printf("Elements: %d\n",node_obj->ne_node);
	for(i=0;i<node_obj->ne_node;i++)
		printf("\tElement %d\t%s\t%d\n",i,node_obj->element_obj[i].name,node_obj->element_obj[i].extra);	
	return 1;
}

