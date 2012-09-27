#include<stdio.h>
#include<string.h>
#include<malloc.h>
int expected;
struct node
{
	char* name;
	int ne_node;
};

struct node_operations
{
	
};
struct node_pool
{
	struct node *node_obj;
	int ne_pool;			//Number of nodes in pool 
	//int add(char* name,char* element);
	//int find(char* name,char* element);
	//int traverse(char* name);
};

typedef struct node_pool node_pool_t;
typedef char new_node;
void start(node_pool_t* pool1)
{
	int i;
	pool1->ne_pool=0;	
	expected=5000;
	pool1->node_obj=(struct node*)malloc(sizeof(struct node)*50);		
//	struct node* n1;
//	n1=pool1->node_obj;
	//for (i=0; i< 40;i++)
	//{
	//printf("%d\n",pool1->node_obj);
	//pool1->node_obj[i].name="def";
	//pool1->node_obj++;
	//}
	//pool1->node_obj=n1;
	//for (i=0; i< 40;i++)
//	{
	//printf("%s\n",pool1->node_obj->name);
	//pool1->node_obj++;
//	}
	
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
	start(&pool1);
	//printf("%d",sizeof(pool1));
	create_node(&pool1,"file2");
	create_node(&pool1,"file3");
	create_node(&pool1,"file4");
	create_node(&pool1,"file5");
	create_node(&pool1,"file6");
	display_node(&pool1);

	//n1.create_node("file3");	
}
