
/* Used to read contents of a community File
 * PARAMS:-
 * 1. community : File which contain list of all community
 * */
void read_community(char* community);

/*
 * Used to calculate the modularity of nodei in the community
 * PARAMS:-
 * 1. community : File which contain list of all community
 * 2. nodei     : Node which modularity is to be calculated
 * */
float find_modularity(char* community, char* nodei);

int create_tmp_community(char* community, char* nodei, char* nodej);
int migrate_node(char* community, char* nodei);
int phase1(pool* pool1);
