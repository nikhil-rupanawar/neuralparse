#include<stdio.h>
#include<string.h>
#include<malloc.h>
int expected;
struct node
{
	char* name;
	int ne;
};

struct node_operations
{
	
};
struct node_pool
{
	struct node *node_obj;
	int ne;
	int expected;	
	//int add(char* name,char* element);
	//int find(char* name,char* element);
	//int traverse(char* name);
};

typedef struct node_pool node_pool_t;
typedef char new_node;
void start(node_pool_t* pool1)
{
	pool1->ne=0;	
	expected=5000;
	pool1->node_obj=(struct node*)malloc(sizeof(struct node)*expected);		
	printf("%d\n",sizeof(pool1->nodeobj));
}

int create_node(node_pool_t* pool1,new_node* name)
{	
	//strcpy(name,pool1->node_obj[pool1->ne]->name);
	//strcpy(name,pool1->node_obj[0]->name);
	pool1->node_obj->ne=pool1->ne;
	pool1->ne++;
}


int main()
{
	node_pool_t pool1;//=()malloc(sizeof(struct Node_ops));
	start(&pool1);
	printf("%d",sizeof(pool1));
	create_node(&pool1,"file2");

	//n1.create_node("file3");	
}
