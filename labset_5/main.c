#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define CMIN -3.0
#define CMAX 3.0


//global variables to keep track of 4 midpoint of a cell
double m1x, m1y, m2x, m2y, m3x, m3y, m4x, m4y;

//function to generate sample data
int CreateSD(double x, double y)
{
    double a = 0.49, b = 0.5;
    return ceil((x * x + y * y + a * a) * (x * x + y * y + a * a) - 4 * a * a * x * x - b * b * b * b);
}

//function to identify a cell type
int celltype(int a, int b, int c, int d)
{
    return a + b * 2 + c * 4 + d * 8;
}

void findmidpoints(float x, float y)
{
    //dx=dy=0.1
    m1x = x;
    m1y = y + 0.1 / 2.0;

    m2x = x + 0.1 / 2.0;
    m2y = y;

    m3x = x + 0.1;
    m3y = y + 0.1 / 2.0;

    m4x = x + 0.1 / 2.0;
    m4y = y + 0.1;
}

//function to draw lines in a cell type
void drawLines(int n, float x, float y)
{
    findmidpoints(x, y);
    glBegin(GL_LINES);

    switch (n)
    {
    case 1:
    case 14:
        glVertex2d(m1x, m1y);
        glVertex2d(m2x, m2y);
        break;
    case 2:
    case 13:
        glVertex2d(m2x, m2y);
        glVertex2d(m3x, m3y);
        break;
    case 4:
    case 11:
        glVertex2d(m4x, m4y);
        glVertex2d(m3x, m3y);
        break;
    case 7:
    case 8:
        glVertex2d(m4x, m4y);
        glVertex2d(m1x, m1y);
        break;

    case 3:
    case 12:
        glVertex2d(m1x, m1y);
        glVertex2d(m3x, m3y);
        break;
    case 6:
    case 9:
        glVertex2d(m2x, m2y);
        glVertex2d(m4x, m4y);
        break;

    case 5:
        glVertex2d(m1x, m1y);
        glVertex2d(m4x, m4y);
        glVertex2d(m2x, m2y);
        glVertex2d(m3x, m3y);
        break;
    case 10:
        glVertex2d(m1x, m1y);
        glVertex2d(m2x, m2y);
        glVertex2d(m4x, m4y);
        glVertex2d(m3x, m3y);
        break ; 
    }
    glEnd();
    glFlush() ; 
}

void display()
{
    //array of sample data generated
    int SD[100][100];
    int i, j;
    float x, y;
    int c;
    glClear(GL_COLOR_BUFFER_BIT);

    //generate sample data and store on to an array
    for (x = CMIN, i = 0; x < CMAX; i++, x += 0.1)
        for (y = CMIN, j = 0; y < CMAX; j++, y += 0.1)
            SD[i][j] = CreateSD(x, y);
    //assign generated data to vertices in mesh and find cell type to draw lines
    for (x = CMIN, i = 0; x < CMAX; i++, x += 0.1)
        for (y = CMIN, j = 0; y < CMAX; j++, y += 0.1)
        {
            c = celltype(SD[i][j], SD[i + 1][j], SD[i + 1][j + 1], SD[i][j + 1]);
            drawLines(c, x, y);
        }
    glFlush();
}
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(CMIN, CMAX, CMIN * (GLfloat)h / (GLfloat)w, CMAX * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(CMIN * (GLfloat)w / (GLfloat)h, CMAX * (GLfloat)w / (GLfloat)h, CMIN, CMAX);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)

{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Marching Squares");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutMainLoop();
    return 0;
}