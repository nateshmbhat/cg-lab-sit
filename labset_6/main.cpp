#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std ; 

typedef struct Point{
	int x , y ; 
} Point; 

class Polygon{
	private : 
	vector< Point > points ; 

	public : 
	bool visible ; 
	static bool newPolygonFlag  ; //flag which is true when user is making a new polygon. becomes false when he selects end polygon.
	static int selectedPolygon  ;//position of the selected Polygon in vector<Polygon>
	int xmax , xmin , ymax , ymin ; 
    int id ; 

	Polygon(const vector<Point> & P , int pid ){//first time polygon creation 
		visible = true ; 
		id = pid ; 
		xmax = -999 , xmin = 999 , ymax = -999 , ymin = 999 ; 
		for(int i =0 ; i < P.size() ; i++) { 
			points.push_back(P[i]) ; 
			xmax = max(P[i].x , xmax)  , xmin = min(P[i].x , xmin) ; //set the bounding box coordinates by finding max and min of x and y
			ymax = max(P[i].y , ymax)  , ymin = min(P[i].y , ymin) ; 
		}
	}
	void setVisible(bool flag) {visible = flag ; }
	void setSelectedPolygon(int pos ){ selectedPolygon = pos ; } ;  //method to select a polygon
	void drawPolygon(){
		if(!visible) return ; 
		if(selectedPolygon==id) glColor3f(0 , 1 , 0) ; 
		else glColor3f(1 , 0 , 0) ; 
		glBegin(GL_POLYGON) ; 
			for(int i =0 ; i < points.size() ; i++) 
                glVertex2d(points[i].x , points[i].y) ; 
		glEnd() ; 
	}
};

bool Polygon::newPolygonFlag = false ; 
int Polygon::selectedPolygon = -1 ; 
vector<Point> clickPoints ;  //points to keep track when polygon is being constructed by repeated clicking at screen
vector<Polygon> polygons ; //list of all the polygons

int getClickedPolygon(int x, int y ){//returns the id of polygon which is clicked else -1 if none clicked
	for(int i= 0 ;i < polygons.size() ; i++){
		if(polygons[i].visible && x<= polygons[i].xmax && x>=polygons[i].xmin && y>= polygons[i].ymin && y<=polygons[i].ymax)
			return polygons[i].id ; 
	}
	return -1 ; 
}

void display(){
    glClearColor(1 , 1,1 , 1) ; 
	glClear(GL_COLOR_BUFFER_BIT) ; 
    for(int i= 0 ;i < polygons.size() ; i++){
        polygons[i].drawPolygon() ; 						
    }
	glFlush() ; 	
}

void reshape(int w, int h ){
	glViewport(0 , 0 , w , h) ; 
	glMatrixMode(GL_PROJECTION) ; 
	glLoadIdentity() ; 
	gluOrtho2D(0 , w , h , 0) ; 
	glMatrixMode(GL_MODELVIEW) ; 
	glLoadIdentity() ; 
}

void mymenu(int id) {
	switch(id){
		case 4 : exit(0) ; 
		case 1 : Polygon::newPolygonFlag = true ; break; 
        case 2 : Polygon::newPolygonFlag = false ;  //when user clicks end polygon , it constructs the polygon and puts it in the array.
                if(clickPoints.size()>0){ //check if user has done some clicks after selecting add option
                    polygons.push_back(Polygon(clickPoints, polygons.size())) ; //make a new Polygon using the clicked Points and add it to list
                    clickPoints.clear() ; 
                }
                break ;
        case 3 :  polygons[Polygon::selectedPolygon].setVisible(false) ; 
            break ; 
	}	
    glutPostRedisplay() ; 
}

void mouseHandler(int btn , int state , int x , int y ){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		int polygonSelected =  getClickedPolygon(x , y) ; 
        polygons[polygonSelected].setSelectedPolygon(polygonSelected) ; 
        if(Polygon::newPolygonFlag==true) { 
            Point p  = {x ,y} ; //add mouse point to clicked list
            clickPoints.push_back(p) ; 
        }
	}
    glutPostRedisplay() ; 
}

int main(int argc , char ** argv){
	glutInit(&argc , argv) ; 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ; 
    glutInitWindowSize(800 , 600) ; 
	glutCreateWindow("wind") ; 
	glutDisplayFunc(display) ;
	glutMouseFunc(mouseHandler) ;
    glutReshapeFunc(reshape) ; 
	glutCreateMenu(mymenu) ; 	
    glutAddMenuEntry("New Polygon", 1);
    glutAddMenuEntry("End Polygon",2);
    glutAddMenuEntry("Delete polygon", 3);
    glutAddMenuEntry("Quit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop() ; 
}
