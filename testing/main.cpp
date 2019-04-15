#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std ; 

#define CMIN -3.0
#define CMAX 3.0

typedef struct{
	float x , y ; 
}Point ; 

Point m1 ,m2 , m3 ,m4 ; 
float dx = 0.1 ; 

int cellType(int a , int b , int c , int d){
	return a+ b*2 + c*4 + d*8 ; 
}

void drawLine(Point a, Point b){
	glBegin(GL_LINES) ;
	glVertex2f(a.x,a.y) ; 
	glVertex2f(b.x,b.y) ; 
	glEnd() ; 
}

void findMidPoints(float x , float y){
	m1.y = y+dx/2 ; 	
	m1.x = x ; 

	m2.y = y+dx ; 
	m2.x = x+dx/2 ; 

	m3.x = x+dx ; 
	m3.y = y+dx/2 ; 

	m4.x = x+dx/2 ; 
	m4.y = y ; 
}

void drawLines(int cell , float x , float y ){
	findMidPoints(x,y) ; 

	switch(cell){
		case 1 : case 14 : 
			drawLine(m1 , m4) ; 
			break;
		case 2 : case 13:
			drawLine(m3 , m4) ; 
			break;
		case 4 : case 11 : 
			drawLine(m2,m3) ;
			break;
		case 8 : case 7 :
			drawLine(m1,m2) ; 
			break;
		
		case 3 : case 12 : 
			drawLine(m1,m3) ; 
			break;
		case 6 : case 9 : 
			drawLine(m2,m4) ; 
			break;
		
		case 5:
			drawLine(m1,m2) ; 
			drawLine(m3,m4) ; 
			break;
		case 10:
			drawLine(m1,m4) ; 
			drawLine(m2,m3) ; 
	}

}

int createSD(float x , float y){
	float a= 0.49 , b= 0.5 ; 
	return ceil(pow( x*x+a*a+y*y , 2) - 4*a*a*x*x - pow(b,4)) ; 
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
	glClearColor(1,1,1,1) ; 

    glColor3f(1 , 0 , 0) ; 

	int SD[100][100] ; 
	double  x , y ; 
	int i , j ; 

	for(x = -3.0, i =0  ; x<3.0 ; i++, x+=dx)
	{
		for(y = -3.0 , j =0 ; y<3.0 ; j++ , y+=dx)
		{
			SD[i][j] = createSD(x,y) ; 
		}
	}

	for(x = -3.0, i =0  ; x<3.0 ; i++, x+=dx)
	{
		for(y = -3.0 , j =0 ; y<3.0 ; j++ , y+=dx)
		{
			int c= cellType(SD[i][j] , SD[i+1][j],SD[i+1][j+1] , SD[i][j+1]) ; 
			drawLines(c , x , y) ; 
		}
	}
	
    glFlush() ; 
}

void reshape(int w, int h ){
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(CMIN, CMAX, CMIN * (GLfloat)h / (GLfloat)w, CMAX * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(CMIN * (GLfloat)w / (GLfloat)h, CMAX * (GLfloat)w / (GLfloat)h, CMIN, CMAX);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc , char ** argv){
	glutInit(&argc , argv) ; 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ; 
	glutCreateWindow("wind") ; 
	glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ; 
	glutMainLoop() ; 
}