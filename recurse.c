/*
 *Devaloped By
 *Pankaj Rawat
 *pankajr141@gmail.com
 */

#include <stddef.h>
#include <stdio.h> // For operators >>, <<, and getline.
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include "wrapper.h"
#include "recurse.h" 
char* gnu_getcwd ()
{
  int size = 100;
  char *buffer = (char*)malloc(sizeof(char)*size);

  while (1)
    {
      char *value = getcwd (buffer, size);
      if (value != 0)
        return buffer;
      size *= 2;
      free (buffer);
      buffer = malloc(sizeof(char)*size);
      //buffer = (char *) xmalloc (size);
    }
}

int listfiles(Wrapper* wrapper1, char* path_dir)
{
	//if (!chdir(path_dir))
	//	printf("CHanged DIRECTORY SUCCESSFULLY\n");
	printf("CD %s\n",path_dir);
  	DIR *dp;
 	struct dirent *ep;
  	dp = opendir (path_dir);
	if (dp != NULL)
	{
		while (ep = readdir (dp))
        	{	//puts (ep->d_name);
			if (!strcmp(ep->d_name,".") || !strcmp(ep->d_name,".."))
			{	//printf("skip\n");
				continue;
			}
			//printf("%d\n",ep->d_fileno);
			struct stat *buf=(struct stat*)malloc(sizeof(struct stat));	//stat structure object to hold file attributes
			if (buf ==NULL)
			{
				printf("Not able to allocate space to buffer\n");
			//	exit(1);
			}

			char *tmp_path;
			//tmp_path=malloc(sizeof(char)*strlen(path_dir));
			tmp_path=malloc(sizeof(char)*(strlen(path_dir)+strlen(ep->d_name)+strlen("/")+1));	//Since ep->dname and / are also added later
			if (tmp_path ==NULL)
			{
				printf("Not able to allocate space to buffer\n");
			//	exit(1);
			}
			strcpy(tmp_path,path_dir);
			strcat(tmp_path,ep->d_name);
			printf("FILE :- %s\n",tmp_path);

			//Check for Hidden files, Skip if exist
			char ch=ep->d_name[0];
			if( ch == '.' )
			{
				printf("Skipping %s\n",ep->d_name);
				free(tmp_path);
				free(buf);
				continue;
			}
			if (!stat(tmp_path,buf))		//Stat fn Return all attributes of file in struct stat (buf) object
			{
				//When stat successful
				mode_t mode = buf->st_mode;
				if ((mode & S_IFMT) == S_IFDIR)	//If current file is Directory
				{
					strcat(tmp_path,"/");
					//wrapper_addfile(wrapper1,tmp_path);
					listfiles(wrapper1, tmp_path);	
				}
				else if ((mode & S_IFMT) == S_IFREG) //Regular file	
				{
					wrapper_addfile(wrapper1,tmp_path);
				}
			}
			else{
				printf("Stat Func is not able to return file attributes\n");
			}
			free(tmp_path);
			free(buf);
		}
     		(void) closedir (dp);
   	}
 	 else
   		 puts ("Couldn't open the directory.");
  return 0;
}

