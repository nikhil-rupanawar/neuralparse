#include<GL/glut.h>     /* Header File For The GLUT Library */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<jpeglib.h>
#include"projection.h"
#include"setdata.h"
#include"pool.h"
#include"hashlist.h"
#include"coords.h"
#define ESCAPE 27        /* ESC key code */

int fullscreen=0;        /* toggle fullscreen */
GLint x_position = 0;   /* position on screen */
GLint y_position = 0;

//extern GLfloat w;         /* Window size. Global for use in rotation routine */
//extern GLfloat h;

GLfloat w = 1200;         /* Window size. Global for use in rotation routine */
GLfloat h = 1200;

int object = 0;            /* Pyramid (0) or cube (1) ?? */
int move=0;		   /* 1 tanslate, 2 rotate*/

int traverse=0;
GLint mb = 0;              /* which mouse button we press */
GLfloat rot, w1, w2, w3;   /* Variables for rotation calculation */
GLint prevx, prevy;        /* Remember previous x and y positions */

GLfloat xt=1.0,yt=1.0,zt=1.0;   /* scale */
pool pool1;
hashlist hashlist1;
line line_obj;
/* Image type - contains height, width, and data */

unsigned char *raw_image = NULL;
int width = 1600;
int height = 1200;
int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
int color_space = JCS_RGB; /* or JCS_GRAYSCALE for grayscale images */


int tmp_w;
int tmp_h;

int read_jpeg_file( char *filename )
{
	/* these are standard libjpeg structures for reading(decompression) */
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	JSAMPROW row_pointer[1];
	
	FILE *infile = fopen( filename, "rb" );
	unsigned long location = 0;
	int i = 0;
	
	if ( !infile )
	{
		printf("Error opening jpeg file %s\n!", filename );
		return -1;
	}
	/* here we set up the standard libjpeg error handler */
	cinfo.err = jpeg_std_error( &jerr );
	/* setup decompression process and source, then read JPEG header */
	jpeg_create_decompress( &cinfo );
	/* this makes the library read from infile */
	jpeg_stdio_src( &cinfo, infile );
	/* reading the image header which contains image information */
	jpeg_read_header( &cinfo, TRUE );
	/* Uncomment the following to output image information, if needed. */
	/*--
	printf( "JPEG File Information: \n" );
	printf( "Image width and height: %d pixels and %d pixels.\n", cinfo.image_width, cinfo.image_height );
	printf( "Color components per pixel: %d.\n", cinfo.num_components );
	printf( "Color space: %d.\n", cinfo.jpeg_color_space );
	--*/
	tmp_w=cinfo.image_width;	
	tmp_h=cinfo.image_height;
	/* Start decompression jpeg here */
	jpeg_start_decompress( &cinfo );

	/* allocate memory to hold the uncompressed image */
	raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );
	/* now actually read the jpeg into the raw buffer */
	row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
	/* read one scan line at a time */
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for( i=0; i<cinfo.image_width*cinfo.num_components;i++) 
			raw_image[location++] = row_pointer[0][i];
	}
	/* wrap up decompression, destroy objects, free pointers and close open files */
	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	free( row_pointer[0] );
	fclose( infile );
	/* yup, we succeeded! */
	return 1;
}


GLvoid LoadTexture(GLvoid)
{	


    Image *TextureImage;    
    TextureImage = (Image *) malloc(sizeof(Image));
    if (TextureImage == NULL) {
        printf("Error allocating space for image");
        exit(1);
    }

    if( read_jpeg_file("door.jpg") > 0 ) 
    {
	printf("Success\n");
    }
    else
    {
	exit(1);
    }
      
    /*  2d texture, level of detail 0 (normal), 3 components (red, green, blue),            */
    /*  x size from image, y size from image,                                              */    
    /*  border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. */ 

    //glTexImage2D(GL_TEXTURE_2D, 0, 3,TextureImage->sizeX, TextureImage->sizeY,0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,tmp_w, tmp_h,0, GL_RGB, GL_UNSIGNED_BYTE, raw_image);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); /*  cheap scaling when image bigger than texture */    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); /*  cheap scaling when image smalled than texture*/

    free (TextureImage->data);
    free( TextureImage );
}

