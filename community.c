#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"pool.h"
#include"node.h"
#include"node2.h"
#include"hashlist.h"
<<<<<<< HEAD
#include"hashlist2.h"
#include"community.h"
#include"distribute.h"
#include"relpath.h"

int pass_no;
int community_previous=0;
struct Modularity
{
    int c_inner;            //Sum of link of weight inside Community
    int inci_c;             //Sum of link of weight incident to nodes in C
    int inci_i;             //Sum of link of weight incident to node i
    int i_inci_c;           //sum of link of weight from i to node in community
    int total;             //sum of link of weight of all nodes in the network
}modularity;

void read_community(char* community)
{
    //printf("%s\n",community);
    int i,j,total,size,comm_total;
    FILE* file_comm=fopen(community,"rb");

    fread(&total,sizeof(int),1,file_comm);
    printf("Total Communities:- %d\n",total);
    int m;
    for(i=0; i<total; i++)          //For each community
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
=======
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
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}

float find_modularity(char* community, char* nodei)
{
<<<<<<< HEAD
    printf("\tCommunity: %s\n",community);
    int i,j,total,size,comm_total;

    modularity.total=0;
    modularity.inci_i=0;
    modularity.inci_c=0;
    modularity.c_inner=0;
    modularity.i_inci_c=0;

    hashlist listnode;                //listnode contains all elemnents in community of nodei
    hashlist_ops.hashlist_initialize(&listnode);

    FILE* file_comm=fopen(community,"rb");
    fread(&total,sizeof(int),1,file_comm);

    /*Finding Elements in community of node i for that we have to traverse the community file, to get i and eventualy its community
     * Then we can add that members to listnode*/     
    for(i=0; i<total; i++)          //For each community
    {
        int break_flag=0;
        long position;
        fread(&comm_total,sizeof(int),1,file_comm);
        position=ftell(file_comm);
        for(j=0;j<comm_total;j++)       //for each nodej in community
        {
            char* node;
            fread(&size,sizeof(int),1,file_comm);
            node=(char*)malloc(sizeof(char)*size+1);
            memset(node,'\0',size+1);      
            fread(node,sizeof(char),size,file_comm);
            /*When nodei is found then iterate over its community to find community weight*/ 
            if (!strcmp(nodei,node))        //Checking if this node is nodei
            {
                int a;
                //long tmp_position;
                //tmp_position=ftell(file_comm);
                //printf("seek to position %ld\n",position);
                fseek(file_comm,position,SEEK_SET);  //Set File ptr to the position after no of elements in to nodei community
                for(a=0;a<comm_total;a++)       //for each nodej in community
                {
                    char* node;
                    fread(&size,sizeof(int),1,file_comm);
                    node=(char*)malloc(sizeof(char)*size+1);
                    memset(node,'\0',size+1);      
                    fread(node,sizeof(char),size,file_comm);
                    hashlist_ops.hashlist_add(&listnode,node,0,0,0);
                    free(node);
                }
                //fseek(file_comm,tmp_position,SEEK_SET);
                //Modification This fseek is not needed instead hust break These LOOPS because community node now finded
                break_flag=1;
                if (break_flag) break;
            }           
            if (break_flag)    break;
              }
        if (break_flag) break;
    }
    fclose(file_comm);
    //printf("Exited\n");
    /*REDEFINATION*/
    file_comm=fopen(community,"rb");
    fread(&total,sizeof(int),1,file_comm);
    //fseek(file_comm,0,SEEK_SET);
    for(i=0; i<total; i++)          //For each community
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
 //ADD Here 
            FILE* file_node;
            file_node=fopen(relpath(node),"rb");
            while(fread(&size,sizeof(int),1,file_node))
            {
                //printf("Size: %d\n",size);
                char* link;
                link=(char*)malloc(sizeof(char)*size+1);
                memset(link,'\0',size+1);      
                fread(link,sizeof(char),size,file_node);
                hash* hashsrc = hashlist_ops.hashlist_findhash(&listnode,node);
                hash* hashdst = hashlist_ops.hashlist_findhash(&listnode,link);

                if (!strcmp(nodei,node))           /*If node is nodei */
                {
                    if (hashdst != NULL)
                        modularity.i_inci_c++;
                }
            
                if (hashdst != NULL)
                {
                    if (hashsrc != NULL )        // If src and dst belong to nodei community 
                        modularity.c_inner++;
                    else                // if src dont belong to nodei community but destination belongs 
                        modularity.inci_c++;
                }    

                if (!strcmp(nodei,link)) modularity.inci_i++;      /*If destination is nodei increment inci_i */
                modularity.total++;                    //Increment the total link counter
                free(link);    
            }
            fclose(file_node);
            free(node);
        }
    }
