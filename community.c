#include<stdio.h>
#include<string.h>
#include"malloc.h"
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
	FILE *fp;
	fp=fopen("PHASE1","wb");
	int i,j;
	int size;
	//pool_ops.display_nodes(pool1);
	struct community comm[pool1->ne_pool];	
	for(i=0;i<pool1->ne_pool;i++)
	{
		size=strlen(pool1->node_obj[i].name);
		printf("SIZE IS %d\n",size);
		fwrite(&size, sizeof(int),1, fp);
		fwrite(pool1->node_obj[i].name, sizeof(char),size, fp);
		//fprintf(fp, "%s\n",pool1->node_obj[i].name);
		FILE* fy;
		fy=fopen(pool1->node_obj[i].name,"wb");
		for(j=0;j<pool1->node_obj[i].ne_node;j++)
		{
			size=strlen(pool1->node_obj[i].element_obj[j].name)/sizeof(char);
			fwrite(&size, sizeof(int),1, fy);
			fwrite(pool1->node_obj[i].element_obj[j].name, sizeof(char),size, fy);
			//fprintf(fy, "%s\n",pool1->node_obj[i].element_obj[j].name);
		}
		fclose(fy);	
	}	
	fclose(fp);
	FILE *file_phase;
	char* name_comm;
	char* name_elem;
	printf("1. %u\n",name_comm);
	printf("2. %u\n",name_elem);
	file_phase=fopen("PHASE1","rb");

	while(fread( &size,sizeof(int),1,file_phase))
	{
		printf("SIZE IS %d\n",size);
		name_comm=malloc(sizeof(char)*size+1);
		fread( name_comm,sizeof(char),size,file_phase);
		printf("CIMM IS %d\n",strlen(name_comm));
		printf("%s\n",name_comm);
		
		FILE* file_comm;
		file_comm=fopen(name_comm,"rb");
		while(fread( &size,sizeof(int),1,file_comm))
		{
			name_elem=malloc(sizeof(char)*size+1);
			fread( name_elem,sizeof(char),size,file_comm);
			printf("\telem size%d\n",strlen(name_elem));
			printf("\telem %s\n",name_elem);
		}
		fclose(file_comm);
				
	}
	fclose(file_phase);


}

int phase2()
{
}

int main()
{
	int i;
	pool pool1;
	create_pool(&pool1);
	pool_ops.create_node(&pool1,"ddddnode0");
	pool_ops.create_node(&pool1,"node1");
	pool_ops.create_node(&pool1,"node2");
	pool_ops.create_node(&pool1,"node3");
	pool_ops.create_node(&pool1,"node4");
	pool_ops.create_node(&pool1,"node5");
	pool_ops.create_node(&pool1,"node6");
	pool_ops.create_node(&pool1,"node7");
	pool_ops.create_node(&pool1,"node8");
	//pool_ops.display_nodes(&pool1);
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
	//for(i=0;i<9;i++)
	//	node_ops.display_element(&pool1.node_obj[i]);
		
	phase1(&pool1);	
}
