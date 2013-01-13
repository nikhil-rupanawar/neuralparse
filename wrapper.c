#include<malloc.h>
#include<string.h>
#include"wrapper.h"

void wrapper_addfile(Wrapper* wrapper1,char* file_path)
{
	printf("ADDING WRAPPER\n");
	Filelist* list_tmp=(Filelist*)malloc(sizeof(Filelist));
	list_tmp->path=(char*)malloc(sizeof(char)*strlen(file_path)+1);
	strcpy(list_tmp->path,file_path);
	list_tmp->next=NULL;
	if (wrapper1->initialized != 300 || wrapper1->filelist1==NULL)
	{
		wrapper1->initialized = 300;
		printf("EMPTY WRAPPER\n");
		//printf("NULLLLLL\n");
		list_tmp->next=NULL;
		wrapper1->filelist1=list_tmp;
	}
	else
	{
		//printf("Entering %s\n",list_tmp->path);
		list_tmp->next=wrapper1->filelist1;
		wrapper1->filelist1=list_tmp;			
	}
	//list_tmp->next=list1;
	//list1=list_tmp;	
}

void wrapper_reverse(Wrapper* wrapper1)
{
	if (wrapper1->filelist1==NULL)	return;
	Filelist* list_tmp1;
	Filelist* list1=wrapper1->filelist1;
	while(list1!=NULL)
	{
		Filelist* list_tmp2=(Filelist*)malloc(sizeof(Filelist));
		int len = strlen(list1->path);
		list_tmp2->path=(char*)malloc(sizeof(char)*len+1);
		strcpy(list_tmp2->path,list1->path);
	
		if (list_tmp1==NULL)	
		{
			list_tmp1=list_tmp2;
			list_tmp1->next=NULL;
		}
		else 
		{
			list_tmp2->next=list_tmp1;
			list_tmp1=list_tmp2;
		}	
		list1=list1->next;		
	}
	free(wrapper1->filelist1);
	wrapper1->filelist1=list_tmp1;
	
}

void wrapper_display(Wrapper* wrapper1)
{
	printf("Displaying\n");
	Filelist* list1=wrapper1->filelist1;
	//struct stat *buf=(struct stat*)malloc(sizeof(struct stat));	//stat structure object to hold file attributes
	while(list1 != NULL)
	{
			/*
			if (!stat(list1->path,buf))		//Stat fn Return all attributes of file in struct stat (buf) object
			{
				//When stat successful
				mode_t mode = buf->st_mode;
				if ((mode & S_IFMT) == S_IFDIR)	//If current file is Directory
				{
					printf("Directory\n");
				}
				else if ((mode & S_IFMT) == S_IFREG) //Regular file	
				{
					printf("File\n");
				}
			}
			else
			{
				printf("Stat Func is not able to return file attributes\n");
			}*/
		printf("%s\n",list1->path);
		list1=list1->next;
	}	
}
/*
int main()
{
	//struct Filelist* list1;
	Wrapper* wrapper1=(Wrapper*)malloc(sizeof(Wrapper));
	//list1.next=NULL;
	wrapper_addfile(wrapper1,"/home/user/Documents/tree/regex.c");
	wrapper_addfile(wrapper1,"/home/user/Documents/tree/cylin.py~");
	wrapper_addfile(wrapper1,"/home/user/Documents/tree/wrapper.h");
	wrapper_addfile(wrapper1,"/home/user/Documents/tree/a.c");
	wrapper_display(wrapper1);
//	wrapper_reverse(wrapper1);
	wrapper_display(wrapper1);
	
}*/
