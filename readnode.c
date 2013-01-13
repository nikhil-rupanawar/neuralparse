#include<malloc.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[])
{
	
        int i,j,total,size,comm_total;
	printf("FILE : %s\n",argv[1]);
        FILE* file=fopen(argv[1],"rb");
        while(fread(&size,sizeof(int),1,file))
	{    char* node;
              printf("\t\tSIZE:- %d\t",size);
              node = malloc(sizeof(char) * size+1);
              memset(node,'\0',size+1);
              fread(node,sizeof(char),size,file);
                        printf("Node: %s\n",node);
        }      
        fclose(file);      
}