//  printf("\tTotal weight     : %d\n",m);
//  printf("\tInci 2 nodei     : %d\n",inci_i);
//  printf("\tnodei 2 community: %d\n",i_inci_c);
//  printf("\tWeight community : %d\n",c_inner);
//  printf("\tInci 2 communitynodes : %d\n",inci_c);
    fclose(file_comm);     
    float tmp1,tmp2;
    //tmp1 = ((float)c_inner+i_inci_c+i_inci_c)/(m+m);
    tmp1 = ((float)modularity.c_inner+modularity.i_inci_c+modularity.i_inci_c)/(modularity.total+modularity.total);
    //tmp1 = tmp1 - ((1+(float)inci_i)/(m+m))*((1+(float)inci_i)/(m+m));
    tmp1 = tmp1 - ((modularity.inci_c+(float)modularity.inci_i)/(modularity.total+modularity.total))*((modularity.inci_c+(float)modularity.inci_i)/(modularity.total+modularity.total));
    tmp2 = ((float)modularity.c_inner)/(modularity.total+modularity.total);
    //tmp2 = tmp2 - (1/m+m)*(1/m+m);
    tmp2 = tmp2 - ((float)modularity.inci_c/(modularity.total+modularity.total))*((float)modularity.inci_c/(modularity.total+modularity.total));
    tmp2 = tmp2 - ((float)modularity.inci_i/(modularity.total+modularity.total))*((float)modularity.inci_i/(modularity.total+modularity.total));
    tmp1=tmp1-tmp2;
    return tmp1;
}

