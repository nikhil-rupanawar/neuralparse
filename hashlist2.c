#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"hashlist2.h"
#include"hashalgo.h"
void hashlist_reallot2(hashlist2* list1)
{
        int i;
        float alloted_percent =  ((float)list1->alloted/list1->size)*100 ;
        printf("Realloting Hashlist with allocation %f  New Size %d\n",alloted_percent,list1->size*2);
        hashlist2 list2;

        list2.Hash=(hash2*)malloc(sizeof(hash2)*list1->size*2);
        list2.size=list1->size*2;
        for( i=0; i < list2.size-1; i++)
                list2.Hash[i].valid=0;
        list2.alloted=0;
       
        for(i=0; i < list1->size; i++)
        {
                if(list1->Hash[i].valid == 1)
                {
                        //printf("\tName   :- %s\n",list1->Hash[i].key_name);
                        //printf("\tCoords :- %d %d %d\n",list1->Hash[i].x,list1->Hash[i].y,list1->Hash[i].z);
                        hashlist_ops2.hashlist_add2(&list2,list1->Hash[i].key_name,list1->Hash[i].extra,list1->Hash[i].x,list1->Hash[i].y,list1->Hash[i].z);
                }                      
        }

        hash2* hash_tmp = list1->Hash;
        list1->Hash=list2.Hash;
        list1->size=list2.size;
        list1->alloted=list2.alloted;
        free(hash_tmp);
}

int hashlist_add_implemented2(hashlist2* list1,char* key_name,char* extra,int x,int y,int z)
{
        int hash_value;
        int i;
        if ( list1->Hash == NULL )
        {
                 list1->Hash = (hash2*)malloc(sizeof(hash2) * list1->size );
                 for( i=0; i<list1->size-1; i++)
                        list1->Hash[i].valid=0;
        }

        /* Reallot Hashlist if it iis 80% full */
        float alloted_percent =  ((float)list1->alloted/list1->size)*100 ;
        //printf("Adding hash :- %s\t Hash:- %d \tAlloted %f\%\n",key_name,hashalgo(key_name,list1->size),alloted_percent);            
        if ( alloted_percent >= 80 )
                hashlist_reallot2(list1);

        hash_value = hashalgo(key_name,list1->size);
        //printf("Hash Value  :- %d\n",hash_value);

        /*Closed Hashing, In collision look for the next available space to fit the key*/

        while (list1->Hash[hash_value].valid == 1)
        {
                /*Check if same key exist. If yes return*/
                if (!strcmp(list1->Hash[hash_value].key_name,key_name)) 
			return;
                if ( hash_value == list1->size-1 )
                        hash_value=-1;
                hash_value++;
        //      printf("Hash %d  Valid %d\n",hash_value,list1->Hash[hash_value].valid);
        }

        list1->Hash[hash_value].key_name = (char*)malloc(sizeof(char)*strlen(key_name)+1);
        list1->Hash[hash_value].extra = (char*)malloc(sizeof(char)*strlen(extra)+1);
        strcpy(list1->Hash[hash_value].key_name,key_name);      
        strcpy(list1->Hash[hash_value].extra,extra);      
        list1->Hash[hash_value].x = x;
        list1->Hash[hash_value].y = y;
        list1->Hash[hash_value].z = z;
        list1->Hash[hash_value].valid = 1;
        list1->alloted++;
       
}

void hashlist_display_implemented2(hashlist2* list1)
{
        int i;
        printf("Displaying Hash list\n");
        if (list1->alloted == 0) return;
        for(i=0; i < list1->size; i++)
        {
                if(list1->Hash[i].valid == 1)
                {
                        printf("\tName   :- %s\t\tExtra	:- %s\n ",list1->Hash[i].key_name, list1->Hash[i].extra);
                        printf("\tCoords :- %d %d %d\n",list1->Hash[i].x,list1->Hash[i].y,list1->Hash[i].z);
                }                      
        }
}

void hashlist_initialize_implemented2(hashlist2* list1)
{
        //printf("Initializing\n");
        list1->size=10;
        list1->alloted=0;
        list1->Hash=NULL;
}

hash2* hashlist_findhash_implemented2(hashlist2* list1, char* key_name)
{
        int i;
        if (list1->alloted == 0) return NULL;
        for(i=0; i < list1->size; i++)
        {
                if(list1->Hash[i].valid == 1 && !strcmp(list1->Hash[i].key_name,key_name))
                        return &list1->Hash[i];
        }
        return NULL;
}

void hashlist_destroy_implemented2(hashlist2* list1)
{
        int i;
        if (list1->alloted == 0) return;
        for(i=0; i < list1->size; i++)
        {
                if(list1->Hash[i].valid == 1)
			free(list1->Hash[i].key_name);
        }
	free(list1->Hash);	
}
