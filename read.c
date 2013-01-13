#include<malloc.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[])
{
	
        int i,j,total,size,comm_total;
	printf("FILE : %s\n",argv[1]);
        FILE* file_comm=fopen(argv[1],"rb");

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
