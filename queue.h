struct queue_node_t
{
	char* key;
	int weight;
	int no;			//No of nodes in community	
	int x1;
	int x2;
	int y1;
	int y2;
	struct queue_node_t* next;
};
typedef struct queue_node_t queue_node;

struct queue_t
{
	int ne;
	queue_node* front;
	queue_node* rear;
};
typedef struct queue_t queue;
int queue_initialize(queue* q1);
int queue_add(queue* q1, char* key, int weight, int no, int x1, int x2, int y1, int y2);
queue_node* queue_remove(queue* q1);
queue_node* queue_get(queue* q1,int pos);
int queue_update(queue* q1,int pos,char* key,int weight, int no, int x1, int x2, int y1, int y2);
	
/* USAGE
 *
 * queue q1;
 * queue_initialize(&q1);
 * queue_add(&q1,"key1",100,1,0,1,1,2);
 * queue_add(&q1,"key2",100,1,0,1,1,2);
 * queue_add(&q1,"key3",100,1,0,1,1,2);
 * queue_add(&q1,"key4",100,1,0,1,1,2);
 * queue_display(&q1);
 * queue_node* n1 = (queue_node*)queue_remove(&q1);
 * printf("R1 %s",n1->key);	
 * queue_update(&q1,2,"key2_change",200,3,0,1,1,2);
 * queue_display(&q1);	
 */
