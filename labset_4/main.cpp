#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std ; 

float P[][3] = {{-1 ,-0.5,0} , {1 , -0.5 , 0} , {0,1,0} , {0,0,1}} ; 
int m ; 

void triangle(float a[] , float b[] , float c[]){
    glBegin(GL_TRIANGLES) ; 
    glVertex2fv(a) ;
    glVertex2fv(b) ;
    glVertex2fv(c) ;
    glEnd() ; 
}


void divide_triangle( float a[] , float b[] , float c[], int m ){
    if(m>1){
        float ab[3] , bc[3] , ac[3] ; 
        for(int i =0 ;i < 3 ; i++){
            ab[i] = (a[i]+b[i])/2 ; 
            ac[i] = (a[i]+c[i])/2 ; 
            bc[i] = (b[i]+c[i])/2 ; 
        }

    glColor3f(1, 0 , 1) ; 
        divide_triangle(ab , ac , a , m-1) ; 
    glColor3f(0, 1 , 0.5) ; 
        divide_triangle(b , bc , ab , m-1) ; 

    glColor3f(0.2, 0.4 , 1) ; 
        divide_triangle(c , bc , ac , m-1) ; 

    }
    else{
        triangle(a , b , c) ; 
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ; 

    glColor3f(1, 0 , 0) ; 
    divide_triangle(P[0] , P[1] , P[2] , m ) ; 

    glColor3f(0, 1 , 0) ; 
    divide_triangle(P[1] , P[2] , P[3] , m ) ; 

    glColor3f(0, 0 , 1) ; 
    divide_triangle(P[2] , P[3] , P[1] , m ) ; 

    glColor3f(1, 0 , 1) ; 
    divide_triangle(P[3] , P[0] , P[1] , m ) ; 

    glutSwapBuffers() ; 
    glFlush() ; 
}

int main(int argc , char **arr){
    glutInit(&argc , arr) ; 
    cout<<"Enter m : " ; cin>>m ; 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH) ; 
    glutCreateWindow("hll") ; 
    glutDisplayFunc(display) ; 
    glutMainLoop() ; 

}