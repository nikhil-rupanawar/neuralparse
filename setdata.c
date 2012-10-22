#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "wrapper.h"
#include "regexfile.h"
#include "pool.h"
#include "node.h"
#include "hashlist.h"
#include "recurse.h"

void setdata(pool* pool1,hashlist* hashlist1)
{	
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
	
	/*TMP CODE*/

	
	//Filelist* list2=wrapper1->filelist1;	
	//hashlist hashlist1;
	
	hashlist_ops.hashlist_initialize(hashlist1);
	for(i=0; i < pool1->ne_pool; i++)
	{
		hashlist_ops.hashlist_add(hashlist1,pool1->node_obj[i].name,rand()%10,rand()%10,rand()%10);
		for(j=0; j < pool1->node_obj[i].ne_node; j++)
			hashlist_ops.hashlist_add(hashlist1,pool1->node_obj[i].element_obj[j].name,rand()%10,rand()%10,rand()%10);
			
		//printf("%s\n",pool1->node_obj[i].name);	
	}
	hashlist_ops.hashlist_display(hashlist1);	
	
	//for(i=0;i<node_obj->ne_node;i++)
		//printf("\tElement %d\t%s\n",i,node_obj->element_obj[i].name);	

}