/*
 * Function is used to create a temprary community file by migrating nodei to nodej community
=======
        printf("\tCommunity: %s\n",community);
        //printf("Nodei: %s\t",nodei);
       	// printf("%s\n",community);
        int i,j,total,size,comm_total;

        int m=0;
        int inci_i=0;
	int inci_c=0;
        int c_inner=0;
	int i_inci_c=0;

        hashlist listnode;				//listnode contains all elemnents in community of nodei
        hashlist_ops.hashlist_initialize(&listnode);

        FILE* file_comm=fopen(community,"rb");
        fread(&total,sizeof(int),1,file_comm);

	/*Finding Elements in community of node i for that we have to traverse the community file, to get i and eventualy its community
 	* Then we can add that members to listnode*/ 	
        for(i=0; i<total; i++)                  //For each community
        {
		int break_flag=0;
                long position;
                fread(&comm_total,sizeof(int),1,file_comm);
                position=ftell(file_comm);
                for(j=0;j<comm_total;j++)       //for each nodej in community
                {
                        char* node;
                        fread(&size,sizeof(int),1,file_comm);
                        node=(char*)malloc(sizeof(char)*size+1);
                        memset(node,'\0',size+1);      
                        fread(node,sizeof(char),size,file_comm);
                        /*When nodei is found then iterate over its community to find community weight*/ 
                        if (!strcmp(nodei,node))                //Checking if this node is nodei
                        {
                                int a;
                                //long tmp_position;
                                //tmp_position=ftell(file_comm);
				printf("seek to position %ld\n",position);
                                fseek(file_comm,position,SEEK_SET);  //Set File ptr to the position after no of elements in to nodei community
                                for(a=0;a<comm_total;a++)       //for each nodej in community
                                {
                                        char* node;
                                        fread(&size,sizeof(int),1,file_comm);
                                        node=(char*)malloc(sizeof(char)*size+1);
                                        memset(node,'\0',size+1);      
                                        fread(node,sizeof(char),size,file_comm);
                                        hashlist_ops.hashlist_add(&listnode,node,0,0,0);
                                        free(node);
                                }
                                //fseek(file_comm,tmp_position,SEEK_SET);
				//Modification This fseek is not needed instead hust break These LOOPS because community node now finded
				break_flag=1;
				if (break_flag) break;
                        }               
			if (break_flag)	break;
      		}
		if (break_flag) break;
	}
	fclose(file_comm);
	printf("Exited\n");
	/*REDEFINATION*/
        file_comm=fopen(community,"rb");
        fread(&total,sizeof(int),1,file_comm);
        //fseek(file_comm,0,SEEK_SET);
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
 //ADD Here 
                        FILE* file_node;
                        file_node=fopen(node,"rb");
                        while(fread(&size,sizeof(int),1,file_node))
                        {
                                //printf("Size: %d\n",size);
                                char* link;
                                link=(char*)malloc(sizeof(char)*size+1);
                                memset(link,'\0',size+1);      
                                fread(link,sizeof(char),size,file_node);
                                hash* hashsrc = hashlist_ops.hashlist_findhash(&listnode,node);
                                hash* hashdst = hashlist_ops.hashlist_findhash(&listnode,link);

				if (!strcmp(nodei,node))                   /*If node is nodei */
				{
					if (hashdst != NULL)
						i_inci_c++;
				}
			
				if (hashdst != NULL)
				{
					if (hashsrc != NULL )		// If src and dst belong to nodei community 
						c_inner++;
					else				// if src dont belong to nodei community but destination belongs 
						inci_c++;
				}	

                                if (!strcmp(nodei,link)) inci_i++;      /*If destination is nodei increment inci_i */
                                m++;					//Increment the total link counter
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
        printf("Inci 2 communitynodes : %d\n",inci_c);
        fclose(file_comm);     
	float tmp1,tmp2;
	tmp1 = ((float)c_inner+i_inci_c+i_inci_c)/(m+m);
	//tmp1 = tmp1 - ((1+(float)inci_i)/(m+m))*((1+(float)inci_i)/(m+m));
	tmp1 = tmp1 - ((inci_c+(float)inci_i)/(m+m))*((inci_c+(float)inci_i)/(m+m));
	tmp2 = ((float)c_inner)/m+m;
	//tmp2 = tmp2 - (1/m+m)*(1/m+m);
	tmp2 = tmp2 - ((float)inci_c/m+m)*((float)inci_c/m+m);
	tmp2 = tmp2 - ((float)inci_i/m+m)*((float)inci_i/m+m);
	tmp1=tmp1-tmp2;
        return tmp1;
}