/* Our viewing transform */
void transform(GLfloat Width , GLfloat Height )
{
    glViewport(0,0,  (GLfloat)Width,  (GLfloat)Height);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, Width/Height,0.1f,100.0f); 
    glTranslatef(0.0, 0.0, -5.0f);     /* Centre and away the viewer */
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
/* We call this right after our OpenGL window is created.*/

void InitGL(GLint Width, GLint Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);     /* This Will Clear The Background Color To Black*/
	glClearDepth(1.0);                	  /* Enables Clearing Of The Depth Buffer*/
	//LoadTexture();
	glEnable(GL_TEXTURE_2D);                      /*  Enable texture mapping. */
	glDepthFunc(GL_LESS);             	/* The Type Of Depth Test To Do*/
	glEnable(GL_DEPTH_TEST);          	/* Enables Depth Testing*/
	glShadeModel(GL_SMOOTH);          	/* Enables Smooth Color Shading*/
	if (traverse==0)
	{	
		printf("Displaying AGAIN\n");
		setdata(&pool1,&hashlist1,&line_obj);
		traverse==1;
	}

    transform(Width,Height);          /* Do our viewing transform */
}


/* The function called when our window is resized */
void ReSizeGLScene(GLint Width, GLint Height)
{
  if (Height==0)    /* Prevent A Divide By Zero If The Window Is Too Small*/
    Height=1;

    transform(Width,Height);    /* Do our viewing transform */
    w = glutGet((GLenum)GLUT_WINDOW_WIDTH);    /* Make sure our window size is updated */
    h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
}


GLvoid draw_room()
{
	int i;
	float ix,iy,iz;
	ix=-1.0f;
	iy=-2.1f;
	iz=-0.1f;
	glPushMatrix();
	printf("DISPLAYING HASH\n");
	printf("LIST SIZE %d\n",hashlist1.size);
/*
	for(i=0; i < hashlist1.size; i++)
	{
		if(hashlist1.Hash[i].valid == 1)
		{
			printf("\tName   :- %s\n",hashlist1.Hash[i].key_name);
			printf("\tCoords :- %d %d %d\n",hashlist1.Hash[i].x,hashlist1.Hash[i].y,hashlist1.Hash[i].z);
		}			
	}
*/
	for(i=0; i < hashlist1.size; i++)
 	{
		if (hashlist1.Hash[i].valid != 1) continue;
    		//glMatrixMode(GL_MODELVIEW);
  	//	glTranslatef(0.4,0,0);
    		//glRotatef(4*rot, w1, w2, w3);    /* Do the transformation */
		glShadeModel(GL_SMOOTH); 
  		glLineWidth(1.0);                             
	  	glPointSize(4.0);                             /* Add point size, to make it clear */
  		glBegin(GL_POINTS);                /* start drawing the cube.*/
	  	glColor3f(1.0f,1.0f,1.0f);            /* Set The Color To Orange*/
  		glVertex3f((float)hashlist1.Hash[i].x,(float)hashlist1.Hash[i].y,(float)hashlist1.Hash[i].z);        /* Bottom Left Of The Quad (Left)*/
	  	glEnd();                              /* Done Drawing The Cube*/
  		glEnable(GL_DEPTH_TEST);
 	 }
	for(i=0; i < line_obj.ne; i++)
 	{
    		//glMatrixMode(GL_MODELVIEW);
  	//	glTranslatef(0.4,0,0);
    		//glRotatef(4*rot, w1, w2, w3);    /* Do the transformation */
		glShadeModel(GL_SMOOTH); 
  		glLineWidth(1.0);                             
	  	glPointSize(4.0);                             /* Add point size, to make it clear */
  		//glLineWidth(1.0);                             
	  	//glPointSize(4.0);                             /* Add point size, to make it clear */
  		glBegin(GL_LINES);                /* start drawing the cube.*/
	  	glColor3f(1.0f,0.0f,1.0f);            /* Set The Color To Orange*/
  		//glVertex3f((float)hashlist1.Hash[i].x,(float)hashlist1.Hash[i].y,(float)hashlist1.Hash[i].z);        /* Bottom Left Of The Quad (Left)*/

  		glVertex3f((float)line_obj.coords_obj[i].x1,(float)line_obj.coords_obj[i].y1,(float)line_obj.coords_obj[i].z1);        /* Bottom Left Of The Quad (Left)*/
  		glVertex3f((float)line_obj.coords_obj[i].x2,(float)line_obj.coords_obj[i].y2,(float)line_obj.coords_obj[i].z2);        /* Bottom Left Of The Quad (Left)*/
	  	glEnd();                              /* Done Drawing The Cube*/
  		glEnable(GL_DEPTH_TEST);
 	 }
	
  	glPopMatrix();
}


