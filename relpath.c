#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <sys/stat.h>
#include"relpath.h"
char* relpath(char* name)
{
    struct stat sb;
    char* name_tmp=malloc(strlen(name)*sizeof(char)+1);
    strcpy(name_tmp,name);
    int len = strlen(name_tmp);
    char delims[] = "/";
    if (name_tmp[0]=='/')
        len--;
    char *result = NULL;
    char* prev=malloc(strlen(name)+sizeof(char)+1);
    result = strtok(name_tmp,delims);
    strcpy(prev,result);
    while( result != NULL )
    {
        if (!(stat(prev, &sb) == 0 && S_ISDIR(sb.st_mode)))
        {
            //printf("Len %d prev %s\n",len,prev);
            if ( len == strlen(prev))
            {
		return prev;
                //FILE* fp = fopen(prev,"w");
                //fclose(fp);
            }
            else
                mkdir(prev,0777);
        }
        //printf( "result is \"%s\" \n", result );
        result = strtok( NULL, delims );
        //printf( "Prev is \"%s\"\n", prev );
        if (result!=NULL)
        {
            strcat(prev,"/");
            strcat(prev,result);
        }
    }
    free(prev);
}
/*
int main()
{
    printf("%s\n",realpath("Intal/fdf"));
    printf("%s\n",realpath("/cratdit/fdf"));
    printf("%s\n",realpath("/Intxcd/FILE/s"));
    //realpath("/Intxcd/FILEs");
}*/
