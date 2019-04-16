#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std ; 

float fg[]= {1,0,0} ; 
float bg[]= {1,1,1} ; 

void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
    glClearColor(1,1,1,0) ; 

    // glRectf(0,1,1,3) ; 

    glColor3fv(fg); 
    cout<<"running display"; 
    glBegin(GL_LINE_LOOP) ; 
        glVertex2d(120 , 140) ; 
        glVertex2d(420 , 140) ; 
        glVertex2d(420 , 340) ; 
        glVertex2d(120 , 340) ; 
    glEnd() ; 

    glFlush() ; 
}

void setPixelColor(float i , float j ){
    glBegin(GL_POINTS) ;  
    glColor3fv(fg) ; 
    glPointSize(2) ; 
    glVertex2f(i,j) ; 
    glEnd() ; 
    glFlush() ; 
}

void scanline(){
    cout<<"Calling scanline" <<endl; 
    for(int y = 140 ; y<=340 ; y++){
        for(int x = 120 ; x<=420; x++){
            float color[3]  ; 
            glReadPixels(x,y ,1,1,GL_RGB , GL_FLOAT, color )  ;
            if(color[0]==bg[0] && color[1]==bg[1] && color[2]==bg[2]){
                setPixelColor(x,y) ;  
                cout<<"setting pixel color" <<endl; 
            }
        }
    }
}


void mouse(int button , int state , int x , int y){
    if(state==GLUT_DOWN) {
        scanline() ; 
    }
}

void init(){
    glPointSize(2) ; 
    glClearColor(1,1,1,0) ; 
    glColor3fv(fg) ; 
    glMatrixMode(GL_PROJECTION) ; 
    glLoadIdentity() ; 
    gluOrtho2D(0,640, 0, 480) ; 
}

int main(int argc , char **argv){
    glutInit(&argc, argv) ; 
    glutInitDisplayMode(GLUT_SINGLE) ; 
    glutCreateWindow("win") ; 
    glutInitWindowSize(640 , 480) ; 
    init() ; 
    glutDisplayFunc(display) ;  
    glutMouseFunc(mouse) ; 
    glutMainLoop() ; 
}