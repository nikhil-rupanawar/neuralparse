#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include"distribute.h"
#include"queue.h"
#include"hashlist.h"
#include"relpath.h"
void read_community1(char* community)
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
	    free(node);
        }
    }      
    fclose(file_comm);      
}

/* Function : edges_node
 * Description : return the no of edges in the given community file
 * Params:
 * 	1. node     :- node file whose edges need to be found  
 * Return Value: 
 * 	1: success
 */
int edges_node(char* node)
{
    int i,j,edges,size;
    edges=0;
    FILE* file=fopen(relpath(node),"rb");
    while(fread(&size,sizeof(int),1,file))
    {   
        char* node;
        node = malloc(sizeof(char) * size+1);
        memset(node,'\0',size+1);
        fread(node,sizeof(char),size,file);
        edges++;
	free(node);
    }      
    fclose(file);
    return edges;      	
}

int set_area(area* a1,int no,int x1,int x2, int y1, int y2)
{
    a1->no=no;
    a1->x1=x1;
    a1->x2=x2;
    a1->y1=y1;
    a1->y2=y2;
    return 1;
}

/* Function : calculate_area
 * Params:
 * 	1. a1     :- src area  
 * 	2. a2     :- dst area
 * 	3. weight :- The %age of area to be allocated to a2
 * 	4. alloted_weight :- The %age area which is already allocated to other Commmunity
 * Return Value: 
 * 	1: success
 */
int calculate_area(area* a1, area* a2,int weight,int alloted_weight)
{
    //printf("\ta1: %d %d %d %d\n",a1->x1,a1->x2,a1->y1,a1->y2);	
    //printf("\tWeight %d\tAlloted_weight %d\n",weight,alloted_weight);

    /* if (x2-x1) >= (y2-y1)  Means The x axis range is large
     * Thier for it is to be partitioned
     */
    if (a1->x2 - a1->x1 >= a1->y2 - a1->y1)
    {
	//printf("\tChanging x axis\n");
	a2->y1=a1->y1;
	a2->y2=a1->y2;
	a2->x1=a1->x1+((float)a1->x2/100)*alloted_weight;
	a2->x2=a2->x1+((float)a1->x2/100)*weight;
    }
    else
    {
	//printf("\tChanging y axis\n");
	a2->x1=a1->x1;
	a2->x2=a1->x2;
	a2->y1=a1->y1+((float)a1->y2/100)*alloted_weight;
	a2->y2=a2->y1+((float)a1->y2/100)*weight;
    }
    //printf("\ta2: %d %d %d %d\n",a2->x1,a2->x2,a2->y1,a2->y2);	
    return 1;
}

/*Function will return a number from range of (a1,a2)*/
int random_range(int a1, int a2)
{
    int num;
    float unit;
    //srand (clock());
    //srand (time(NULL));
    num=rand();
    unit=num/(float) RAND_MAX; 
    unit=a1 + (int)(unit * ((a2 - a1) + 1));
    //printf("a1:%d a2:%d num %d \n",a1,a2,(int)unit);  	
    return (int)unit;
}

/* Function will assign coordinates to nodes in PASS1 community
 * It will add coordinates to hashlist1
 */
int assign_coordinates(hashlist* hashlist1,queue* q1) 
{
    int i,j,total,size,comm_total;
    FILE* file_comm=fopen("PASS1","rb");
    fread(&total,sizeof(int),1,file_comm);
    printf("Total Communities:- %d\n",total);
    int m;
    srand (clock());
    for(i=0; i<total; i++)          //For each community
    {
        //printf("\tCommunity:- %d\n",i);
        fread(&comm_total,sizeof(int),1,file_comm);
        //printf("\t\tTotal N_C : %d\n",comm_total);
	queue_node* n1 = (queue_node*)queue_remove(q1);
        //printf("\t\tAREA:- x1:%d x2:%d y1:%d y2:%d\n",n1->x1,n1->x2,n1->y1,n1->y2);
        for(j=0;j<comm_total;j++)       //for each nodej in community
        {
            char* node;
            fread(&size,sizeof(int),1,file_comm);
            printf("\t\tSIZE:- %d\t",size);
            node=(char*)malloc(sizeof(char)*size+1);
            memset(node,'\0',size+1);      
            fread(node,sizeof(char),size,file_comm);
            printf("Node: %s\n",node);
	    printf("x1:%d x2:%d y1:%d y2:%d\n",n1->x1,n1->x2,n1->y1,n1->y2); 
    	    hashlist_ops.hashlist_add(hashlist1,node,random_range(n1->x1,n1->x2),random_range(n1->y1,n1->y2),rand()%100);    
	    free(node);
        }
    }      
    fclose(file_comm);      
    //queue_display(q1); 	
    //hashlist_ops.hashlist_display(hashlist1);	
}


