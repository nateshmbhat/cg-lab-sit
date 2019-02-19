#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std ; 


void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
    glColor3f(1 , 0 , 0) ; 

    glBegin(GL_POLYGON)  ; 
        glVertex2f(100 , 0) ; 
        glVertex2f(108 , 54) ; 
        glVertex2f(200 , 38) ; 
        glVertex2f( 20 , 28) ; 
    glEnd() ; 

    glFlush() ; 
}

void reshape(int w, int h ){
	glViewport(0 , 0 , w , h) ; 
	glMatrixMode(GL_PROJECTION) ; 
	glLoadIdentity() ; 
	gluOrtho2D(0 , w , 0 , h) ; 
	glMatrixMode(GL_MODELVIEW) ; 
	glLoadIdentity() ; 
}


int main(int argc , char ** argv){
	glutInit(&argc , argv) ; 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ; 
	glutCreateWindow("wind") ; 
	glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ; 
	glutMainLoop() ; 
}