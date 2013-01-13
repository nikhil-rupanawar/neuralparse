struct hash_t2
{
	/*File Name . x,y,z coordinates*/
	char* key_name;		
	char* extra;
	int x;			
	int y;
	int z;
	int valid;
};
typedef struct hash_t2 hash2;

struct hashlist_t2
{
	int size;
	int alloted;
	hash2* Hash;
};
typedef struct hashlist_t2 hashlist2;

struct hashlist_ops_n2
{
	void (*hashlist_initialize2)(hashlist2* list1);
	int (*hashlist_add2)(hashlist2* list1, char* key_name,char* extra,int x, int y, int z);
	void (*hashlist_display2)(hashlist2* list1);
	hash2* (*hashlist_findhash2)(hashlist2* list1, char* key_name);
	void (*hashlist_destroy2)(hashlist2* list1);
};
static const struct hashlist_ops_n2 hashlist_ops2;

void hashlist_reallot2(hashlist2* list1);
int hashlist_add_implemented2(hashlist2* list1,char* key_name,char* extra,int x,int y,int z);
void hashlist_display_implemented2(hashlist2* list1);
void hashlist_initialize_implemented2(hashlist2* list1);
void hashlist_destroy_implemented2(hashlist2* list1);
hash2* hashlist_findhash_implemented2(hashlist2* list1, char* key_name);

static const struct hashlist_ops_n2 hashlist_ops2 = {		//Redefining Functions to operate on node
	.hashlist_initialize2=hashlist_initialize_implemented2,
	.hashlist_add2=hashlist_add_implemented2,
	.hashlist_display2=hashlist_display_implemented2,
	.hashlist_findhash2=hashlist_findhash_implemented2,
	.hashlist_destroy2=hashlist_destroy_implemented2
};


/*Usage
hashlist2 list1;
hashlist_ops2.hashlist_initialize2(&list1);
hashlist_ops2.hashlist_add2(&list1,"A","sd",3,4,4);
hashlist_ops2.hashlist_add2(&list1,"N","sd",3,4,4);
hashlist_ops2.hashlist_add2(&list1,"N","sd",3,4,4);
hashlist_ops2.hashlist_display2(&list1);	
hash* h1 = hashlist_ops2.hashlist_findhash2(&list1,"key");	
*/
