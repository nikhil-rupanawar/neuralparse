#include<stdio.h>
#include<malloc.h>
#include"coords.h"

int create_line(line* line_obj)
{
	line_obj->ne=0;
	line_obj->alloted=0;
}

int line_reallot(line* line_obj)
{
	int i;
	printf("New Reallot %d\n",line_obj->alloted*2);
	line line_tmp;

	line_tmp.ne=0;
	line_tmp.coords_obj=(coords*)malloc(sizeof(coords)*line_obj->alloted*2);	
	line_tmp.alloted=line_obj->alloted*2;
	
	for(i=0; i < line_obj->ne; i++)
	{
		line_ops.line_add(&line_tmp, line_obj->coords_obj[i].x1, line_obj->coords_obj[i].y1, line_obj->coords_obj[i].z1, line_obj->coords_obj[i].x2, line_obj->coords_obj[i].y2, line_obj->coords_obj[i].z2);	
	}
	free(line_obj->coords_obj);		

	line_obj->coords_obj=line_tmp.coords_obj;	
	line_obj->alloted*=2;
}
int line_add_implemented(line* line_obj, int x1, int y1, int z1, int x2, int y2, int z2)
{
	printf("ALLOTED %d\n",line_obj->alloted); 
	if ( line_obj->alloted == 0 )
	{
		line_obj->coords_obj=(coords*)malloc(sizeof(coords)*4);	
		line_obj->alloted=4;
		printf("Empty line\n");
	}
	if ( line_obj->ne == line_obj->alloted )
		line_reallot(line_obj);
		
	line_obj->coords_obj[line_obj->ne].x1=x1;
	line_obj->coords_obj[line_obj->ne].y1=y1;
	line_obj->coords_obj[line_obj->ne].z1=z1;
	line_obj->coords_obj[line_obj->ne].x2=x2;
	line_obj->coords_obj[line_obj->ne].y2=y2;
	line_obj->coords_obj[line_obj->ne].z2=z2;
	printf("%d%d%d%d\n",x1,x2,y1,y2);
	line_obj->ne++;
}
int line_display_implemented(line* line_obj)
{
	int i;
	for(i=0; i < line_obj->ne; i++)
	{
		printf("COORDS\n");
		printf("\t%d %d %d\n",line_obj->coords_obj[i].x1,line_obj->coords_obj[i].y1,line_obj->coords_obj[i].z1);
		printf("\t%d %d %d\n",line_obj->coords_obj[i].x2,line_obj->coords_obj[i].y2,line_obj->coords_obj[i].z2);
	}
}
