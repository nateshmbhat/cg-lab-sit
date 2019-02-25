#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std ; 

typedef struct{
	float x , y ; 
}Point ; 

Point m1 ,m2 , m3 ,m4 ; 
float dx = 0.1 ; 

int cellType(int a , int b , int c , int d){
	return a+ b*2 + c*4 + d*8 ; 
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

void displayLines(int cell , float x , float y ){
	findMidPoints(x,y) ; 
	switch(cell){

	}
}

float createSD(float x , float y){
	float a= 0.49 , b= 0.5 ; 
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
	glClearColor(1,1,1,1) ; 
    glColor3f(1 , 0 , 0) ; 




    glFlush() ; 
}

void reshape(int w, int h ){
	glViewport(0,0,w,h) ; 
	glutPostRedisplay() ; 
}


int main(int argc , char ** argv){
	glutInit(&argc , argv) ; 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ; 
	glutCreateWindow("wind") ; 
	glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ; 
	glutMainLoop() ; 
}