struct element_t2
{
	char* name;
	int extra;
	int sno_elem;			//element Sno in the node	
};
typedef struct element_t2 element2;

struct node2
{
	char* name;	
	int sno_node;			//Node Sno in the pool
	int ne_node;			//Number of element currently in this node
	int alloted;
	element2* element_obj;	
};
typedef struct node2 node2;

struct node_ops_n2
{
	int (*add_element2)(struct node2* node_obj,char* element,int extra);
	int (*display_element2)(struct node2* node_obj);
	int (*initialize2)(struct node2* node_obj);
};

int add_element_node2(struct node2* node_obj,char* element_name,int extra);
int reallot_node2(struct node2* node_obj);
int display_element_node2(struct node2* node_obj);
int initialize_node2(struct node2* node_obj);

static const struct node_ops_n2 node_ops2 = {		//Redefining Functions to operate on node
	.add_element2=add_element_node2,
	.display_element2=display_element_node2,
	.initialize2=initialize_node2
};
