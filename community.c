#include<stdio.h>
#include<string.h>
#include"malloc.h"
#include"pool.h"
#include"node.h"
struct community
{
	int no;
	int c_inner;			//Sum of link of weight inside Community
	int inci_c;			//Sum of link of weight incident to nodes in C
	int inci_i;			//Sum of link of weight incident to node i
	int i_inci_c;			//sum of link of weight from i to node in community
	int m;				//sum of link of weight of all nodes in the network
};

void create_tmp_community(char* community, char* nodei, char* nodej)
{
	printf("\tCommunity: %s\t",community);
	printf("Nodei: %s\t",nodei);
	printf("Nodej: %s\n",nodej);
	FILE* file_comm;
	char* node;
	int i,j,size;
	int total=0;
	file_comm=fopen(community,"rb");
	fread(&total,sizeof(int),1,file_comm);
	printf("\tTotal nodes:- %d\n",total);
	for(i=0;i<total;i++)
	//while(fread(&size,sizeof(int),1,file_comm))
	{
		int comm_total;
		fread(&comm_total,sizeof(int),1,file_comm);
		printf("Total Node community:- %d\n",comm_total);
		for(j=0;j<comm_total;j++)
		{
			fread(&size,sizeof(int),1,file_comm);
			node=malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
			printf("\tProcessing %s\n",node);
			if(!strcmp(nodei,node))	
				printf("Hit i\n");
			if(!strcmp(nodej,node))
				printf("Hit j\n");
		}
	}		
	fclose(file_comm);
}
int migrate_node(char* community, char* nodei)
{
	printf("---------------------------------\n");
	printf("Community: %s\t",community);
	printf("Node name: %s\n",nodei);
	FILE* filei;
	char* nodej;
	int size;
	filei=fopen(nodei,"rb");
	while(fread(&size,sizeof(int),1,filei))
	{
		nodej=malloc(sizeof(char)*size+1);
	        memset(nodej,'\0',size+1);	
		fread(nodej,sizeof(char),size,filei);
		//printf("\t%s\n",nodej);
		create_tmp_community(community,nodei,nodej);
	}
	fclose(filei);	
	/*
	FILE* filei;
	char* namei;
	filei=fopen("PHASE1","rb");
	while(fread(&size,sizeof(int),1,filei))
	{
		//printf("SIZE IS %d\n",size);
		namei=malloc(sizeof(char)*size+1);
	        memset(namei,'\0',size+1);	
		fread(namei,sizeof(char),size,filei);
		//printf("CIMM IS %d\n",strlen(namei));
		printf("%s\n",namei);
	
		FILE *file_phase;
		char* name_comm;
		char* name_elem;
		file_phase=fopen("PHASE1","rb");
		int total=0;
		int in_i=0;
		while(fread(&size,sizeof(int),1,file_phase))
		{
			//printf("SIZE IS %d\n",size);
			name_comm=malloc(sizeof(char)*size+1);
		        memset(name_comm,'\0',size+1);	
			fread(name_comm,sizeof(char),size,file_phase);
			//printf("CIMM IS %d\n",strlen(name_comm));
			printf("\t%s\n",name_comm);
		
			FILE* file_comm;
			file_comm=fopen(name_comm,"rb");
			while(fread(&size,sizeof(int),1,file_comm))
			{
				total++;
				//printf("\tSIZE IS %d\n",size);
				name_elem=malloc(sizeof(char)*size+1);
	        		memset(name_elem,'\0',size+1);	
				fread( name_elem,sizeof(char),size,file_comm);
				//printf("\telem size%d\n",strlen(name_elem));
				printf("\t\telem %s\n",name_elem);
				if (!strcmp(namei,name_elem))
				{
					in_i++;		
				}
			}
			fclose(file_comm);
		}
		fclose(file_phase);
		printf("Total weight : %d\n",total);
		printf("in_i 	     : %d\n",in_i);
	}
	fclose(filei);
	*/
}

int phase1(pool* pool1)
{
	FILE *fp;
	fp=fopen("PHASE1_community","wb");
	int i,j;
	int size;
	//pool_ops.display_nodes(pool1);
	struct community comm[pool1->ne_pool];	
	fwrite(&pool1->ne_pool, sizeof(int),1, fp);
	for(i=0;i<pool1->ne_pool;i++)
	{	
		int no_of_nodes;
		no_of_nodes=1;
		fwrite(&no_of_nodes, sizeof(int),1, fp);
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

	FILE* file;
	char* node_name;
	int total=0;
	file=fopen("PHASE1_community","rb");
	fread(&total,sizeof(int),1,file);
	printf("Total nodes:- %d\n",total);
	for(i=0;i<total;i++)
	{
		int comm_total;
		fread(&comm_total,sizeof(int),1,file);
		printf("Total Node community:- %d\n",comm_total);
		for(j=0;j<comm_total;j++)
		{
			fread(&size,sizeof(int),1,file);
			node_name=malloc(sizeof(char)*size+1);
		        memset(node_name,'\0',size+1);	
			fread(node_name,sizeof(char),size,file);
			printf("%s\n",node_name);
			migrate_node("PHASE1_community",node_name);
		
		}
	}
	fclose(file);
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
	//pool_ops.display_nodes(&pool1);
	node_ops.add_element(&pool1.node_obj[0],"node1");
	node_ops.add_element(&pool1.node_obj[0],"node2");
	node_ops.add_element(&pool1.node_obj[1],"node0");
	node_ops.add_element(&pool1.node_obj[1],"node2");
	node_ops.add_element(&pool1.node_obj[2],"node0");
	node_ops.add_element(&pool1.node_obj[2],"node1");
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
