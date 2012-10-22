#include<GL/glut.h>     /* Header File For The GLUT Library */
#include"projection.h"

//extern GLfloat w;         /* Window size. Global for use in rotation routine */
//extern GLfloat h;

int main(int argc, char **argv) 
{  
    glutInit(&argc, argv);                     /* Initialize GLUT state */
    glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE |GLUT_DEPTH);           /* Select type of Display mode */  
    glutInitWindowSize( (GLint)1200,(GLint)1200);    /* get a 640 x 480 window */
    glutInitWindowPosition(0, 0);              /* top left please */
    window = glutCreateWindow("\"Crystal sphere\" mouse rotation");   /* Open window */
    glutDisplayFunc(DrawGLScene);              /* Drawing function */
    glutReshapeFunc(ReSizeGLScene);            /* resize function */
    glutKeyboardFunc(keyPressed);              /* Processor for "normal keys" */
    glutSpecialFunc(specialKeyPressed);        /* Processor for "special keys" */
    glutMouseFunc( Mouse );                    /* Mouse button pressed function */
    glutMotionFunc( Motion );                  /* Mouse motion function */
    InitGL( (GLint)1200 , (GLint)1200 );             /* Init Open GL window attributes */
    glutMainLoop();                            /* Process events */
  return 1;                                    /* ANSI rules, ok? */
}
