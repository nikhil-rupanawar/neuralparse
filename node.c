#include<stdio.h>
#include<string.h>
#include<malloc.h>
int expected;
struct node
{
	char* name;
	int ne_node;
};

typedef struct node node_t;

struct node_ops
{
	int (*add_element)(node_t* node_obj,char* element);
	int (*display_element)(node_t* node_obj);
};


static int add_element_node(node_t* node_obj,char* element)
{
	printf("Hello\n");
	return 1;
}

static int display_element_node(node_t* node_obj)
{
	printf("Hello\n");
	printf("%s\n",node_obj->name);
	return 1;
}

static const struct node_ops node_ops_n = {		//Redefining Functions to operate on node
	.add_element=add_element_node,
	.display_element=display_element_node
};

struct node_pool
{
	struct node *node_obj;
	int ne_pool;			//Number of nodes in pool 
	//int add(char* name,char* element);
	//int find(char* name,char* element);
	//int traverse(char* name);
};

struct node_pool_ops
{
	
};

typedef struct node_pool node_pool_t;
typedef char new_node;
void create_pool(node_pool_t* pool1)
{
	int i;
	pool1->ne_pool=0;	
	expected=5000;
	pool1->node_obj=(struct node*)malloc(sizeof(struct node)*50);		
	
}

int create_node(node_pool_t* pool1,new_node* name)
{
	int len = strlen(name);

	pool1->node_obj[pool1->ne_pool].name = (char*)malloc(sizeof(char)*len);	//Allocate memory to name pointer

	strcpy(pool1->node_obj[pool1->ne_pool].name,name);			//Copy Node name to name pointer in struct node

	pool1->node_obj[pool1->ne_pool].ne_node=pool1->ne_pool;
	pool1->ne_pool++;
}

int display_node(node_pool_t* pool1)
{
	int i;
	for(i=0;i<pool1->ne_pool;i++)
	{
		printf("%s\n",pool1->node_obj[i].name);	
	}
} 

int main()
{
	node_pool_t pool1;//=()malloc(sizeof(struct Node_ops));
	create_pool(&pool1);
	//printf("%d",sizeof(pool1));
	create_node(&pool1,"file2");
	create_node(&pool1,"file3");
	create_node(&pool1,"file4");
	create_node(&pool1,"file5");
	create_node(&pool1,"file6");
	display_node(&pool1);

	//node_ops_n->display_element_node(pool1->node_obj[0]);
	node_ops_n.display_element(&pool1.node_obj[2]);
	//n1.create_node("file3");	
}