/*
 * Function is used to create a temprary community file by migrating nodei tovnodej community
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
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
<<<<<<< HEAD
    //printf("\tCommunity: %s\t",community);
    //printf("Nodei: %s\t",nodei);
    printf("\tChecking neighbour: %s\n",nodej);
    FILE* file_comm;                /* It will hold original commumnity file for reading */
    FILE* file_comm_tmp;                /* It will hold tmp community file for writing */
    char* node;
    int i,j,k,size,tmp;
    int total=0;
    file_comm=fopen(community,"rb");
    if (!file_comm)
    {
	printf("FILE to open %s\n",community);
	printf("aUnable to open File\n");
	return;
	exit(1);
    }
    char* community_tmp = (char*)malloc(sizeof(char)*(strlen(community)+strlen("_tmp")+1));
    strcpy(community_tmp,community);
    strcat(community_tmp,"_tmp");
    file_comm_tmp=fopen(community_tmp,"wb");
    if (!file_comm_tmp)
    {
	printf("FILE to open %s\n",community_tmp);
	printf("bUnable to open File\n");
	return;
	exit(1);
    }
    long position;                     //for holding read position
    long positionw;                 //for holding write position

    fread(&total,sizeof(int),1,file_comm);
    //printf("\tTotal Communities:- %d\n",total);
           
    position=ftell(file_comm_tmp);
    /* Writing Total no of communities. This can be changed later as community will shrink when a node is removed 
     * from its community and added to other(Exception if the community fromn which node is removed contains some
     * elements then total communities will not change */
    fwrite(&total,sizeof(int),1,file_comm_tmp);
    for(i=0; i<total; i++)                 //For each community
    {
        int comm_total;

        fread(&comm_total,sizeof(int),1,file_comm);            /* Get the total no of elements in the community */
	//printf("\tCommunity %d\n",i);
        //printf("\tNode in community:- %d\n",comm_total);
        int flag=0;
        node2 buffer;
        node_ops2.initialize2(&buffer);
        for(j=0; j<comm_total; j++)                       //for each nodej in community
        {
            fread(&size,sizeof(int),1,file_comm);
            node=(char*)malloc(sizeof(char)*size+1);
            memset(node,'\0',size+1);      
            fread(node,sizeof(char),size,file_comm);
            node_ops2.add_element2(&buffer,node,size);      

            // printf("\tProcessing %s\n",node);

            if(!strcmp(nodei,node))                    /* Nodei found */
            {
                flag=flag+1;
            }
            if(!strcmp(nodej,node))                    /* Nodej found */
            {
                flag=flag+2;
            }
        }
	//printf("\tFLAG= %d\n",flag);

        if(flag==1)                                //nodei found
        {
            comm_total--;
	    //printf("\tComm_total %d\n",comm_total);
            //printf("\tPosition_com %ld\n",position);
            if (comm_total == 0)
            {
                long position_tmp=ftell(file_comm_tmp);
                //fseek(file_comm_tmp,position,SEEK_SET);
                fseek(file_comm_tmp,0,SEEK_SET);
                //printf("**POSITION AFTER NODEI: %ld\n",ftell(file_comm_tmp));                    
                tmp=total-1;                    /*Since After migration no of communities will be less*/
		//printf("tmp %d\n",tmp);
                //printf("setting total %d\n",tmp);
                fwrite(&tmp,sizeof(int),1,file_comm_tmp);
                //position=ftell(file_comm_tmp);    doubt
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
        else if(flag==2)                        //nodej found
        {
            //printf("\tADDING TO DEST COMMUNITY\n")   ;
            comm_total++;
	    //printf("\tComm total %d\n",comm_total);
            fwrite(&comm_total,sizeof(int),1,file_comm_tmp);
            for(k=0; k < buffer.ne_node; k++)
            {
               // printf("\tElement %d\t%s\t%d\n",k,buffer.element_obj[k].name,buffer.element_obj[k].extra);    
                if(!strcmp(buffer.element_obj[k].name, nodei))  continue;
                fwrite(&buffer.element_obj[k].extra,sizeof(int),1,file_comm_tmp);
                fwrite(buffer.element_obj[k].name,sizeof(char),buffer.element_obj[k].extra,file_comm_tmp);
            }      
            size=strlen(nodei);
            fwrite(&size,sizeof(int),1,file_comm_tmp);
            fwrite(nodei,sizeof(char),size,file_comm_tmp);
        }
        else if(flag==3)                        //nodei in same community as nodej
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
    fclose(file_comm);
    fflush(file_comm_tmp);
   
    read_community(community_tmp);
    free(community_tmp);
    return 1;
=======
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
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}

/*
 *Function is used to migrate a node to a community where it gains maximum modularity including the existing one
 *
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei     : Node to migrate
 *
<<<<<<< HEAD
 * Return value :- 1 if node migrated  , 0 if not migrated
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
    FILE* filei = fopen(relpath(nodei),"rb");        /*Reading file of nodei for its neighbours*/
    float max_modularity=0.0f;
    char* node_max=NULL;
    while(fread(&size,sizeof(int),1,filei))
    {
        nodej = malloc(sizeof(char) * size+1);              /*Neighbour of nodei*/
        memset(nodej,'\0',size+1); 
        fread(nodej,sizeof(char),size,filei);
        //printf("\t%s\n",nodej);
        //create_tmp_community(community_tmp,"node2","node8");
        if ( create_tmp_community(community,nodei,nodej) == 0)        /*Create a tmp file for new community*/
            continue;
        float modularity1 = find_modularity(community,nodei);    /*Get modularity of nodei*/
        float modularity2 = find_modularity(community_tmp,nodei);    /*Get modularity of nodei*/
        //printf("\tModularity1 ori:-  %f\n",modularity1);
        //printf("\tModularity2 tmp:-  %f\n",modularity2);
        float modularity=modularity2-modularity1;
        //printf("\tModularity:-  %f\n\n",modularity);
        if (modularity > max_modularity)
        {
            max_modularity=modularity;
            if (node_max != NULL ) 
            {
                //printf("NODE %s\n",node_max);        
                free(node_max);
            }
            node_max = malloc(sizeof(char) * size+1);              /*Neighbour of nodei*/
            memset(node_max,'\0',size+1);
            strcpy(node_max,nodej);
        }    
        //read_community(community_tmp);
        //read_community("PHASE1_community_tmp_tmp");
    }
    //if (node_max !=NULL)
    if (max_modularity > 0.0f )
    {
        printf("\tNODE_MAX:  %s\n",node_max);
        create_tmp_community(community,nodei,node_max);        /*Create a tmp file for new community*/
        //rename(community,"aaa");
        rename(community_tmp,community);
        //system("./read PHASE1_community");
        //system("cp PHASE1_community dd");
        return 1;
    }
    fclose(filei); 
    return 0; 
=======
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
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}


int phase1(pool* pool1)
{
<<<<<<< HEAD
    if ( chdir("tmp") == 0 )
        printf("Directory changed successfully\n");
    else
        printf("Error in changing diretory\n");
    int i, j, size;
    char* community=(char*)malloc(sizeof("PASS")+sizeof(pass_no));
    sprintf(community,"PASS%d",pass_no);
    FILE *fp = fopen(community,"wb");
    printf("Name: %s\n",community);
    //pool_ops.display_nodes(pool1);
    //struct community comm[pool1->ne_pool];  
    fwrite(&pool1->ne_pool, sizeof(int),1, fp);
        
    if ((community_previous == pool1->ne_pool && pass_no != 2)  || pass_no == 4)
    {	
	printf("No more reduction in community now possible\n");
	printf("Level of communty found %d\n",pass_no-1);
	//distribute(pass_no-1);
	return;
    }
    community_previous=pool1->ne_pool;

    for(i=0; i<pool1->ne_pool; i++)
    {     
	//Writing to new community file 
        int no_of_nodes = 1;
        fwrite(&no_of_nodes, sizeof(int),1, fp);
        size=strlen(pool1->node_obj[i].name);// * sizeof(char);
        fwrite(&size, sizeof(int),1, fp);
        fwrite(pool1->node_obj[i].name, sizeof(char),size, fp);
        //fprintf(fp, "%s\n",pool1->node_obj[i].name);
        printf("Writing File  %s\n",pool1->node_obj[i].name);

	if (pass_no == 1)		/*Node files are created only for first pass as for rest file will be created in phase2*/
	{
	    //printf("write: %s\n",pool1->node_obj[i].name);	
            FILE* fy = fopen(relpath(pool1->node_obj[i].name),"wb");            /* Writing to node files */
            for(j=0; j<pool1->node_obj[i].ne_node; j++)
            {
		printf("name:- %s\n",relpath(pool1->node_obj[i].element_obj[j].name));
                size=strlen(relpath(pool1->node_obj[i].element_obj[j].name))*sizeof(char);
                //size=strlen(pool1->node_obj[i].element_obj[j].name)*sizeof(char);
                fwrite(&size, sizeof(int),1, fy);
                fwrite(relpath(pool1->node_obj[i].element_obj[j].name), sizeof(char),size, fy);
                //fwrite(pool1->node_obj[i].element_obj[j].name, sizeof(char),size, fy);
            }
            fclose(fy);  
	}  
    }      
    //printf("Debugging\n");
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
                    //printf("BREAKING LOOP1\n");
                    file=fopen(community,"rb");		//Looks Redundant as at break the file is going to be closed
                    fread(&total,sizeof(int),1,file);
                    break;
                    //repeat again
                } 
            }
            if(flag==1)
            {
                //printf("BREAKING LOOP2\n");
                break;
            }
        }
        //system("./read PHASE1_community");
        fclose(file);
    }
    //system("./../read PHASE1_community");
    //read_community(community);
    //pool_ops.display_nodes(pool1);
    phase2(pool1);
