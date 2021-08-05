#include <GL/glut.h>
void init (void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}

void lineSegment (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.4,0.2);
    glBegin(GL_LINE_LOOP);
    glVertex2i(180,15);
    glVertex2i(10,145);
    glVertex2i(78,15);
    glEnd();
    glFlush();
}

void main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("Line Loop Program");
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}