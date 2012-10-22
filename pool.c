#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"pool.h"
#include"node.h"

void create_pool(pool* pool1)
{
	int i;
	pool1->ne_pool=0;	
	pool1->alloted=1;
	printf("Alloted %d\n",pool1->alloted);
	pool1->node_obj=(struct node*)malloc(sizeof(struct node) * pool1->alloted);
	printf("\nPool created\n");
}

//pool_t* reallot_pool(pool_t* pool1)
int reallot_pool(pool* pool1)
{
	int i,j;

	pool pool_obj;
	pool* pool2;
	pool2=&pool_obj;
	pool2->ne_pool=0;
	pool2->alloted=pool1->alloted*2;
	printf("\n***************Realotting Pool with new size %d*****************\n",pool2->alloted);
	pool2->node_obj=(struct node*)malloc(sizeof(struct node) * pool2->alloted);
	printf("->>>>>>>>>Copying old node of pool Started\n\n");
	for(i=0;i<pool1->ne_pool ;i++)					//Copying the old valueof node_obj into new node_obj
	{
		create_node_implemented(pool2,pool1->node_obj[i].name);

		node* node1=pool_ops.get_node(pool2,pool1->node_obj[i].name);	
		printf("Node:- \n");
		printf("Name: %s\n",pool1->node_obj[i].name);
	        printf("elements: %d\n",pool1->node_obj[i].ne_node);
//		if (node1!=NULL) 
//			regexfile(node1,list1->path);	
		
	        for(j=0;j<(pool1->node_obj[i].ne_node);j++)
        	{
			printf("Copying element %d\n",j+1);
			node_ops.add_element(node1, pool1->node_obj[i].element_obj[j].name);
		}		

	}
	printf("\n->>>>>>>>Copying old node of pool Finished\n");
	
	struct node *node_tmp=pool1->node_obj;
	pool1->node_obj=pool2->node_obj;
	pool1->alloted=pool2->alloted;
	free(node_tmp);
	printf("***************Reallocation Pool Ends*********************\n\n");
	return 1;
} 
int create_node_implemented(pool* pool1,char* name)
{
	if(pool1->ne_pool==pool1->alloted)		//If the pool is full reallocate the pool
		reallot_pool(pool1);
	int len = strlen(name);
	printf("Creating Node at pos %d %s\n",pool1->ne_pool,name);
	pool1->node_obj[pool1->ne_pool].name = (char*)malloc(sizeof(char)*len+1);	//Allocate memory to name pointer

	strcpy(pool1->node_obj[pool1->ne_pool].name,name);			//Copy Node name to name pointer in struct node
	pool1->node_obj[pool1->ne_pool].ne_node=0;
	pool1->node_obj[pool1->ne_pool].alloted=0;
	pool1->node_obj[pool1->ne_pool].sno_node=pool1->ne_pool;
	pool1->ne_pool++;
}

node* get_node_implemented(pool* pool1,char* nodename)
{
	int i=0;
	while(1)
	{
		if( i == pool1->ne_pool)
		{
			//printf("Node not present\n");
			return NULL;
		} 
		if (!strcmp(pool1->node_obj[i].name, nodename))
		{
			//printf("Node present\n");
			return &(pool1->node_obj[i]);
		}
	i++;
	}	
}
int display_node_implemented(pool* pool1)
{
	int i;
	printf("-----------------displaying pool nodes---------------\n");
	for(i=0;i<pool1->ne_pool;i++)
	{
		printf("%s\n",pool1->node_obj[i].name);	
	}
} 

//static const struct pool_ops_n pool_ops = {		//Redefining Functions to operate on node
//	.create_node=create_node_implemented,
//	.display_nodes=display_node_implemented
//};