=======
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
	//read_community(community);	
	//phase2(pool1);
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}

int phase2(pool* pool1)
{
<<<<<<< HEAD
    int local=0;    
    pool_ops.display_nodes(pool1);
    pool poolphase2;
    create_pool(&poolphase2);

    char* community=(char*)malloc(sizeof("PASS")+sizeof(pass_no));
    sprintf(community,"PASS%d",pass_no);

    int i,j,total,size,comm_total;
    FILE* file_comm=fopen(community,"rb");
    fread(&total,sizeof(int),1,file_comm);
    printf("Total Communities:- %d\n",total);
    int m;
    hashlist2 list_node2community;
    hashlist_ops2.hashlist_initialize2(&list_node2community);
    for(i=0; i<total; i++)          //For each community
    {
        printf("\tCommunity:- %d\n",i);
        fread(&comm_total,sizeof(int),1,file_comm);
        printf("\t\tTotal N_C : %d\n",comm_total);

        char* name_node=(char*)malloc(sizeof("PASS")+sizeof(pass_no)+sizeof("_node")+sizeof(long));
        sprintf(name_node,"PASS%d_node%d",pass_no,local++);
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
    	    hashlist_ops2.hashlist_add2(&list_node2community,relpath(node),relpath(name_node),0,0,0);
	    free(node);
        }
        free(name_node);
    }      
    fclose(file_comm);      
    printf("Displaying node 2 Community\n");
    hashlist_ops2.hashlist_display2(&list_node2community);
    if (list_node2community.alloted == 0) return;
    for(i=0; i < list_node2community.size; i++)
    {
        if(list_node2community.Hash[i].valid == 1)
        {
		FILE* file_nodephase1=fopen(relpath(list_node2community.Hash[i].key_name),"r");
		FILE* file_nodephase2=fopen(relpath(list_node2community.Hash[i].extra),"ab");
		char* node;
		printf("\tRead File %s\n",relpath(list_node2community.Hash[i].key_name));
		printf("\tWrite Fil %s\n",relpath(list_node2community.Hash[i].extra));
        	while(fread(&size,sizeof(int),1,file_nodephase1))
	        {
                    node = malloc(sizeof(char) * size+1);
                    memset(node,'\0',size+1);
                    fread(node,sizeof(char),size,file_nodephase1);
		    printf("\t\tNode2find %s\n",node);

		    hash2* h1 = hashlist_ops2.hashlist_findhash2(&list_node2community,node);
		    if (h1!=NULL)
		    {
			printf("\t\tWriting  %s\n",h1->extra);
        		size=strlen(h1->extra);// * sizeof(char);
        		fwrite(&size, sizeof(int),1, file_nodephase2);
        		fwrite(h1->extra, sizeof(char),size, file_nodephase2);
	 	    }	
		    free(node);
		}
		fclose(file_nodephase1);
		fclose(file_nodephase2);
                //printf("\tName   :- %s\t\tExtra :- %s\n ",list_node2community.Hash[i].key_name, list_node2community.Hash[i].extra);
        }
    }
    //read_community("PASS1");    
    //pool_ops.display_nodes(&poolphase2);
    pass_no++; 
    phase1(&poolphase2);
    //node_ops.add_element(&pool1.node_obj[1],"node0");
}

