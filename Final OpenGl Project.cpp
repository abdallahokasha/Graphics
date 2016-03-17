#include <windows.h>
#include <gl\gl.h>
#include <gl\glut.h>
#include <math.h>
 
int i;
double angle = 0, angle2 = 0, angle3 = 0, angle4 = 0;
double sx = 0.5, sy = 0.5, sz = 0.5;
double tx = 0.25, ty = 0.25, tz = 0.25, xx, yy;
int doorFlag, windowsFlag, wheelFlag, flag = 1, RwheelFlag, LwheelFlag;
void Init()
{
	// Set Background Color
    glClearColor(0.0,1,0.0,0.0);
 
    // Enable 3D Rendering
    glEnable(GL_DEPTH_TEST);
}
// Mouse handling
void handleMouse(int mouse,int state,int x,int y)
{
     if(mouse == GLUT_LEFT_BUTTON)
     {
     	 puts("Left");
		 flag = 1;
		 glutPostRedisplay();
     }
     if(mouse == GLUT_RIGHT_BUTTON)
     {
		 flag = 0; 
		 puts("Right");
		 angle = 0;
		 glutPostRedisplay();
     }
}
// Keyboard handling
void handleKey(char key,int x,int y)
{    
 
     if(key == 'w')
     {
       angle += 3;
	   glutPostRedisplay();
     }
     else if(key == 's')
     {
      angle -= 3;
	  glutPostRedisplay(); 
     }
     if(key == 'q')
     {
       exit(0);
     }
     else if(key == 'o')
     {
       doorFlag = 1;
	   angle = 2;
       glutPostRedisplay();
     }
     else if(key == 'c')
     {
       doorFlag = 0;
	   angle = 2;
       glutPostRedisplay();
     }
     else if(key == 'O')
     {
       windowsFlag = 1;
       angle3 += 2;
       glutPostRedisplay();
     }
     else if(key == 'C')
     {
       windowsFlag = 0;
       angle3 -= 2;
       glutPostRedisplay();
     }
     else if(key == 'b')
     {
       puts("b");
        wheelFlag = 1;
		angle2 -= 5;
       glutPostRedisplay();
     }
      else if(key == 'r')
     {
     	puts("r");
        wheelFlag = 1;
		angle4 += 5;
       glutPostRedisplay();
     }
      else if(key == 'f')
     {
     	puts("f");
        wheelFlag = 1;
		angle2 += 5;
       glutPostRedisplay();
     }
     else if(key == 'l')
     {
     	puts("L");
        LwheelFlag = 1;
		 angle2 += 5;
       glutPostRedisplay();
     }
      else if(key == '+')
     {
            sx += 0.1;
            sy += 0.1;
            sz += 0.1;
            glutPostRedisplay();
     }
     else if(key == '-')
     {
            sx -= 0.1;
            sy -= 0.1;
            sz -= 0.1;
            glutPostRedisplay();
     }
}
// Drawing function
void drawWindows(){	
    
	glPushMatrix();
    
	glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.2,0.2,-0.51);
        glVertex3f(0.2, 0.4,-0.51);
        glVertex3f(0.4, 0.4,-0.51);
        glVertex3f(0.4,0.2,-0.51);
    glEnd();
 
	glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2,0.2,-0.51);
        glVertex3f(-0.2, 0.4,-0.51);
        glVertex3f(-0.4, 0.4,-0.51);
        glVertex3f(-0.4,0.2,-0.51);
    glEnd();
 
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2, -0.1, -0.51);
        glVertex3f(-0.2, -0.3, -0.51);
        glVertex3f(-0.4, -0.3, -0.51);
        glVertex3f(-0.4, -0.1, -0.51);
    glEnd();
 
      glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.2, -0.1, -0.51);
        glVertex3f(0.2, -0.3, -0.51);
        glVertex3f(0.4, -0.3, -0.51);
        glVertex3f(0.4, -0.1, -0.51);
    glEnd();
    
    glPopMatrix();
}
/* Draw & Rotate Windows*/
void r_drawWindows(){
        //glLoadIdentity();
        glPushMatrix();
		glRotatef(angle3,0,1,0);
		
	glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.2,0.2,-0.51);
        glVertex3f(0.2, 0.4,-0.51);
        glVertex3f(0.4, 0.4,-0.51);
        glVertex3f(0.4,0.2,-0.51);
    glEnd();
 
	glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2,0.2,-0.51);
        glVertex3f(-0.2, 0.4,-0.51);
        glVertex3f(-0.4, 0.4,-0.51);
        glVertex3f(-0.4,0.2,-0.51);
    glEnd();
 
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.2, -0.1, -0.51);
        glVertex3f(-0.2, -0.3, -0.51);
        glVertex3f(-0.4, -0.3, -0.51);
        glVertex3f(-0.4, -0.1, -0.51);
    glEnd();
 
      glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.2, -0.1, -0.51);
        glVertex3f(0.2, -0.3, -0.51);
        glVertex3f(0.4, -0.3, -0.51);
        glVertex3f(0.4, -0.1, -0.51);
    glEnd();
    
    glPopMatrix();
	
}
/* Draw Roof - 4 Triangles */
void drawTriangles(){
	glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, 0.5,0.5);
        glVertex3f( 0,1,-0.5);
        glVertex3f( 0.5, 0.5,0.5);
    glEnd();
 
   	glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, 0.5,-0.5);
        glVertex3f( 0,1,-0.5);
        glVertex3f( -0.5, 0.5,-0.5);
    glEnd();
 
	glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.5,-0.5);
        glVertex3f(0, 1, -0.5);
        glVertex3f(0.5, 0.5,-0.5);
    glEnd(); 
 
     glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, 0.5,-0.5);
        glVertex3f( 0,1,-0.5);
        glVertex3f( 0.5, 0.5,-0.5);
    glEnd();
}
/* Draw Sides */
void drawSides(){
	 glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5, 0.5,-0.5);  
	glVertex3f(-0.5, 0.5,0.5);
	glVertex3f(-0.5,-0.5,0.5);
	glEnd();
 
	  glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f( 0.5,-0.5,-0.5);
    glVertex3f( 0.5, 0.5,-0.5);
    glVertex3f( 0.5, 0.5,0.5);
    glVertex3f( 0.5,-0.5,0.5);
	glEnd();
}
/* Draw Door */
void drawDoor(){
	glPushMatrix();
      glColor3f(0,0,0);
	  glColor3f(0.7, 0.5, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.1, -0.5, -0.51);
        glVertex3f(-0.1, -0.2, -0.51);
        glVertex3f( 0.1, -0.2, -0.51);
        glVertex3f( 0.1, -0.5, -0.51);
    glEnd();
    glPushMatrix();
}
/* Draw & Rotate Door */
void r_drawDoor(){
	glPushMatrix();
	glColor3f(0,0,0);
	glRotatef(angle,0,1,0);
	
	   glColor3f(0.7, 0.5, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.1, -0.5, -0.51);
        glVertex3f(-0.1, -0.2, -0.51);
        glVertex3f( 0.1, -0.2, -0.51);
        glVertex3f( 0.1, -0.5, -0.51);
    glEnd();
    glPopMatrix();
}
void drawBasics(){
	 /* front 1 */ 
       glColor3f(1,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5, 0.5,-0.5);
        glVertex3f( 0.5, 0.5,-0.5);
        glVertex3f( 0.5,-0.5,-0.5);
    glEnd();
    /* Front 2  */
    glColor3f(1, 0, 1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5, 0.5,0.5);
        glVertex3f( 0.5, 0.5,0.5);
        glVertex3f( 0.5,-0.5,0.5);
    glEnd();
    /* Right basic side */
    glColor3f(0.7, 0.4, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f( 0.5, -0.5, 0.5);
        glVertex3f( 0.5, -0.5, -0.5);
    glEnd();
 
    glColor3f(.8, .2, .1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f( 0.5, 0.5, 0.5);
        glVertex3f( 0.5, 0.5, -0.5);
    glEnd();
}
void r_rightWheel(){
    
	glPushMatrix();	
	glTranslatef(-xx, -yy, -0.52);
	glRotatef(angle4, 1, 0, 0);
	glTranslatef(xx, yy, 0.52);
	glBegin(GL_LINE_LOOP);
	for(i =0; i <= 30; i++){
	double angle = 2 * 3.14159265 * i / 30;
	double x = (cos(angle)/12)-0.5;
	double y = (sin(angle)/12)-0.9;
	glColor3f(0,0,0);
	glVertex3d(x,y,-0.52);
	}
	glEnd();
    glPopMatrix();
}
void Display()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    int camera[3] = {0, 1, 0};// = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};
 	/* rotate in x & y direction */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluLookAt(0.5, .5, 0.5, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 0, 1, 0);
	glCallList(Display);
	glRotatef(angle,1,1,0);
	glTranslatef(tx,ty,tz);
	glScalef(sx,sy,sz);
    
    /* House Basic sides */
	drawBasics();
    /* 4 triangles */
    drawTriangles();
    /* sides */
      drawSides();
	/* door */
	if(doorFlag == 1){
	   r_drawDoor();
	}
	else{
    drawDoor();   
	}
	/* 4 windows */
	if (windowsFlag == 1){
	r_drawWindows();
	}
	else{
	drawWindows();
	}
	/* draw Bicycle*/
	 
	 if(flag == 1){
			 angle2 += 2;
			 glutPostRedisplay();
	}
	
	if(wheelFlag == 1 || flag){
		glRotatef(angle2, 0, 0, 1);
	}
	//glPushMatrix();
	/* Right Wheel */
	
	xx = (cos(angle)/12)-0.5;
    yy = (sin(angle)/12)-0.9;
	
	if (RwheelFlag == 1){
		r_rightWheel();
	}
	if (LwheelFlag == 1){
		glTranslatef(-tx, -ty, -0.52);
		glRotatef(- angle4, 0, 1, 1);
		glTranslatef(tx, ty, 0.52);
		
	}
	glBegin(GL_LINE_LOOP);
	for(i =0; i <= 30; i++){
	double angle = 2 * 3.14159265 * i / 30;
	double x = (cos(angle)/12)-0.5;
	double y = (sin(angle)/12)-0.9;
	glColor3f(0,0,0);
	glVertex3d(x,y,-0.52);
	}
	glEnd();
    
    /*  left Wheel */
	glBegin(GL_LINE_LOOP);
	for(i =0; i <= 30; i++){
	double angle = 2 * 3.14159265 * i / 30;
	double x = (cos(angle)/12)-0.8;
	double y = (sin(angle)/12)-0.9;
	glColor3f(0,0,0);
	glVertex3d(x,y,-0.52);
	}
	glEnd();
	
	/* Line between Wheels */
	double angle = 2 * 3.14159265;
	double x = (cos(angle)/12)-0.8;
	double y = (sin(angle)/12)-0.9;
    /* Line */
	glLineWidth(3.5); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(x, y, -0.52);
	glVertex3f(x+0.135, y, -0.52);
	glEnd();
	glPopMatrix();
    /* Bicycle done! */
	glFlush();
}
// Main function
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("My House");
 
	glutDisplayFunc(Display);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKey);
 
	Init();
	glutMainLoop();
}