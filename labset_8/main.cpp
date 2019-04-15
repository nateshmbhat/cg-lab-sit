#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std ; 

int direction = 0 ;
// right , top , left , bottom
int angles[]={0,90,180 , 270} ;  
float x = 0 ; 
float speed = 0.00001 ; 
string color = "red" ; 


void renderCar(){
    glPushMatrix() ; 
        cout<<"x = " << x << endl; 
        x+=speed ; 
        glRotatef(angles[direction] , 0,0,1) ; 
        glTranslatef(x , 0,0) ;  

        glColor3f(color=="red"?1:0,color=="green"?1:0,color=="blue"?1:0) ; 
        glRectf(0,0,0.4,0.4) ;

        glColor3f(0,1,1) ; 
        glRectf(0.1,0,0.18,0.4)  ; 
        glRectf(0.3,0,0.38,0.4)  ; 
          
    glPopMatrix() ; 
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT) ; 
    renderCar() ; 
    glFlush() ; 
}

void idle(){
    glutPostRedisplay() ; 
}

void menuHandler(int id){
    switch(id){
        case 0 : color="red" ; break ; 
        case 1 : color="green" ; break ; 
        case 2 : color="blue" ; break ; 
        case 3 : direction = ((direction+1)%4) ; x =0  ;  break ; 
        case 4 : direction = direction==0?3:(direction-1)%4 ; x= 0  ; break ; 
        case 5 : speed+=0.000001 ;  break; 
        case 6 : speed-=0.000001 ; break ;
    }
}

int main(int argc , char **argv){
    glutInit(&argc, argv) ; 
    glutInitDisplayMode(GLUT_SINGLE) ; 
    glutCreateWindow("dsf") ; 
    glutInitWindowSize(800,800) ; 

    glutDisplayFunc(display) ; 
    glutIdleFunc(idle) ; 

    int colormenu = glutCreateMenu(menuHandler) ;
    glutAddMenuEntry("Red" , 0) ; 
    glutAddMenuEntry("Green" , 1) ; 
    glutAddMenuEntry("Blue" , 2) ; 
    glutCreateMenu(menuHandler) ; 
    glutAddMenuEntry("Left turn" , 3) ; 
    glutAddMenuEntry("right turn" , 4) ; 
    glutAddMenuEntry("speed up" , 5) ; 
    glutAddMenuEntry("slow down" , 6) ; 
    glutAddSubMenu("Color" , colormenu) ; 

    glutAttachMenu(GLUT_RIGHT_BUTTON) ; 

    glutMainLoop() ; 
}