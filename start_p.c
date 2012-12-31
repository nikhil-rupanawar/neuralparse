#include<GL/glut.h>     /* Header File For The GLUT Library */
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include"projection.h"

//extern GLfloat w;         /* Window size. Global for use in rotation routine */
//extern GLfloat h;
int flag;
void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 
    // register callbacks
    //glutIgnoreKeyRepeat(1);
    //glutSpecialUpFunc(releaseKey);
    glutReshapeFunc(ReSizeGLScene);            /* resize function */
    glutKeyboardFunc(keyPressed);              /* Processor for "normal keys" */
    glutSpecialFunc(specialKeyPressed);        /* Processor for "special keys" */
    glutMouseFunc( Mouse );                    /* Mouse button pressed function */
    glutMotionFunc( Motion );                  /* Mouse motion function */
    glutPassiveMotionFunc(passiveMouseMotion_function);                  /* Passive Mouse motion function */
}

int main(int argc, char **argv) 
{  
    int c;
    opterr = 0;
    while ((c = getopt (argc, argv, "abc:")) != -1)
    {
        switch(c)
        {
            case 'a':
		flag=1;
		printf("value =%s",optarg);
            case 'b':
                flag+=2;
            case 'c':
                flag+=4;
        }
    }
    printf("FLAG is %d",flag);
    glutInit(&argc, argv);                                             /* Initialize GLUT state */
    glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE |GLUT_DEPTH);           /* Select type of Display mode */  
    glutInitWindowSize( (GLint)1200,(GLint)1200);                      /* get a 640 x 480 window */
    glutInitWindowPosition(0, 0);                                      /* top left please */
    Window = glutCreateWindow("\"Crystal sphere\" mouse rotation");    /* Open window */
    glutDisplayFunc(DrawGLScene);             	                       /* Drawing function */
    init();
    displaylist();
    InitGL( (GLint)1200 , (GLint)1200 );                               /* Init Open GL window attributes */

    //subWindow1 = glutCreateSubWindow(Window, 0,0,600,400);
    //glutDisplayFunc(DrawGLScene);
    //init(); 
    glutMainLoop();                                                    /* Process events */
    return 1;                                                          /* ANSI rules, ok? */
}
