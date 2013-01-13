struct area_t
{
    int no;		//For no of communities
    int x1;
    int x2;
    int y1;
    int y2;
};
typedef struct area_t area;

/* Function : edges_node
 * Description : return the no of edges in the given community file
 * Params:
 * 	1. node     :- node file whose edges need to be found  
 * Return Value: 
 * 	1: success
 */
int edges_node(char* node);

int set_area(area* a1,int no,int x1,int x2, int y1, int y2);

/* Function : calculate_area
 * Params:
 * 	1. a1     :- src area  
 * 	2. a2     :- dst area
 * 	3. weight :- The %age of area to be allocated to a2
 * 	4. alloted_weight :- The %age area which is already allocated to other Commmunity
 * Return Value: 
 * 	1: success
 */
int calculate_area(area* a1, area* a2,int weight,int alloted_weight);

typedef struct hashlist_t hashlist;
int distribute(int pass_no,hashlist* hashlist1);
