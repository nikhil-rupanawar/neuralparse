#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include "wrapper.h"
#include "regexfile.h"
#include "pool.h"
#include "node.h"
#include "hashlist.h"
#include "recurse.h"
#include "coords.h"
#include "community.h"
void setdata(pool* pool1,hashlist* hashlist1,line* line_obj)
{	
    	system("rm tmp/* -rf");
	int i,j;			
	char* cwd=gnu_getcwd();
	strcat(cwd,"/");

	Wrapper* wrapper1=(Wrapper*)malloc(sizeof(Wrapper));
	/*
	 List all files recursively, Add them to the wrapper object
	*/
	printf("ADDING FILES to WRAPPER\n");
	listfiles(wrapper1,cwd);
	printf("FILES ADDED TO WRAPPER\n");	
	
	/*Creating pool object to hold the Files and their links */
	//pool pool1;
	create_pool(pool1);
	
	/*Traversing the wrapper object
 	While traversing copy the contents of wrapper object as pool nodes
 	Then pass node to regexfile to extract The needed dependency as elements of node*/
	Filelist* list1=wrapper1->filelist1;	
	node* node1;
	printf("$$$$$$$$$ Traversing Wrapper object starts\n\n");
	while(list1 != NULL)
	{
		//printf("%s",list1);
		if (!strlen(list1->path)) continue;
		printf("------------%s-----------\n",list1->path);
		pool_ops.create_node(pool1,list1->path);
	
		node1=pool_ops.get_node(pool1,list1->path);	
		if (node1!=NULL) 
			regexfile(node1,list1->path);	
		list1=list1->next;
	}	
	printf("$$$$$$$$$ Traversing Wrapper object Ends\n\n");

	pool_ops.display_nodes(pool1);
	for(i=0; i< pool1->ne_pool; i++)
	{
		printf("NODE NO:- %d\n",i);
		node_ops.display_element(&pool1->node_obj[i]);
	}

	hashlist_ops.hashlist_initialize(hashlist1);
	find_community(pool1,hashlist1);
	/*		
	for(i=0; i < pool1->ne_pool; i++)
	{
		hashlist_ops.hashlist_add(hashlist1,pool1->node_obj[i].name,rand()%20,rand()%20,rand()%20);
		for(j=0; j < pool1->node_obj[i].ne_node; j++)
			hashlist_ops.hashlist_add(hashlist1,pool1->node_obj[i].element_obj[j].name,rand()%20,rand()%20,rand()%20);
			
		//printf("%s\n",pool1->node_obj[i].name);	
	}
	*/
	//exit(0);	
	hashlist_ops.hashlist_display(hashlist1);	
	//for(i=0;i<node_obj->ne_node;i++)
		//printf("\tElement %d\t%s\n",i,node_obj->element_obj[i].name);	
	hash* hash_get1;
	hash* hash_get2;

	create_line(line_obj);
	
	for(i=0; i < pool1->ne_pool; i++)
	{
		printf("NODE NAME :- %s\n",pool1->node_obj[i].name);
		hash_get1=hashlist_ops.hashlist_findhash(hashlist1,pool1->node_obj[i].name);	
		if (hash_get1 == NULL)
		{
			printf("Hash1 not added properly\n");
			exit(1);
		}	
		for(j=0; j < pool1->node_obj[i].ne_node; j++)
		{
			printf("Name to find %s\n",pool1->node_obj[i].element_obj[j].name);	
			hash_get2=hashlist_ops.hashlist_findhash(hashlist1,pool1->node_obj[i].element_obj[j].name);	
			if (hash_get2 == NULL)
			{
				printf("Hash2 not added properly\n");
				//exit(1);
				continue;
			}	
	      		printf("Not NULL\n");
		        printf("\tName   :- %s\n",hash_get1->key_name);
		   	printf("\tCoords :- %d %d %d\n",hash_get1->x,hash_get1->y,hash_get1->z);	
		        printf("\tName   :- %s\n",hash_get2->key_name);
		   	printf("\tCoords :- %d %d %d\n",hash_get2->x,hash_get2->y,hash_get2->z);	
			printf("\tElement Name :- %s\n",pool1->node_obj[i].element_obj[j].name);
			line_ops.line_add(line_obj,hash_get1->x,hash_get1->y,hash_get1->z,hash_get2->x,hash_get2->y,hash_get2->z);
		}
	}
	line_ops.line_display(line_obj);
//	exit(0);
}
