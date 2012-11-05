#include"pool.h"
#include"node.h"
struct community
{
	int c_inner;			//Sum of link of weight inside Community
	int inci_c;			//Sum of link of weight incident to nodes in C
	int inci_i;			//Sum of link of weight incident to node i
	int i_inci_c;			//sum of link of weight from i to node in community
	int m;				//sum of link of weight of all nodes in the network
};
int phase1(pool* pool1)
{
	int i;
	pool_ops.display_nodes(pool1);
	struct community comm[pool1->ne_pool];	
	for(i=0;i<pool1->ne_pool;i++)
	{
		cum[i].c_inner=0;
							
	}	
}

int phase2()
{
}

int main()
{
	int i;
	pool pool1;
	create_pool(&pool1);
	pool_ops.create_node(&pool1,"node0");
	pool_ops.create_node(&pool1,"node1");
	pool_ops.create_node(&pool1,"node2");
	pool_ops.create_node(&pool1,"node3");
	pool_ops.create_node(&pool1,"node4");
	pool_ops.create_node(&pool1,"node5");
	pool_ops.create_node(&pool1,"node6");
	pool_ops.create_node(&pool1,"node7");
	pool_ops.create_node(&pool1,"node8");
	pool_ops.display_nodes(&pool1);
	node_ops.add_element(&pool1.node_obj[0],"node1");
	node_ops.add_element(&pool1.node_obj[0],"node2");
	node_ops.add_element(&pool1.node_obj[1],"node0");
	node_ops.add_element(&pool1.node_obj[1],"node2");
	node_ops.add_element(&pool1.node_obj[2],"node0");
	node_ops.add_element(&pool1.node_obj[2],"node3");
	node_ops.add_element(&pool1.node_obj[3],"node2");
	node_ops.add_element(&pool1.node_obj[4],"node5");
	node_ops.add_element(&pool1.node_obj[4],"node6");
	node_ops.add_element(&pool1.node_obj[5],"node4");
	node_ops.add_element(&pool1.node_obj[5],"node6");
	node_ops.add_element(&pool1.node_obj[5],"node7");
	node_ops.add_element(&pool1.node_obj[6],"node4");
	node_ops.add_element(&pool1.node_obj[6],"node5");
	node_ops.add_element(&pool1.node_obj[7],"node5");
	node_ops.add_element(&pool1.node_obj[7],"node8");
	node_ops.add_element(&pool1.node_obj[8],"node7");
	for(i=0;i<9;i++)
		node_ops.display_element(&pool1.node_obj[i]);
		
	phase1(&pool1);	
}
