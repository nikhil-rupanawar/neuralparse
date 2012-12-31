
GLint Window;              /* The number of our GLUT window */
GLint subWindow1;
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
GLint dl ;
typedef struct Image Image;


void displaylist();
int read_jpeg_file( char *filename );
GLvoid LoadTexture(GLvoid);
void transform(GLfloat Width , GLfloat Height );
void InitGL(GLint Width, GLint Height);
void ReSizeGLScene(GLint Width, GLint Height);
GLvoid draw_room();
void DrawGLScene();
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y) ;
void find_axis_of_rotation(int x, int y, int dx, int dy,GLfloat *rot, GLfloat *w1, GLfloat *w2, GLfloat *w3);
GLvoid Mouse( int b , int s, int xx, int yy);
GLvoid Motion( int xx , int yy );
GLvoid passiveMouseMotion_function( int xx , int yy );
