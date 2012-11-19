#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"pool.h"
#include"node.h"
#include"node2.h"
#include"hashlist.h"
#include"community.h"
int phase_no;
struct info
{
        int no;
        int c_inner;                    //Sum of link of weight inside Community
        int inci_c;                     //Sum of link of weight incident to nodes in C
        int inci_i;                     //Sum of link of weight incident to node i
        int i_inci_c;                   //sum of link of weight from i to node in community
        int weight;                     //sum of link of weight of all nodes in the network
};

void read_community(char* community)
{
        //printf("%s\n",community);
        int i,j,total,size,comm_total;
        FILE* file_comm=fopen(community,"rb");

        fread(&total,sizeof(int),1,file_comm);
        printf("Total Communities:- %d\n",total);
        int m;
        for(i=0; i<total; i++)                  //For each community
        {
                printf("\tCommunity:- %d\n",i);
                fread(&comm_total,sizeof(int),1,file_comm);
                printf("\t\tTotal N_C : %d\n",comm_total);
                for(j=0;j<comm_total;j++)       //for each nodej in community
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

float find_modularity(char* community, char* nodei)
{
        //printf("\tCommunity: %s\t",community);
        //printf("Nodei: %s\t",nodei);
       	// printf("%s\n",community);
        int i,j,total,size,comm_total;
        FILE* file_comm=fopen(community,"rb");

        fread(&total,sizeof(int),1,file_comm);
        //printf("Total Communities:- %d\n",total);
        int m=0;
        int inci_i=0;
        int c_inner=0;
	int i_inci_c=0;
        for(i=0; i<total; i++)                  //For each community
        {
                long position;
                //printf("\tCommunity:- %d\n",i);
                fread(&comm_total,sizeof(int),1,file_comm);
                //printf("\t\tTotal N_C : %d\n",comm_total);
                position=ftell(file_comm);
                for(j=0;j<comm_total;j++)       //for each nodej in community
                {
                        char* node;
                        fread(&size,sizeof(int),1,file_comm);
                        //printf("\t\tSIZE:- %d\t",size);
                        node=(char*)malloc(sizeof(char)*size+1);
                        memset(node,'\0',size+1);      
                        fread(node,sizeof(char),size,file_comm);

                        /*When nodei is found then iterate over its community to find community weight*/ 
                        if (!strcmp(nodei,node))                /*Checking if this node is nodei*/
                        {
                                int a;
                                long tmp_position;
                                tmp_position=ftell(file_comm);

//Tmp_code Start
                                hashlist listlink;
                                hashlist_ops.hashlist_initialize(&listlink);
                                hashlist listnode;
                                hashlist_ops.hashlist_initialize(&listnode);
				
                                fseek(file_comm,position,SEEK_SET);     /*Set File ptr to the position after no of elements in the
									 nodei community*/
                                for(a=0;a<comm_total;a++)       //for each nodej in community
                                {
                                        char* node;
                                        fread(&size,sizeof(int),1,file_comm);
                                        node=(char*)malloc(sizeof(char)*size+1);
                                        memset(node,'\0',size+1);      
                                        fread(node,sizeof(char),size,file_comm);
                                        hashlist_ops.hashlist_add(&listnode,node,0,0,0);        /* Treat 2 argument as cntr */

                                        FILE* file_node=fopen(node,"rb");
                                        while(fread(&size,sizeof(int),1,file_node))
                                        {
                                                //printf("Size: %d\n",size);
                                                char* link = (char*)malloc(sizeof(char)*size+1);
                                                memset(link,'\0',size+1);      
                                                fread(link,sizeof(char),size,file_node);
                                               
                                                /*Adding links to the addlist */
                                                hash* hashnode = hashlist_ops.hashlist_findhash(&listlink,link);                                              
                                                if ( hashnode == NULL )
                                                {
                                                        //if (!strcmp(,link))
                                                        if(!strcmp(node,nodei))
                                                        	hashlist_ops.hashlist_add(&listlink,link,1,1,0);  /* Treat 2 argument as 
															cntr,3 arg as
															cntr for nodei */
							else	
                                                       		hashlist_ops.hashlist_add(&listlink,link,1,0,0);        /* Treat 2 argument as cntr */
                                                        //printf("$$$$$$$$$$$$$$$$$$$$$$ NULL    : %s \n",link);
                                                }
                                                else
                                                {
                                                        if(!strcmp(node,nodei))
                                                        	++hashnode->y;                                  /*Incrementing counter of links of nodei*/
                                                        ++hashnode->x;                                  /*Incrementing counter of links*/
                                                        //printf("<<<<<<<<<<<<<<<<<<<<<< NOT null: %s \n",link);
                                                }
                                                //hashlist_ops.hashlist_add(&list,"A",3,4,4);   /*Treat 2 argument as cntr and third one as valid bit */

                                                free(link);    
                                        }
                                        fclose(file_node);

                                        free(node);
                                }

                                /*
                                * Now hashlink contains all list of link and their cntr,
                                * hashnode contain all the nodes in community of nodei
                                * */
                               
                                /*Link inside the community*/  
                                int s;          
                                if (listlink.alloted == 0) return;
                                for(s=0; s < listlink.size; s++)
                                {
                                        if(listlink.Hash[s].valid == 1)
                                        {
                                                hash* tmp;
                                               // printf("\tName   :- %s\n",listlink.Hash[s].key_name);
                                               // printf("\tCoords :- %d %d %d\n",listlink.Hash[s].x,listlink.Hash[s].y,listlink.Hash[s].z);
                                                tmp = hashlist_ops.hashlist_findhash(&listnode,listlink.Hash[s].key_name);

                                                if ( tmp != NULL )      
                                                {
						        c_inner += listlink.Hash[s].x;
							if (listlink.Hash[s].y > 0)
								i_inci_c+=listlink.Hash[s].y;		
                                                }       
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
                                if (!strcmp(nodei,link)) inci_i++;                      /*If destination is nodei increment inci_i */
                                m++;
                                free(link);    
                        }
                        fclose(file_node);
                        free(node);
                }
        }
        printf("Total weight     : %d\n",m);
        printf("Inci 2 nodei     : %d\n",inci_i);
        printf("nodei 2 community: %d\n",i_inci_c);
        printf("Weight community : %d\n",c_inner);
        fclose(file_comm);     
	float tmp1,tmp2;
	tmp1 = ((float)c_inner+i_inci_c+i_inci_c)/(m+m);
	tmp1 = tmp1 - ((1+(float)inci_i)/(m+m))*((1+(float)inci_i)/(m+m));
	tmp2 = ((float)c_inner)/m+m;
	tmp2 = tmp2 - (1/m+m)*(1/m+m);
	tmp2 = tmp2 - ((float)inci_i/m+m)*((float)inci_i/m+m);
	tmp1=tmp1-tmp2;
        return tmp1;
}

/*
 * Function is used to create a temprary community file by migrating nodei tovnodej community
 *
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei     : Node which is to be transferred
 * 3. nodej     : Node to which community nodei will be transferred
 *
 * Return value:-
 * 0 means comm(nodei) == comm (nodej)
 * 1 Community file successfully created
 * */
int create_tmp_community(char* community, char* nodei, char* nodej)
{
        //printf("\tCommunity: %s\t",community);
        //printf("Nodei: %s\t",nodei);
        printf("Checking neighbour: %s\n",nodej);
        FILE* file_comm;				/* It will hold original commumnity file for reading */
        FILE* file_comm_tmp;				/* It will hold tmp community file for writing */
        char* node;
        int i,j,k,size,tmp;
        int total=0;
        file_comm=fopen(community,"rb");
        char* community_tmp = (char*)malloc(sizeof(char)*(strlen(community)+strlen("_tmp")+1));
        strcpy(community_tmp,community);
        strcat(community_tmp,"_tmp");
        file_comm_tmp=fopen(community_tmp,"wb");
        long position;         				//for holding read position
        long positionw;         			//for holding write position

        fread(&total,sizeof(int),1,file_comm);
        //printf("\tTotal Communities:- %d\n",total);
               
        position=ftell(file_comm_tmp);
        fwrite(&total,sizeof(int),1,file_comm_tmp);     /* Writing Total no of communities. This can be changed later as community will shrink when a node
                                                        is removed from its community and added to other(Exception if the community fromn which node is removed                                                         contains some elements then total communities will not change */
        for(i=0; i<total; i++)                         	//For each community
        {
                int comm_total;

                fread(&comm_total,sizeof(int),1,file_comm);			/* Get the total no of elements in the community */
                //printf("\tNode in community:- %d\n",comm_total);
                int flag=0;
                node2 buffer;
                node_ops2.initialize2(&buffer);
                for(j=0; j<comm_total; j++)       				//for each nodej in community
                {
                        fread(&size,sizeof(int),1,file_comm);
                        node=(char*)malloc(sizeof(char)*size+1);
                        memset(node,'\0',size+1);      
                        fread(node,sizeof(char),size,file_comm);
                        node_ops2.add_element2(&buffer,node,size);      

                        //printf("\tProcessing %s\n",node);

                        if(!strcmp(nodei,node))					/* Nodei found */
                        {
                                flag=flag+1;
                        }
                        if(!strcmp(nodej,node))					/* Nodej found */
                        {
                                flag=flag+2;
                        }
                }

                if(flag==1)    							//nodei found
                {
                        comm_total--;
                        //printf("\tPosition_com %ld\n",position);
                        if (comm_total == 0)
                        {
                                long position_tmp=ftell(file_comm_tmp);
                                fseek(file_comm_tmp,position,SEEK_SET);
                                //printf("**POSITION AFTER NODEI: %ld\n",ftell(file_comm_tmp));                                        
                                tmp=total-1;                                    /*Since After migration no of communities will be less*/
				//printf("setting total %d\n",tmp);
                                fwrite(&tmp,sizeof(int),1,file_comm_tmp);
                                //position=ftell(file_comm_tmp);	doubt
                                fseek(file_comm_tmp,position_tmp,SEEK_SET);
                                //printf("**POSITION AFTER NODEI: %ld\n",ftell(file_comm_tmp));                                        
                                continue;
                        }
                        fwrite(&comm_total,sizeof(int),1,file_comm_tmp);	
			//printf("Comparing comm total: %d buff nenode: %d\n",comm_total,buffer.ne_node);
                        for(k=0; k < buffer.ne_node; k++)
                        {
                                //printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);    
                                if(!strcmp(buffer.element_obj[k].name, nodei))  continue;       /*To skip adding nodei to its previous community*/
                                fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
                                fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
                        }      
                }
                else if(flag==2)        					//nodej found
                {
                       
                        comm_total++;
                        fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
                        for(k=0; k < buffer.ne_node; k++)
                        {
                                //printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);    
                                if(!strcmp(buffer.element_obj[k].name, nodei))  continue;
                                fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
                                fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
                        }      
                        size=strlen(nodei);
                        fwrite(&size,sizeof(int),1,file_comm_tmp);
                        fwrite(nodei,sizeof(char),size,file_comm_tmp);
                                       
                }
                else if(flag==3)						//nodei in same community as nodej
                {
                                //printf("Same community\n");
				return 0;
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
	return 1;
}

/*
 *Function is used to migrate a node to a community where it gains maximum modularity including the existing one
 *
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei     : Node to migrate
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

        char* nodej;
        int size;
        FILE* filei = fopen(nodei,"rb");                /*Reading file of nodei for its neighbours*/
	float max_modularity=0.0f;
	char* node_max=NULL;
        while(fread(&size,sizeof(int),1,filei))
        {
		
                nodej = malloc(sizeof(char) * size+1);                      /*Neighbour of nodei*/
                memset(nodej,'\0',size+1); 
                fread(nodej,sizeof(char),size,filei);
                //printf("\t%s\n",nodej);
                //create_tmp_community(community_tmp,"node2","node8");
                if ( create_tmp_community(community,nodei,nodej) == 0)            /*Create a tmp file for new community*/
			continue;
                float modularity1 = find_modularity(community,nodei);    /*Get modularity of nodei*/
                float modularity2 = find_modularity(community_tmp,nodei);    /*Get modularity of nodei*/
                printf("Modularity1 ori:-  %f\n",modularity1);
                printf("Modularity2 tmp:-  %f\n",modularity2);
		float modularity=modularity2-modularity1;
                printf("Modularity:-  %f\n",modularity);
		//rename(community_tmp,"pppp");
		if (modularity > max_modularity)
		{
			max_modularity=modularity;
			if (node_max != NULL ) 
			{
				printf("NODE %s\n",node_max);		
				free(node_max);
			}
                	node_max = malloc(sizeof(char) * size+1);                      /*Neighbour of nodei*/
	                memset(node_max,'\0',size+1);
        		strcpy(node_max,nodej);
		}	
                //read_community(community_tmp);
                //read_community("PHASE1_community_tmp_tmp");
                
        }
	//if (node_max !=NULL)
	if (max_modularity > 0.0f )
	{
		printf("NODE_MAX:  %s\n",node_max);
                create_tmp_community(community,nodei,node_max);            /*Create a tmp file for new community*/
		//rename(community,"aaa");
		rename(community_tmp,community);
		//system("./read PHASE1_community");
		//system("cp PHASE1_community dd");
		return 1;
	}
        fclose(filei); 
	return 0; 
}


int phase1(pool* pool1)
{
	if ( chdir("tmp") == 0 )
		printf("Directory changed successfully\n");
	else
		printf("Error in changing diretory\n");
        int i, j, size;
	char* community=(char*)malloc(sizeof("PASS")+sizeof(phase_no));
	sprintf(community,"PASS%d",phase_no);
        FILE *fp = fopen(community,"wb");
        //pool_ops.display_nodes(pool1);
        //struct community comm[pool1->ne_pool];  
        fwrite(&pool1->ne_pool, sizeof(int),1, fp);
        for(i=0; i<pool1->ne_pool; i++)
        {      
                int no_of_nodes = 1;
                fwrite(&no_of_nodes, sizeof(int),1, fp);
                size=strlen(pool1->node_obj[i].name);// * sizeof(char);
                fwrite(&size, sizeof(int),1, fp);
                fwrite(pool1->node_obj[i].name, sizeof(char),size, fp);
                //fprintf(fp, "%s\n",pool1->node_obj[i].name);

                FILE* fy = fopen(pool1->node_obj[i].name,"wb");			/* Writing to node files */
		//printf("file to write %s\n", pool1->node_obj[i].name);
                for(j=0; j<pool1->node_obj[i].ne_node; j++)
                {
                      	size=strlen(pool1->node_obj[i].element_obj[j].name)/sizeof(char);
                        fwrite(&size, sizeof(int),1, fy);
                        fwrite(pool1->node_obj[i].element_obj[j].name, sizeof(char),size, fy);
                        //fprintf(fy, "%s\n",pool1->node_obj[i].element_obj[j].name);
                }
                fclose(fy);    
        }      
        fclose(fp);

        char* node_name;
        int total=0;
	int flag=1;
        hashlist listvisited;
        hashlist_ops.hashlist_initialize(&listvisited);
	while(flag == 1)
	{
		flag=0;
        	FILE* file = fopen(community,"rb");
        	fread(&total,sizeof(int),1,file);
	        for( i=0; i<total; i++)
        	{
                	int comm_total;
	                fread(&comm_total,sizeof(int),1,file);
        	        //printf("Total Node community:- %d\n",comm_total);
                	for(j=0;j<comm_total;j++)
	                {
        	                fread(&size,sizeof(int),1,file);
                	        node_name = (char*)malloc(sizeof(char) * size+1);
                        	memset(node_name,'\0',size+1);  
	                        fread(node_name,sizeof(char),size,file);
        	                //printf("%s\n",node_name);
                                               
				hash* hashnode = hashlist_ops.hashlist_findhash(&listvisited,node_name);                                              
                                //if ( hashnode != NULL ) continue;
                                hashlist_ops.hashlist_add(&listvisited,node_name,1,1,0);       

                	        if ( migrate_node(community,node_name)==1)    //IF true
				{
					flag=1;
        				fclose(file);
					printf("BREAKING LOOP1\n");
	        			file=fopen(community,"rb");
			        	fread(&total,sizeof(int),1,file);
					break;
					//repeat again
				} 
        	       
	                }
				if(flag==1)
				{
					printf("BREAKING LOOP2\n");
				//	break;
				}
	        }
		//system("./read PHASE1_community");
        	fclose(file);
	}
	//system("./../read PHASE1_community");
	read_community(community);	
	phase2(pool1);
}

int phase2(pool* pool1)
{
	int local=0;	
        pool_ops.display_nodes(pool1);
        pool poolphase2;
        create_pool(&poolphase2);

	char* community=(char*)malloc(sizeof("PASS")+sizeof(phase_no));
	sprintf(community,"PASS%d",phase_no);

        int i,j,total,size,comm_total;
        FILE* file_comm=fopen(community,"rb");

        fread(&total,sizeof(int),1,file_comm);
        printf("Total Communities:- %d\n",total);
        int m;
        for(i=0; i<total; i++)                  //For each community
        {
                printf("\tCommunity:- %d\n",i);
                fread(&comm_total,sizeof(int),1,file_comm);
                printf("\t\tTotal N_C : %d\n",comm_total);

		char* name_node=(char*)malloc(sizeof("PASS")+sizeof(phase_no)+sizeof("_node")+sizeof(long));
		sprintf(name_node,"PASS%d_node%d",phase_no,local++);
	        pool_ops.create_node(&poolphase2,name_node);
		
                for(j=0;j<comm_total;j++)       //for each nodej in community
                {
                        char* node;
                        fread(&size,sizeof(int),1,file_comm);
                        printf("\t\tSIZE:- %d\t",size);
                        node=(char*)malloc(sizeof(char)*size+1);
                        memset(node,'\0',size+1);      
                        fread(node,sizeof(char),size,file_comm);
                        printf("Node: %s\n",node);
                }
		free(name_node);
        }      
        fclose(file_comm);      
	//read_community("PASS1");	
        pool_ops.display_nodes(&poolphase2);
        //node_ops.add_element(&pool1.node_obj[1],"node0");
}

int main()
{
        int i;
	phase_no=1;
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
        pool_ops.create_node(&pool1,"node9");
        //pool_ops.display_nodes(&pool1);
        node_ops.add_element(&pool1.node_obj[0],"node1");
        node_ops.add_element(&pool1.node_obj[0],"node2");
        //node_ops.add_element(&pool1.node_obj[1],"node0");
        node_ops.add_element(&pool1.node_obj[1],"node2");
        //node_ops.add_element(&pool1.node_obj[2],"node0");
        //node_ops.add_element(&pool1.node_obj[2],"node1");
        node_ops.add_element(&pool1.node_obj[2],"node3");
        //node_ops.add_element(&pool1.node_obj[3],"node2");
        node_ops.add_element(&pool1.node_obj[4],"node5");
        node_ops.add_element(&pool1.node_obj[4],"node6");
        //node_ops.add_element(&pool1.node_obj[5],"node4");
        //node_ops.add_element(&pool1.node_obj[5],"node6");
        //node_ops.add_element(&pool1.node_obj[5],"node7");
        //node_ops.add_element(&pool1.node_obj[6],"node4");
        node_ops.add_element(&pool1.node_obj[6],"node5");
        node_ops.add_element(&pool1.node_obj[7],"node5");
        node_ops.add_element(&pool1.node_obj[7],"node8");
        //node_ops.add_element(&pool1.node_obj[8],"node7");
        phase1(&pool1);
        //phase1();
	//fflush(stdio);
	//system("./read PHASE1_community");
}
