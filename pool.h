struct pool_t
{
	struct node *node_obj;
	int ne_pool;			//Number of nodes in pool 
	int alloted;
	//int add(char* name,char* element);
	//int find(char* name,char* element);
	//int traverse(char* name);
};
typedef struct pool_t pool;

struct pool_ops_n
{
	int (*create_node)(pool* pool1,char* name);
	struct node* (*get_node)(pool* pool1, char* nodename);
	int (*display_nodes)(pool* pool1);
	
};

void create_pool(pool* pool1);
int reallot_pool(pool* pool1);
int create_node_implemented(pool* pool1,char* name);
struct node* get_node_implemented(pool* pool1,char* nodename);
int display_node_implemented(pool* pool1);

static const struct pool_ops_n pool_ops = {		//Redefining Functions to operate on node
	.create_node=create_node_implemented,
	.get_node=get_node_implemented,
	.display_nodes=display_node_implemented
};
