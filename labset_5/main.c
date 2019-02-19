#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>

#define CMIN -3.0
#define CMAX 3.0
#define THS 0.0
#define NC 62
//global variables to keep track of 4 midpoint of a cell
double m1x,m1y,m2x,m2y,m3x,m3y,m4x,m4y;

//function to generate sample data
double CreateSD(double x,double y)
{
double a=0.49, b=0.5;
return (x*x+y*y+a*a)*(x*x+y*y+a*a)-4*a*a*x*x-b*b*b*b;
}

//function to identify a cell type
int celltype(double a, double b, double c, double d)
{
    int n=0;
    if(a>THS) n+=1;
    if(b>THS) n+=2;
    if(c>THS) n+=4;
    if(d>THS) n+=8;
    return n;
}

//function to draw lines in a cell type
void drawLines(int n, float x, float y)
{
    void drawOne(int n, float x, float y);
    void drawAdjacent(int n, float x, float y);
    void drawOpposite(int n, float x, float y);


    switch(n)
    {
        case 1:case 2:case 4:case 7:case 8: case 11: case 13:case 14:
            drawOne(n,x,y);
            break;
        case 3:case 6:case 9:case 12:
            drawAdjacent(n,x,y);
            break;
        case 5: case 10:
            drawOpposite(n,x,y);
            break;
        case 0:case 15:
            break;
    }
}


void findmidpoints(float x, float y)
{
//dx=dy=0.1
m1x= x;
m1y = y+0.1/2.0;

m2x= x+0.1/2.0;
m2y= y;

m3x= x+0.1;
m3y= y+0.1/2.0;

m4x= x+0.1/2.0;
m4y= y+0.1;
}


void drawOne(int n, float x,float y)
{
findmidpoints(x,y);
glBegin(GL_LINES);
switch(n)
{
    case 1: case 14:
        glVertex2d(m1x,m1y);
        glVertex2d(m2x,m2y);
        break;
    case 2: case 13:
        glVertex2d(m2x,m2y);
        glVertex2d(m3x,m3y);
        break;
    case 4: case 11:
        glVertex2d(m4x,m4y);
        glVertex2d(m3x,m3y);
        break;
    case 7: case 8:
        glVertex2d(m4x,m4y);
        glVertex2d(m1x,m1y);
     }
glEnd();
}

void drawAdjacent(int n, float x,float y)
{
findmidpoints(x,y);
glBegin(GL_LINES);
switch(n)
{
    case 3: case 12:
        glVertex2d(m1x,m1y);
        glVertex2d(m3x,m3y);
        break;
    case 6: case 9:
        glVertex2d(m2x,m2y);
        glVertex2d(m4x,m4y);

}
glEnd();
}

void drawOpposite(int n, float x,float y)
{
findmidpoints(x,y);
glBegin(GL_LINES);
switch(n)
{
    case 5:
        glVertex2d(m1x,m1y);
        glVertex2d(m4x,m4y);
        glVertex2d(m2x,m2y);
        glVertex2d(m3x,m3y);
        break;
    case 10:
        glVertex2d(m1x,m1y);
        glVertex2d(m2x,m2y);
        glVertex2d(m4x,m4y);
        glVertex2d(m3x,m3y);


}
glEnd();
}

void display()
{
//array of sample data generated
double SD[NC][NC];
int i,j;
float x,y;
int c;
glClear(GL_COLOR_BUFFER_BIT);

//generate sample data and store on to an array
for(x=-3.0,i=0;x<3.0;i++,x+=0.1)
    for(y=-3.0,j=0;y<3.0;j++,y+=0.1)
        SD[i][j]= CreateSD(x,y);
//assign generated data to vertices in mesh and find cell type to draw lines
for(x=-3.0,i=0;x<3.0;i++,x+=0.1)
    for(y=-3.0,j=0;y<3.0;j++,y+=0.1)
    {
        c=celltype(SD[i][j],SD[i+1][j],SD[i+1][j+1],SD[i][j+1]);
        drawLines(c,x,y);
    }
glFlush();
}
void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
    gluOrtho2D(CMIN,CMAX,CMIN*(GLfloat)h/(GLfloat)w,CMAX*(GLfloat)h/(GLfloat)w);
    else
    gluOrtho2D(CMIN*(GLfloat)w/(GLfloat)h,CMAX*(GLfloat)w/(GLfloat)h,CMIN, CMAX);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)

{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Marching Squares");
     glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
      glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glutMainLoop();
    return 0;
}