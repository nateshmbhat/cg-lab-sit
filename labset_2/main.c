#include <stdio.h>
#include <GL/glut.h>

void display2d()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0) ; 

    glRectd(-1 , -1 ,1 , 1) ; 

    glFlush();
}

void display3d()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,1) ; 
    glColor3f(1,0,0) ; 

    glPushMatrix() ; 
    glutWireTeapot(1) ; 
    glPopMatrix() ; 

    glFlush();
}


void init2d(int ch)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    if (ch == 1)
        glutCreateWindow("2d orthogonal view");
    else
        glutCreateWindow("2d perspective view");
    glutDisplayFunc(display2d);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ch == 1)
        gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    else
    {
        gluPerspective(30.0, 1.0, 1.0, 100.0);
        gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutMainLoop();
}
void init3d(int ch)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    if (ch == 1)
        glutCreateWindow("3d orthogonal view");
    else
        glutCreateWindow("3d perspective view");
    glutDisplayFunc(display3d);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ch == 1)
        glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    else
    {
        glFrustum(-2, 2, -2, 2, 1, 10);
        gluLookAt(1, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutMainLoop();
}

int main(int argc, char **argv)
{
    int ch ; 
    glutInit(&argc, argv);
    while (1)
    {
        printf("\nenter your choice:\n1.2d with ortho\n2.2d with perspective\n3.3d with ortho\n4.3d with perspective\n");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                init2d(1);
                break;
            case 2:
                init2d(2);
                break;
            case 3:
                init3d(1);
                break;
            case 4:
                init3d(2);
                break;
        }
        glEnable(GL_DEPTH_TEST);
    }
    return 0;
}