#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define CMIN -3.0
#define CMAX 3.0

typedef struct Point{
    double x ,y ;
}Point ; 

//global variables to keep track of 4 midpoint of a cell
Point m1 , m2 , m3 , m4 ; 
const double dx =0.1 , dy = 0.1 ; //increase in x and y 


int CreateSampleData(double x, double y) //return the value of cassini's equation for the curve (sample data)
{
    double a = 0.49, b = 0.5;
    return ceil((x * x + y * y + a * a) * (x * x + y * y + a * a) - 4 * a * a * x * x - b * b * b * b);
}

int celltype(int a, int b, int c, int d) //return the decimal value of the binary number dcba to identify cell type.
{
    return a + b * 2 + c * 4 + d * 8;
}

void findmidpoints(float x, float y)
{
    m1.x = x;
    m1.y = y + dy / 2.0;

    m2.x = x + dx / 2.0;
    m2.y = y;

    m3.x = x + dx ; 
    m3.y = y + dy / 2.0;

    m4.x = x + dx / 2.0;
    m4.y = y + dy;
}

void drawLine(Point a , Point b){
    glVertex2d(a.x, a.y) ; 
    glVertex2d(b.x, b.y) ; 
}

//function to draw lines in a cell type
void drawLines(int n, float x, float y)
{
    findmidpoints(x, y);
    glBegin(GL_LINES);

    switch (n)
    {
    case 1: case 14:
        drawLine(m1 , m2) ; break;
    case 2: case 13:
        drawLine(m2 , m3) ; break;
    case 4: case 11:
        drawLine(m3,m4) ; 
        break;
    case 7: case 8:
        drawLine(m4 ,m1) ; break;
    case 3: case 12:
        drawLine(m1 ,m3) ; break;
    case 6: case 9:
        drawLine(m2 ,m4) ; break;
    case 5:
        drawLine(m1 ,m4) ;
        drawLine(m2 ,m3) ;
        break;
    case 10:
        drawLine(m1 ,m2) ;
        drawLine(m4 ,m3) ;
        break ; 
    }
    glEnd();
}

void display()
{
    //array of sample data generated
    int SD[100][100];
    int i, j;
    double x, y;
    glClear(GL_COLOR_BUFFER_BIT);

    //generate sample data and store on to an array
    for (x = CMIN, i = 0; x < CMAX; i++, x += dx)
        for (y = CMIN, j = 0; y < CMAX; j++, y += dy)
            SD[i][j] = CreateSampleData(x, y);
    //assign generated data to vertices in mesh and find cell type to draw lines
    for (x = CMIN, i = 0; x < CMAX; i++, x += dx)
        for (y = CMIN, j = 0; y < CMAX; j++, y += dy)
        {
            int ct = celltype(SD[i][j], SD[i + 1][j], SD[i + 1][j + 1], SD[i][j + 1]);
            drawLines(ct, x, y);
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
}