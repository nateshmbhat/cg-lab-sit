#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std ;

int choice ; 

void drawPoints(int primitive){
    glBegin(primitive) ; 
    glVertex2f(0.1,0.1) ; 
    glVertex2f(0.1,0.3) ; 
    glVertex2f(0.3,0.3) ; 
    glVertex2f(0.3,0.1) ; 
    glVertex2f(0.4,0.6) ; 
    glVertex2f(0.5,0.8) ; 
    glEnd() ; 
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
    glClearColor(0,0,0,1) ; 

    switch(choice){
        case 0 : drawPoints(GL_POINTS) ;break ; 
        case 1 : drawPoints(GL_TRIANGLES) ; break ; 
        case 2 : drawPoints(GL_QUADS) ; break ; 
        case 3 : drawPoints(GL_LINES) ; break ; 
        case 4 : drawPoints(GL_LINE_STRIP) ; break ; 
        case 5 : drawPoints(GL_LINE_LOOP) ; break ; 
        case 6 : drawPoints(GL_TRIANGLE_STRIP) ; break ; 
        case 7 : drawPoints(GL_TRIANGLE_FAN) ; break ; 
        case 8 : drawPoints(GL_QUAD_STRIP) ; break ; 
        case 9 : drawPoints(GL_POLYGON) ; break ; 
    }

    glFlush() ; 
}

void reshape(int w , int h){
    glViewport(0 , 0 , w, h) ; 
    glMatrixMode(GL_PROJECTION) ; 
    glLoadIdentity() ; 
    gluOrtho2D(0,1,0 ,1) ; 
    glMatrixMode(GL_MODELVIEW) ; 
}

int main(int argc , char ** argv){
    glutInit(&argc , argv) ;  
    glutInitDisplayMode(GLUT_SINGLE) ;
    glutCreateWindow("glut") ; 
    glutDisplayFunc(display) ; 
    glutReshapeFunc(reshape) ; 

    cout<<"Enter choice : " ; 
    cin>>choice ;
    glutMainLoop() ; 
}