#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"pool.h"
#include"node.h"
#include"node2.h"
struct community
{
	int no;
	int c_inner;			//Sum of link of weight inside Community
	int inci_c;			//Sum of link of weight incident to nodes in C
	int inci_i;			//Sum of link of weight incident to node i
	int i_inci_c;			//sum of link of weight from i to node in community
	int m;				//sum of link of weight of all nodes in the network
};


void read_community(char* community)
{
	printf("%s\n",community);
	FILE* file_comm;
	int i,j,total,size,comm_total;
	char* node;
	file_comm=fopen(community,"rb");
	fread(&total,sizeof(int),1,file_comm);
	printf("Total Communities:- %d\n",total);
	for(i=0; i<total; i++)			//For each community 
	{
		printf("\tCommunity:- %d\n",i);
		fread(&comm_total,sizeof(int),1,file_comm);
		printf("\t\tTotal N_C : %d\n",comm_total);
		for(j=0;j<comm_total;j++)	//for each nodej in community 
		{
			//size=0;
			fread(&size,sizeof(int),1,file_comm);
			printf("\t\tSIZE:- %d\t",size);
			node=(char*)malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
			printf("Node: %s\n",node);
		}
	}	
}

//IF return == 0 means nodes in same community skip this 
//IF return == 1 means nodes in diff community thus tmp file valid
int find_modularity(char* community, char* nodei)
{
	printf("\tCommunity: %s\t",community);
	printf("Nodei: %s\t",nodei);
	
	return 1;
}

void create_tmp_community(char* community, char* nodei, char* nodej)
{
	printf("\tCommunity: %s\t",community);
	printf("Nodei: %s\t",nodei);
	printf("Nodej: %s\n",nodej);
	FILE* file_comm;
	FILE* file_comm_tmp;
	char* node;
	int i,j,k,size,tmp;
	int total=0;
	file_comm=fopen(community,"rb");
	char* community_tmp = (char*)malloc(sizeof(char)*(strlen(community)+strlen("_tmp")+1));
	strcpy(community_tmp,community);
	strcat(community_tmp,"_tmp");
	file_comm_tmp=fopen(community_tmp,"wb");
	long positionr;		//for holding read position
	long positionw;		//for holding write position
	fread(&total,sizeof(int),1,file_comm);
	printf("\tTotal Communities:- %d\n",total);
		
	//tmp=total;					/*Since After migration no of communities will be less This can be changed at last*/
	tmp=total-1;					/*Since After migration no of communities will be less This can be changed at last*/
	fwrite(&tmp,sizeof(int),1,file_comm_tmp);

	for(i=0; i<total; i++)			//For each community 
	{
		int comm_total;

		long positionw_com,positionr_com;
		positionw_com=ftell(file_comm_tmp);
		positionr_com=ftell(file_comm);
		//printf("\tPositionwrite_com %ld\n",positionw_com);
		//printf("\tPositionread_com %ld\n",positionr_com);

		fread(&comm_total,sizeof(int),1,file_comm);
		printf("\tNode in community:- %d\n",comm_total);
		int flag=0;
		node2 buffer;
		node_ops2.initialize2(&buffer);	
		for(j=0;j<comm_total;j++)	//for each nodej in community 
		{
			//positionr=ftell(file_comm);
			//printf("position ft %ld",positionr);
			fread(&size,sizeof(int),1,file_comm);
			//fwrite(&size,sizeof(int),1,file_comm_tmp);
			node=malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
			//fwrite(node,sizeof(char),size,file_comm_tmp);
			node_ops2.add_element2(&buffer,node,size);	

			printf("\tProcessing %s\n",node);

			if(!strcmp(nodei,node))	
			{
				flag=flag+1;
				printf("Hit i\n");
				//continue;
			}
			if(!strcmp(nodej,node))
			{
				flag=flag+2;
				printf("Hit j\n");
				//continue;
			}
			if(flag==3)
				printf("Same community\n");
		}
		//node_ops2.display_element2(&buffer);
		if(flag==1)	//nodei found
		{
			comm_total--;
			if (comm_total == 0) continue;
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			for(k=0; k < buffer.ne_node; k++)
			{
				printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
				if(!strcmp(buffer.element_obj[k].name, nodei))	continue;
				fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
				fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
			}	
			//Todo  write in buffer insted in file then flush its contents later on
			//fseek(file_comm_tmp,positionw_com,SEEK_SET);
			//printf("**POSITION AFTER NODEI: %ld",ftell(file_comm_tmp));	
		}
		else if(flag==2)//nodej found
		{
			
			comm_total++;
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			for(k=0; k < buffer.ne_node; k++)
			{
				printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
				if(!strcmp(buffer.element_obj[k].name, nodei))	continue;
				fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
				fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
			}	
			size=strlen(nodei);
			fwrite(&size,sizeof(int),1,file_comm_tmp);
			fwrite(nodei,sizeof(char),size,file_comm_tmp);
					
		}
		else if(flag==3)//nodei in same community as nodej
		{	
			//return 0;
		}
		else
		{
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			//printf("\tBuffer %d\n", buffer.ne_node);
			for(k=0; k < buffer.ne_node; k++)
			{
				printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
				fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
				fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
			}	
		
		}
	}		
	fclose(file_comm_tmp);
	free(community_tmp);
	fclose(file_comm);
}
int migrate_node(char* community, char* nodei)
{
	printf("---------------------------------\n");
	printf("Community: %s\t",community);
	printf("Node name: %s\n",nodei);
	char* community_tmp = (char*)malloc(sizeof(char)*(strlen(community)+strlen("_tmp")+1));
	strcpy(community_tmp,community);
	strcat(community_tmp,"_tmp");
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
		int modularity=find_modularity(community_tmp,nodei);
		printf("Modularity:-  %d\n",modularity);
		//read_community("PHASE1_community_tmp");
		break;
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
