#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"pool.h"
#include"node.h"
#include"node2.h"
#include"hashlist.h"
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
	file_comm=fopen(community,"rb");
	fread(&total,sizeof(int),1,file_comm);
	printf("Total Communities:- %d\n",total);
	int m;
	for(i=0; i<total; i++)			//For each community 
	{
		printf("\tCommunity:- %d\n",i);
		fread(&comm_total,sizeof(int),1,file_comm);
		printf("\t\tTotal N_C : %d\n",comm_total);
		for(j=0;j<comm_total;j++)	//for each nodej in community 
		{
			char* node;
			fread(&size,sizeof(int),1,file_comm);
			printf("\t\tSIZE:- %d\t",size);
			node=(char*)malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
			printf("Node: %s\n",node);
		}
	}	
	fclose(file_comm);	
}

/*
 * Function is used to calculate the modularity of nodei in the community
 * 
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei	: Node which modularity is to be calculated
 *
 * */
int find_modularity(char* community, char* nodei)
{
	//printf("\tCommunity: %s\t",community);
	//printf("Nodei: %s\t",nodei);
	printf("%s\n",community);
	FILE* file_comm;
	int i,j,total,size,comm_total;
	file_comm=fopen(community,"rb");
	fread(&total,sizeof(int),1,file_comm);
	//printf("Total Communities:- %d\n",total);
	int m=0;
	int inci_i=0;
	int c_inner=0; 
	for(i=0; i<total; i++)			//For each community 
	{
		long position;
		//printf("\tCommunity:- %d\n",i);
		fread(&comm_total,sizeof(int),1,file_comm);
		//printf("\t\tTotal N_C : %d\n",comm_total);
		position=ftell(file_comm);
		for(j=0;j<comm_total;j++)	//for each nodej in community 
		{
			char* node;
			fread(&size,sizeof(int),1,file_comm);
			//printf("\t\tSIZE:- %d\t",size);
			node=(char*)malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
	
			/*When nodei is found then iterate over ity community to find community weight*/		
			if (!strcmp(nodei,node))		/*Checking if this node is nodei*/
			{
				int a;
				long tmp_position;
				tmp_position=ftell(file_comm);

//Tmp_code Start
				hashlist listlink;
				hashlist_ops.hashlist_initialize(&listlink);
				hashlist listnode;
				hashlist_ops.hashlist_initialize(&listnode);
				
				fseek(file_comm,position,SEEK_SET);	/*Set File ptr to the position after no of elements in the nodei community*/
				for(a=0;a<comm_total;a++)	//for each nodej in community 
				{
					char* node;
					fread(&size,sizeof(int),1,file_comm);
					node=(char*)malloc(sizeof(char)*size+1);
				       	memset(node,'\0',size+1);	
					fread(node,sizeof(char),size,file_comm);
					hashlist_ops.hashlist_add(&listnode,node,0,0,0);	/*Treat 2 argument as cntr and third one as valid bit */

					FILE* file_node;
					file_node=fopen(node,"rb");
					while(fread(&size,sizeof(int),1,file_node))
					{
						//printf("Size: %d\n",size);
						char* link;
						link=(char*)malloc(sizeof(char)*size+1);
				        	memset(link,'\0',size+1);	
						fread(link,sizeof(char),size,file_node);
						
						/*Adding links to the addlist */
						hash* hashnode;
						hashnode = hashlist_ops.hashlist_findhash(&listlink,link);						
						if ( hashnode == NULL )
						{
							//if (!strcmp(,link))
							hashlist_ops.hashlist_add(&listlink,link,1,0,0);	/*Treat 2 argument as cntr and third one as valid bit */
							printf("$$$$$$$$$$$$$$$$$$$$$$ NULL    : %s \n",link);
						}
						else
						{
							++hashnode->x;					/*Incrementing counter of links*/
							printf("<<<<<<<<<<<<<<<<<<<<<< NOT null: %s \n",link);
						} 
						//hashlist_ops.hashlist_add(&list,"A",3,4,4);	/*Treat 2 argument as cntr and third one as valid bit */

						free(link);	
					}
					fclose(file_node);

					free(node);
				}

				/*
 				* Now hashlink contains all list of link and their cntr,
 				* hashnode contain all the nodes in community
 				* */
				
				/*Link inside the community*/	
				int s;		
				if (listlink.alloted == 0) return;
				for(s=0; s < listlink.size; s++)
				{
					if(listlink.Hash[s].valid == 1)
					{
						hash* tmp;
						printf("\tName   :- %s\n",listlink.Hash[s].key_name);
						printf("\tCoords :- %d %d %d\n",listlink.Hash[s].x,listlink.Hash[s].y,listlink.Hash[s].z);
						tmp = hashlist_ops.hashlist_findhash(&listnode,listlink.Hash[s].key_name);

						if ( tmp != NULL )	
							c_inner += listlink.Hash[s].x;
							
					}			
				}
					
				fseek(file_comm,tmp_position,SEEK_SET);
//TMP_code Ends
					
			}			
	
			//printf("Node: %s\n",node);
			FILE* file_node;
			file_node=fopen(node,"rb");
			while(fread(&size,sizeof(int),1,file_node))
			{
				//printf("Size: %d\n",size);
				char* link;
				link=(char*)malloc(sizeof(char)*size+1);
		        	memset(link,'\0',size+1);	
				fread(link,sizeof(char),size,file_node);
				if (!strcmp(nodei,link)) inci_i++;			/*If destination is nodei increment inci_i */
				//printf("Link :- %s\n", link);
				m++;
				free(link);	
			}
			fclose(file_node);
			free(node);
		}
	}
	printf("Total weight	: %d\n",m);
	printf("Inci 2 nodei	: %d\n",inci_i);
	printf("Weight community: %d\n",c_inner);
	fclose(file_comm);	
	return 1;
}

