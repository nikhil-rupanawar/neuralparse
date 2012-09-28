#include<stdio.h>
#include<string.h>
#include<malloc.h>
int expected;
struct element_t
{
	char* name;
	int sno_elem;			//element Sno in the node	
};
typedef struct element_t element;
struct node
{
	char* name;	
	int sno_node;			//Node Sno in the pool
	int ne_node;			//Number of element currently in this node
	element* element_obj;	
};


struct node_ops_n
{
	int (*add_element)(struct node* node_obj,char* element);
	int (*display_element)(struct node* node_obj);
};


static int add_element_node(struct node* node_obj,char* element_name)
{
//	printf("Hello\n");
//	if(pool1->ne_pool==pool1->alloted)		//If the pool is full reallocate the pool
//		reallot_pool(pool1);
	int len = strlen(element_name);
	if (node_obj->ne_node==0)
	{
		printf("Allocating Memory Node\n");
		node_obj->element_obj=(element*)malloc(sizeof(element)*1);
	}
	printf("Creating At pos %d %s\n",node_obj->ne_node,element_name);
	node_obj->element_obj[node_obj->ne_node].name = (char*)malloc(sizeof(char)*len);	//Allocate memory to name pointer
	//strcpy(pool1->node_obj[pool1->ne_pool].name,name);			//Copy Node name to name pointer in struct node
	strcpy(node_obj->element_obj[node_obj->ne_node].name,element_name);			
	node_obj->element_obj->sno_elem=node_obj->ne_node;
	node_obj->ne_node++;
	printf("No of Elements: %d\n",node_obj->ne_node);
	return 1;
}

int reallot_node(struct node* node_obj)
{
}

static int display_element_node(struct node* node_obj)
{
	int i;
	printf("Hello\n");
	printf("Node Name: %s\n",node_obj->name);
	printf("No of Elements: %d\n",node_obj->ne_node);
	for(i=0;i<node_obj->ne_node;i++)
		printf("Element %d\t%s\n",i,node_obj->element_obj[i].name);	
		
	return 1;
}

static const struct node_ops_n node_ops = {		//Redefining Functions to operate on node
	.add_element=add_element_node,
	.display_element=display_element_node
};

struct node_pool_t
{
	struct node *node_obj;
	int ne_pool;			//Number of nodes in pool 
	int alloted;
	//int add(char* name,char* element);
	//int find(char* name,char* element);
	//int traverse(char* name);
};
typedef struct node_pool_t node_pool;

struct node_pool_ops
{
	
};

typedef char new_node;
void create_pool(node_pool* pool1)
{
	int i;
	pool1->ne_pool=0;	
	pool1->alloted=1;
	printf("Alloted %d\n",pool1->alloted);
	pool1->node_obj=(struct node*)malloc(sizeof(struct node) * pool1->alloted);		
}

//node_pool_t* reallot_pool(node_pool_t* pool1)
int reallot_pool(node_pool* pool1)
{
	int i;

	node_pool pool_obj;
	node_pool* pool2;
	pool2=&pool_obj;
	pool2->ne_pool=0;
	pool2->alloted=pool1->alloted*2;
	printf("Realotted Pool %d\n",pool2->alloted);
	pool2->node_obj=(struct node*)malloc(sizeof(struct node) * pool2->alloted);
	for(i=0;i<pool1->ne_pool ;i++)					//Copying the old valueof node_obj into new node_obj
	{
		create_node(pool2,pool1->node_obj[i].name);	
	}
	
	struct node *node_tmp=pool1->node_obj;
	pool1->node_obj=pool2->node_obj;
	pool1->alloted=pool2->alloted;
	free(node_tmp);
	return 1;
} 
int create_node(node_pool* pool1,new_node* name)
{
	if(pool1->ne_pool==pool1->alloted)		//If the pool is full reallocate the pool
		reallot_pool(pool1);
	int len = strlen(name);
	printf("Creating At pos %d %s\n",pool1->ne_pool,name);
	pool1->node_obj[pool1->ne_pool].name = (char*)malloc(sizeof(char)*len);	//Allocate memory to name pointer

	strcpy(pool1->node_obj[pool1->ne_pool].name,name);			//Copy Node name to name pointer in struct node
	pool1->node_obj[pool1->ne_pool].ne_node=0;
	pool1->node_obj[pool1->ne_pool].sno_node=pool1->ne_pool;
	pool1->ne_pool++;
}

int display_node(node_pool* pool1)
{
	int i;
	printf("displaying pool nodes\n");
	for(i=0;i<pool1->ne_pool;i++)
	{
		printf("%s\n",pool1->node_obj[i].name);	
	}
} 

int main()
{
	node_pool pool1;//=()malloc(sizeof(struct Node_ops));
	create_pool(&pool1);
	//printf("%d",sizeof(pool1));
	create_node(&pool1,"file2");
	create_node(&pool1,"file2");
	create_node(&pool1,"file2");
	create_node(&pool1,"file2");

	display_node(&pool1);

	//node_ops_n->display_element_node(pool1->node_obj[0]);
	node_ops.display_element(&pool1.node_obj[2]);
	//n1.create_node("file3");	
	node_ops.add_element(&pool1.node_obj[0],"dat");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.add_element(&pool1.node_obj[0],"cool");
	node_ops.display_element(&pool1.node_obj[0]);
}
