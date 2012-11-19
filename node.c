#include<stdio.h>
#include<string.h>
#include<malloc.h>
//#include"pool.h"
#include"node.h"
int expected;

int add_element_node(struct node* node_obj,char* element_name)
{
	if (node_obj->ne_node==0 && node_obj->alloted==0)
	{
		//printf("-------------Initializing Memory Allotment to Element----------------\n");
		node_obj->element_obj=(element*)malloc(sizeof(element)*1);
		node_obj->alloted=1;
		node_obj->ne_node=0;
	}
	if(node_obj->ne_node==node_obj->alloted)		//If the pool is full reallocate the pool
		reallot_node(node_obj);
	int len = strlen(element_name);
	//printf("Creating At pos %d\t::\tElement Name:%s\t::\t",node_obj->ne_node,element_name);
	node_obj->element_obj[node_obj->ne_node].name = (char*)malloc(sizeof(char)*len+1);	//Allocate memory to name pointer
	//strcpy(pool1->node_obj[pool1->ne_pool].name,name);			//Copy Node name to name pointer in struct node
	strcpy(node_obj->element_obj[node_obj->ne_node].name,element_name);			
	//node_obj->element_obj->sno_elem=node_obj->ne_node;
	node_obj->element_obj[node_obj->ne_node].sno_elem=node_obj->ne_node;
	node_obj->ne_node++;
	//printf("No of Elements: %d\n",node_obj->ne_node);
	return 1;
}

int reallot_node(struct node* node_obj)
{
	int i;
	struct node node_tmp;
	struct node* node_obj2;
	node_obj2=&node_tmp;
	node_obj2->ne_node=0;
	node_obj2->alloted=node_obj->alloted*2;
	//printf("Realotted Elements  %d\n",node_obj2->alloted);
	node_obj2->element_obj=(element *)malloc(sizeof(element) * node_obj2->alloted);
	for(i=0;i<node_obj->ne_node ;i++)					//Copying the old valueof node_obj into new node_obj
	{
		add_element_node(node_obj2,node_obj->element_obj[i].name);	
	}

	element *element_tmp=node_obj->element_obj;
	node_obj->element_obj=node_obj2->element_obj;
	node_obj->alloted=node_obj2->alloted;
	free(element_tmp);
	return 1;
}

int display_element_node(struct node* node_obj)
{
	int i;
	printf("Name: %s\n",node_obj->name);
	printf("Elements: %d\n",node_obj->ne_node);
	for(i=0;i<node_obj->ne_node;i++)
		printf("\tElement %d\t%s\n",i,node_obj->element_obj[i].name);	
	return 1;
}