/* The main drawing function. */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    /* Clear The Screen And The Depth Buffer*/ 
    printf("%f %f %f\n",xt,yt,zt);
    printf("%f %f %f %f\n",rot,w1,w2,w3);
    glPushMatrix();
   
  
    glMatrixMode(GL_PROJECTION);
   // if ( move==2 )
    {
   	 glRotatef(4*rot, w1, w2, w3);    /* Do the transformation */
	 move=0;
    }
    glMatrixMode(GL_MODELVIEW);
   // if ( move==1 )
    {
    	glTranslatef(xt,yt, zt);
	move=0;
    }
  //glScalef(xt,yt,zt);
//    if( object == 0 )                /* Draw an object */
//        draw_pyramid();
//    else
//        draw_cube();

  //  glLoadIdentity();


    draw_room();
    glPopMatrix();
    glutSwapBuffers();               /* Swap buffers */
    glFlush();
}

/* The function called whenever a "normal" key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{

    switch ( key )    { 
     case ESCAPE :
        exit(0);                   
        break;

     case 'O':
     case 'o':
        object = object ? 0 : 1;    /* Switch object which is plotted */
        glutPostRedisplay();        /* Redisplay please */
        break;
     case 'x':                          /* Scale x up */
        xt += 0.2;
	move=1;
        glutPostRedisplay();
        break;
     case 'X':
        xt -= 0.2;                      /* Scale x down */
	move=1;
        glutPostRedisplay();
        break;

      case 'y':                          /* Scale y up */
        yt += 0.2;
	move=1;
        glutPostRedisplay();
        break;
     case 'Y':
        yt -= 0.2;                      /* Scale y down */
	move=1;
        glutPostRedisplay();
        break;

      case 'z':                          /* Scale z up */
        zt += 0.2;
	move=1;
        glutPostRedisplay();
        break;
     case 'Z':
        zt -= 0.2;                      /* Scale z down */
	move=1;
        glutPostRedisplay();
        break;
     case 'r':				/* Reset */
	xt = 1.0;
	yt = 1.0;
	zt = 1.0;
	rot = 0.0;
	w1 = 0.0;
	w2 = 0.0;
	w3 = 0.0;
        glutPostRedisplay();
	//DrawGLScene();    
    	break;
	
     default:
        break;
    }

}

/* The function called whenever a "special" key is pressed. */
void specialKeyPressed(int key, int x, int y) 
{
   switch (key) {    
    case GLUT_KEY_F1:
    fullscreen = !fullscreen;
    if (fullscreen) {
        x_position = glutGet((GLenum)GLUT_WINDOW_X);    /* Save parameters */
        y_position = glutGet((GLenum)GLUT_WINDOW_Y);
        w = glutGet((GLenum)GLUT_WINDOW_WIDTH);
        h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
        glutFullScreen();                /* Go to full screen */
    } else {
        glutReshapeWindow(w, h);        /* Restore us */
        glutPositionWindow(x_position, y_position);
    }
        break;
     default:
        break;
        }
}