void create_tmp_community(char* community, char* nodei, char* nodej)
{
	//printf("\tCommunity: %s\t",community);
	//printf("Nodei: %s\t",nodei);
	printf("Checking neighbour: %s\n",nodej);
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
	long position;		//for holding read position
	long positionw;		//for holding write position
	fread(&total,sizeof(int),1,file_comm);
	//printf("\tTotal Communities:- %d\n",total);
		
	position=ftell(file_comm_tmp);
	fwrite(&total,sizeof(int),1,file_comm_tmp);		/* Writing Total no of communities. This can be changed later as community will shrink when a node
								is removed from its community and added to other(Exception if the community fromn which node is removed 								contains some elements then total communities will not change */

	for(i=0; i<total; i++)					//For each community 
	{
		int comm_total;

		fread(&comm_total,sizeof(int),1,file_comm);
		//printf("\tNode in community:- %d\n",comm_total);
		int flag=0;
		node2 buffer;
		node_ops2.initialize2(&buffer);	
		for(j=0;j<comm_total;j++)	//for each nodej in community 
		{
			fread(&size,sizeof(int),1,file_comm);
			node=malloc(sizeof(char)*size+1);
	        	memset(node,'\0',size+1);	
			fread(node,sizeof(char),size,file_comm);
			node_ops2.add_element2(&buffer,node,size);	

			//printf("\tProcessing %s\n",node);

			if(!strcmp(nodei,node))	
			{
				flag=flag+1;
				//printf("Hit i\n");
			}
			if(!strcmp(nodej,node))
			{
				flag=flag+2;
				//printf("Hit j\n");
			}
		}
		//node_ops2.display_element2(&buffer);
		if(flag==1)	//nodei found
		{
			comm_total--;
			//printf("\tPosition_com %ld\n",position);
			if (comm_total == 0)
			{
				long position_tmp=ftell(file_comm_tmp);
				fseek(file_comm_tmp,position,SEEK_SET);
				//printf("**POSITION AFTER NODEI: %ld\n",ftell(file_comm_tmp));						
				tmp=total-1;					/*Since After migration no of communities will be less*/
				fwrite(&tmp,sizeof(int),1,file_comm_tmp);
				position=ftell(file_comm_tmp);
				fseek(file_comm_tmp,position_tmp,SEEK_SET);
				//printf("**POSITION AFTER NODEI: %ld\n",ftell(file_comm_tmp));						
 				continue;
			}
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			for(k=0; k < buffer.ne_node; k++)
			{
				//printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
				if(!strcmp(buffer.element_obj[k].name, nodei))	continue;	/*To skip adding nodei to its previous community*/
				fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
				fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
			}	
		}
		else if(flag==2)	//nodej found
		{
			
			comm_total++;
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			for(k=0; k < buffer.ne_node; k++)
			{
				//printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
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
				printf("Same community\n");
				//return;
		}
		else
		{
			fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
			for(k=0; k < buffer.ne_node; k++)
			{
				//printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);	
				fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
				fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
			}	
		
		}
	}		
	fclose(file_comm_tmp);
	free(community_tmp);
	fclose(file_comm);
}


/*
 *Function is used to migrate a node to a community where it gains maximum modularity including the existing one
 *
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei	: Node to migrate
 *
 * */
int migrate_node(char* community, char* nodei)
{
	printf("---------------------------------\n");
	//printf("Community: %s\t",community);
	printf("Node To migrate:    %s\n",nodei);
	char* community_tmp = (char*)malloc(sizeof(char)*(strlen(community)+strlen("_tmp")+1));
	strcpy(community_tmp,community);
	strcat(community_tmp,"_tmp");
	FILE* filei;
	char* nodej;
	int size;
	filei=fopen(nodei,"rb");		/*Reading file of nodei for its neighbours*/
	while(fread(&size,sizeof(int),1,filei))
	{
		nodej=malloc(sizeof(char)*size+1);			/*Neighbour of nodei*/
	        memset(nodej,'\0',size+1);	
		fread(nodej,sizeof(char),size,filei);
		//printf("\t%s\n",nodej);
		//create_tmp_community(community_tmp,"node2","node8");
		create_tmp_community(community,nodei,nodej); 		/*Create a tmp file for new community*/
		int modularity=find_modularity(community_tmp,nodei);	/*Get modularity of nodej*/ 
		printf("Modularity:-  %d\n",modularity);
		//read_community(community_tmp);
		//read_community("PHASE1_community_tmp_tmp");
	}
	fclose(filei);	
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
	//printf("Total nodes:- %d\n",total);
	for(i=0;i<total;i++)
	{
		int comm_total;
		fread(&comm_total,sizeof(int),1,file);
		//printf("Total Node community:- %d\n",comm_total);
		for(j=0;j<comm_total;j++)
		{
			fread(&size,sizeof(int),1,file);
			node_name=malloc(sizeof(char)*size+1);
		        memset(node_name,'\0',size+1);	
			fread(node_name,sizeof(char),size,file);
			//printf("%s\n",node_name);
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
