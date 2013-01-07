struct element_t
{
	char* name;
	int extra;
	int sno_elem;			//element Sno in the node	
};
typedef struct element_t element;

struct node
{
	char* name;	
	int sno_node;			//Node Sno in the pool
	int ne_node;			//Number of element currently in this node
	int alloted;
	element* element_obj;	
};
typedef struct node node;

struct node_ops_n
{
	int (*add_element)(struct node* node_obj,char* element);
	int (*display_element)(struct node* node_obj);
};

int add_element_node(struct node* node_obj,char* element_name);
int reallot_node(struct node* node_obj);
int display_element_node(struct node* node_obj);

static const struct node_ops_n node_ops = {		//Redefining Functions to operate on node
	.add_element=add_element_node,
	.display_element=display_element_node
};
