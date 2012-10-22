#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
struct hash_t
{
	/*File Name . x,y,z coordinates*/
	char* key_name;		
	int x;			
	int y;
	int z;
	int valid;
};
typedef struct hash_t hash;

struct hashlist_t
{
	int size;
	int alloted;
	hash* Hash;
};
typedef struct hashlist_t hashlist;

struct hashlist_ops_n
{
	void (*hashlist_initialize)(hashlist* list1);
	int (*hashlist_add)(hashlist* list1, char* key_name,int x, int y, int z);
	void (*hashlist_display)(hashlist* list1);
};

int hashfunc(char* str,int M)
{
	int i,j,k,length;
	long mult,sum=0;
	length=strlen(str)/4;
	for(i=0;i<strlen(str);i++)
	{
			
		sum+=str[i]^(23+i%4);		
	}	
	sum=53*sum^3+3*sum^2-5*sum+8;
	if ( sum <0 )
	  sum = -sum;	
	
	//printf("%d\n",sum);
	return sum % M;	
}

void hashlist_reallot(hashlist* list1)
{
	float alloted_percent =  ((float)list1->alloted/list1->size)*100 ;
	printf("Realloting Hashlist with allocation %f\n",alloted_percent);
	exit(0);
}

int hashlist_add_implemented(hashlist* list1,char* key_name,int x,int y,int z)
{
	int hash_value;
	if ( list1->Hash == NULL ) 
	{
		 list1->Hash = (hash*)malloc(sizeof(hash) * list1->size );
	}

	float alloted_percent =  ((float)list1->alloted/list1->size)*100 ;
	printf("Adding hash :- %s\t Alloted %f\%\n",key_name,alloted_percent);	 	
	
	if ( alloted_percent >= 80 )
	//if ( ((float)list1->alloted/list1->size)*100 >= 80 ) 
		hashlist_reallot(list1);

	hash_value = hashfunc(key_name,list1->size);
	printf("Hash Value  :- %d\n",hash_value);

	while (list1->Hash[hash_value].valid == 1)
	{		
		if ( hash_value == list1->size-1 )
			hash_value=-1;
		hash_value++;
		printf("Hash %d  Valid %d\n",hash_value,list1->Hash[hash_value].valid);
	}

	list1->Hash[hash_value].key_name=(char*)malloc(sizeof(char)*strlen(key_name)+1);
	strcpy(list1->Hash[hash_value].key_name,key_name);	
	list1->Hash[hash_value].x = x;
	list1->Hash[hash_value].y = y;
	list1->Hash[hash_value].z = z;
	list1->Hash[hash_value].valid = 1;
	list1->alloted++;
	//printf("X %d\n",list1->Hash[hash_value].x);
	
}

void hashlist_display_implemented(hashlist* list1)
{
	int i;
	printf("Displaying Hash list\n");
	for(i=0; i < list1->size; i++)
	{
		if(list1->Hash[i].valid == 1)
		{
			printf("\tName   :- %s\n",list1->Hash[i].key_name);
			printf("\tCoords :- %d %d %d\n",list1->Hash[i].x,list1->Hash[i].y,list1->Hash[i].z);
		}			
	}
}

void hashlist_initialize_implemented(hashlist* list1)
{
	printf("Initializing\n");
	list1->size=10;
	list1->alloted=0;
	list1->Hash=NULL;
}
static const struct hashlist_ops_n hashlist_ops = {		//Redefining Functions to operate on node
	.hashlist_initialize=hashlist_initialize_implemented,
	.hashlist_add=hashlist_add_implemented,
	.hashlist_display=hashlist_display_implemented
};

int main()
{
	int hash;
	hashlist hashlist1;
	hashlist_ops.hashlist_initialize(&hashlist1);
	hashlist_ops.hashlist_add(&hashlist1,"Good",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"Gooesss",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"wood",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_add(&hashlist1,"yest",3,4,4);
	hashlist_ops.hashlist_display(&hashlist1);	
}