/* Function : distribute
 * Description : Called from community.c , distibute the area with the community find in different passes recursively. 
 *		 The Areas is stored in queue 
 * Params:
 * 	1. pass_no     :-  last PASS_no  
 * Return Value: 
 * 	1: success
 */
int distribute(int pass_no, hashlist* hashlist1)
{
    //Assuming screen to be 600 * 600 pixels
    printf("Distributing\n");
    printf("%d\n",pass_no);
    int i, j,k, total,size;
    for(i=pass_no;i>=1;i--)
    {
    	char* community=(char*)malloc(sizeof("PASS")+sizeof(i));
   	sprintf(community,"PASS%d",i);	
	printf("%s\n",community);
	//read_community1(community);
    }

    queue q1;
    queue_initialize(&q1);
    int prev_comm=1;		/*No of communities in previos pass*/
    for(k=pass_no;k>=1;k--)	/*For each pass*/
    {

        char* community=(char*)malloc(sizeof("PASS")+sizeof(k));
        sprintf(community,"PASS%d",k);
	printf("%s\n",community)	;
        FILE* file_comm=fopen(community,"rb");
        fread(&total,sizeof(int),1,file_comm);
	area* a1 = malloc(sizeof(area)*prev_comm);		/* Area a1 hold the rectangle coordinates from the previos pass community
								 * Each community contains the area, Initially area[0] , area[1]and so on
							 	 * */
	int* total_edges = malloc(sizeof(int)*prev_comm);	/* total_edges[i] hold the total edges which fits in previous area a1[i]*/							
	for(i=0;i<prev_comm;i++)
	    total_edges[i]=0;
 	int save_prev;
	//save_prev=prev_comm;	//GARBAGE
        prev_comm=total;	//Setting prev_comm for next PASS
	int zone_cntr=0; 
	int new_flag=1; 
        for(i=0; i<total; i++)          /*For each community*/
        {
	    int comm_total;
            fread(&comm_total,sizeof(int),1,file_comm);
	    int edges_community=0; 
	    int no_nodes=0;
	    printf("SISIS %d %d\n",total,i);
    	    char* name_community=(char*)malloc(sizeof("Community_")+sizeof(i));
    	    sprintf(name_community,"Community_%d",i);
            /* For Community calculate the Total no of edges in the community*/	
            for(j=0;j<comm_total;j++)       //for each nodej in community
            {
                char* node;
                fread(&size,sizeof(int),1,file_comm);
                node=(char*)malloc(sizeof(char)*size+1);
                memset(node,'\0',size+1);      
                fread(node,sizeof(char),size,file_comm);
   	        edges_community += edges_node(node);	/* Adding the edge count to total edges in community */
	        no_nodes++;
	        free(node);
            }
            if (edges_community==0)		/*For links which are not stale*/
		edges_community=1;	
            if (k==pass_no)				/*Initially only 1 area is their*/
	    {
	    	total_edges[0] += edges_community;
        	set_area(a1,0,0,400,0,400);	
	        queue_add(&q1,name_community,edges_community,no_nodes,-1,-1,-1,-1);	//To queue we add Current Pass communities info
	    }
	    else
            {
	    	total_edges[zone_cntr] += edges_community;	/* Adding total edges of community to those community which will
								 * be in same area as calculted previously
								 */
		/* Here we have to add new community_nodes(current pass) to queue and remove the old community_nodes(previous pass)*/
	    	queue_node* qn = queue_get(&q1,1);		/* Getting the front element of queue*/
		//printf("qn->jey %s\n",qn->key);
		/* Set area[i] only if element is removed from queue or in entry*/
		if (new_flag==1)
		{
		    //printf("Set Area zone_cntr: %d\tno_nodes: %d x1:%d x2:%d y1:%d y2:%d\n",zone_cntr,qn->no,qn->x1,qn->x2,qn->y1,qn->y2);
		    set_area(&a1[zone_cntr],qn->no,qn->x1,qn->x2,qn->y1,qn->y2);
		    new_flag=0;
		}
		if(qn->no == 1)
		{
		    /* Removing community(previous_pass) from queue */
		    queue_node* n1 = (queue_node*)queue_remove(&q1);
		    new_flag=1;			//Means new element will be available at next node
		}
		else						
		{
		    /* Here only decreasing the no count when it reduces to 1 then we remove the element fron the queue
		     * Queue contains the number of community in the previous PASS and their rect coordinates.
		     * */
	    	    char* key = malloc(sizeof(strlen(qn->key)*sizeof(char)+1));
		    printf("KEy > %s Weight:%d no:%d\n",qn->key,qn->weight,qn->no);    
		    
		    strcpy(key,qn->key);		
	    	    printf("HERE\n");
		    qn->no--;  /* Decrease the no of nodes count*/					
 	    	    queue_update(&q1,1,key,qn->weight,qn->no,qn->x1,qn->x2,qn->y1,qn->y2);
		}
		//printf("adding to queue %s\tEdges%d No_nodes %d\n",name_community,edges_community,no_nodes);
		/* Add each new comminity(current_pass) to queue */
		
	//	printf("NAME_COMM %s\n",name_community);
	        queue_add(&q1,name_community,edges_community,no_nodes,-1,-1,-1,-1);
		if (new_flag)
		{
		    zone_cntr++;
		}
	    }
        }      
        fclose(file_comm);
        int alloted_weight=0;
	int area_cntr=0;			//Point to which area currently executing ;
	
	/*
        for(i=0;i<save_prev;i++)
	{
	    printf("AREA%d: %d\n",i,a1[i].no);
    	    printf("COORD: %d %d %d %d\n",a1[i].x1,a1[i].x2,a1[i].y1,a1[i].y2);	
		
	}*/
	
        for (i=1; i <= q1.ne; i++)		//For each element in Queue
        {
    	    area a2;
	    /* Read community from queue whose coords needs to be calculated */
	    queue_node* qn = queue_get(&q1,i);	/*Get the ith element */
	    char* key = malloc(sizeof(strlen(qn->key)*sizeof(char)+1));
	    strcpy(key,qn->key);
	    int weight;
	    if (k == pass_no)				//For the Last Pass
	    {
	    	weight = (100/(float)total_edges[0])*qn->weight;
	    	calculate_area(&a1[0],&a2,weight,alloted_weight);
	    }
	    else
	    {
		/* Approximation used to calculate community edge %age among all communities edges in a given area */
	    	weight = (100/(float)total_edges[area_cntr])*qn->weight;
		/* Calculate the coords of the community */
	    	calculate_area(&a1[area_cntr],&a2,weight,alloted_weight);
       	    }
	    alloted_weight += weight;

	    a1[area_cntr].no -= 1; 		
	    if (a1[area_cntr].no == 0)		/* Means no more community in that area */
	    {
		area_cntr++;
		/* As area_cntr updates , new area is used hence alloted_weight=0
		 * Above Scenario is not valid for last pass, as lastpass contains only one area i.e whole screen to divide
		 */
		if (k!=pass_no)
			alloted_weight=0;	
	    }
 	    queue_update(&q1,i,key,weight,qn->no,a2.x1,a2.x2,a2.y1,a2.y2);
        }
    }
    //queue_display(&q1);
    assign_coordinates(hashlist1,&q1);     
    return 1;
}