int find_community(pool* pool1,hashlist* hashlist1)
{
    system("rm tmp/* -rf");
    pass_no=1;
    phase1(pool1);
    //hashlist_ops.hashlist_initialize(hashlist1);
//    exit(0);
    distribute(pass_no-1,hashlist1);
=======
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
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}
/*
int main()
{
<<<<<<< HEAD
    int i;
    pool pool1;
    create_pool(&pool1);
    int total,node,link;
    char are[8];
    FILE *fp; fp=fopen("graph","r");
    if (fp == NULL) {
          printf("Can't open output file\n");
          exit(1);
    }
    printf("Buggy\n"); 
            
    fscanf(fp,"%d\n",&total);
    printf("%d",total) ;
    for (i=0;i<total;i++)
    {
        char* tmp=(char*)malloc(sizeof(char)*20);
         sprintf(tmp, "node%d", i);
        pool_ops.create_node(&pool1,tmp);
    }
    while (fscanf(fp,"%d %d",&node,&link) != EOF)
    {
        char* tmp=(char*)malloc(sizeof(char)*20);
         sprintf(tmp, "node%d",link);
        node_ops.add_element(&pool1.node_obj[node],tmp);
    }
    fclose(fp);

    printf("-----------------displaying pool nodes---------------\n");
    for(i=0;i< pool1.ne_pool;i++)
    {
    //    printf("%s\n",pool1.node_obj[i].name);    
    //    node_ops.display_element(&pool1.node_obj[i]);
    }
    find_community(&pool1);
=======
	int i;
	phase_no=1;
        pool pool1;
        create_pool(&pool1);
	int total,node,link;
	
	char are[8];
	FILE *fp; fp=fopen("graph","r");
	if (fp == NULL) {
  		printf("Can't open output file\n");
  		exit(1);
	}
			
	fscanf(fp,"%d",&total);
	for (i=0;i<total;i++)
	{
		char* tmp=(char*)malloc(sizeof(char)*20);
	 	sprintf(tmp, "node%d", i);
        	pool_ops.create_node(&pool1,tmp);
	}
	while (fscanf(fp,"%d %d",&node,&link) != EOF)
	{
		char* tmp=(char*)malloc(sizeof(char)*20);
	 	sprintf(tmp, "node%d",link);
        	node_ops.add_element(&pool1.node_obj[node],tmp);
	}
	fclose(fp);

	printf("-----------------displaying pool nodes---------------\n");
	for(i=0;i< pool1.ne_pool;i++)
	{
	//	printf("%s\n",pool1.node_obj[i].name);	
	//	node_ops.display_element(&pool1.node_obj[i]);
	}
        phase1(&pool1);
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}
*/
/*
int main()
{
<<<<<<< HEAD
    int i;
    pass_no=1;
    pool pool1;
    create_pool(&pool1);
    pool_ops.create_node(&pool1,"last/node0");
    pool_ops.create_node(&pool1,"/norway/node1");
    pool_ops.create_node(&pool1,"node2");
    pool_ops.create_node(&pool1,"node3");
    pool_ops.create_node(&pool1,"node4");
    pool_ops.create_node(&pool1,"node5");
    pool_ops.create_node(&pool1,"node6");
    pool_ops.create_node(&pool1,"node7");
    pool_ops.create_node(&pool1,"node8");
    pool_ops.create_node(&pool1,"node9");
    //pool_ops.display_nodes(&pool1);
    node_ops.add_element(&pool1.node_obj[0],"/norway/node1");
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
    find_community(&pool1);
    //phase1();
    //fflush(stdio);
    //system("./read PHASE1_community");
=======
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
>>>>>>> 2ef2b550d72d95a2d4a5cabdd99cadf6486ef13b
}*/
