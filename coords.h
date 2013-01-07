
struct coords_t
{
	int x1;
	int y1;
	int z1;
	int x2;
	int y2;
	int z2;
};
typedef struct coords_t coords;

struct line_t
{
	coords* coords_obj;
	int ne;
	int alloted;
};
typedef struct line_t line;

struct line_ops_n
{	
	int (*line_add)(line* line_obj, int x1, int y1, int z1, int x2, int y2, int z2);
	int (*line_display)(line* line_obj);
};

int line_add_implemented(line* line_obj, int x1, int y1, int z1, int x2, int y2, int z2);
int line_display_implemented(line* line_obj);

static const struct line_ops_n line_ops = {		//Redefining Functions to operate on line
	.line_add=line_add_implemented,
	.line_display=line_display_implemented
};

int create_line(line* line_obj);
int line_reallot(line* line_obj);


/**Usage

	line line_obj; 
	create_line(&line_obj);
	line_ops.line_add(&line_obj,1,1,1,1,1,1);
	line_ops.line_add(&line_obj,2,2,2,2,2,2);
	line_ops.line_display(&line_obj);
*/
