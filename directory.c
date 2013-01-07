#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
int listfiles(char*);
int listdeps(path)
{
}

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

int listfiles(char* path_dir)
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
			struct stat* buf;
			buf=(struct stat*)malloc(sizeof(struct stat));	//stat structure object to hold file attributes
			//printf("%d\n",ep->d_fileno);
			if (buf ==NULL)
			{
				printf("Not able to allocate space to buffer\n");
			//	exit(1);
			}
			char *tmp_path;
			tmp_path=malloc(sizeof(char)*(strlen(path_dir)+strlen(ep->d_name)+2));	//Since ep->dname and / are also added later
			if (tmp_path==NULL)
			{
				printf("Not able to allocate space to buffer\n");
			//	exit(1);
				
			}
			strcpy(tmp_path,path_dir);
			strcat(tmp_path,ep->d_name);
			printf("FILE :- %s\n",tmp_path);
			if (!stat(tmp_path,buf))		//Stat fn Return all attributes of file in struct stat (buf) object
			{
				//When stat successful
				mode_t mode = buf->st_mode;
				printf("Address %d\n",buf->st_mode);
				if ((mode & S_IFMT) == S_IFDIR)	//If current file is Directory
				{
					strcat(tmp_path,"/");
					listfiles(tmp_path);	
				}
				else if ((mode & S_IFMT) == S_IFREG) //Regular file	
				{}
				else
				{
					printf("Dont know\n");
				}
				printf("%s\n",tmp_path);
			}
			else{
				printf("Stat Func is not able to return file attributes\n");
			}
			printf("Debugg\n");
			printf("Tmp_path %s\n",tmp_path);
			printf("Tmp_path %u\n",tmp_path);
			free(tmp_path);
			printf("Debugg\n");
			free(buf);
			printf("Debugg\n");
		}
     		(void) closedir (dp);
   	}
 	 else
   		 puts ("Couldn't open the directory.");
  return 0;
}
int main()
{		
	char* cwd=gnu_getcwd();
	strcat(cwd,"/");
	//listfiles("./");	
	listfiles(cwd);	
}