/* Routine to compute the axis and angle of rotation of a "crystal sphere"
   inverted on the canvas, under the action of the mouse.
 
   The mouse moves from the point (x,y) on canvas by the amount (dx, dy).
   This causes the glass sphere to rotate about an axis (w1,w2,w3) by an
   angle "rot".  The axis is computed with respect to the coordinates
   attached to the sphere, not the world frame.

*/
void find_axis_of_rotation(int x, int y, int dx, int dy,GLfloat *rot, GLfloat *w1, GLfloat *w2, GLfloat *w3)
{
    GLfloat m[16];    /* To return the OpenGL transformation matrix values */
    float z, dz;
    float R2, r2;
    float a1, a2, a3;

    w = glutGet((GLenum)GLUT_WINDOW_WIDTH); /* Make real sure we have the correct */
    h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);/* window height and width */

    R2 = (w*w+h*h)/4;    /* sqrt(R2) is window's half-diagonal */

    /* z determines the mouse contact point (x,y,z) on the
     * "invisible glass" sphere (of radius sqrt(R2).
    */
    r2 = x*x + y*y;
    z = sqrt(R2-r2);

    /* The motion of the mouse produces a vector (dx,dy,dz).
     * The first two components are read off the screen.  The
     * third component is computed assuming that the vector
     * (dx,dy,dz) is tangent to the sphere, thus orthogonal
     * to the vector (x,y,z).
    */
    dz = -(x*dx+y*dy)/z;

    /* the action of the displacement vector (dx,dy,dz) at the
     * contact point (x,y,z) rotates the virtual "glass sphere" about
     * an axis (a1,a2,a3) which is computed as the cross-product
     * of the vectors (x,y,z) and (dx,dy,dz).
    */
    a1 = y*dz-z*dy;
    a2 = z*dx-x*dz;
    a3 = x*dy-y*dx;

    /* the rotation angle equals displacement over the radius.  */
    *rot = (180/M_PI)*sqrt(dx*dx+dy*dy+dz*dz)/sqrt(R2);

    /* The components (a1,a2,a3) of the axis of rotation w are
     * with respect to the coordiantes fixed to the screen.
     * We convert this to the model's local coordinates and
     * arrive at the rotation axis (w1, w2, w3) which
     * is computed as M^T a, where M is the ModelView matrix.
    */
    glGetFloatv(GL_MODELVIEW_MATRIX,m);
    *w1 = m[0]*a1 + m[1]*a2 + m[2]*a3;
    *w2 = m[4]*a1 + m[5]*a2 + m[6]*a3;
    *w3 = m[8]*a1 + m[9]*a2 + m[10]*a3;
}

GLvoid Mouse( int b , int s, int xx, int yy)
{
    switch (b) {
    case GLUT_LEFT_BUTTON:	/* only stash away for left mouse */
        prevx = xx - w/2;
        prevy = h/2 - yy;
        mb = 0;                 /* Note which button */
    break;
    case GLUT_MIDDLE_BUTTON:
        mb = 1;                 /* Note if user pressed t'other button */
        break;
    case GLUT_RIGHT_BUTTON:
        mb = 2;                 /* and the 3rd if 3 button-ing */
        break;
    }
}

GLvoid Motion( int xx , int yy )
{
    int x, y, dx, dy;
        
    if( mb == 0 )            /* only for left mouse folks */
    {
	move=2;
        x = xx - w/2;
        y = h/2 - yy;
        dx = x - prevx;
        dy = y - prevy;
        prevx = x; /* Save x and y for dx and dy calcs next time */
        prevy = y;
        find_axis_of_rotation(x, y, dx, dy, &rot, &w1, &w2, &w3);
        //glutPostRedisplay();
        DrawGLScene();

    }  
}

