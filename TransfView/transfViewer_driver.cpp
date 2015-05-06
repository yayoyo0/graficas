#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

//window size
int width = 800;
int height = 600;

// Global variables for moving camera
int mouseButton = 0;
bool mouseRotate = false;
bool mouseZoom = false;
bool mousePan = false;
int xClick = 0;
int yClick = 0;
int xAux = 0;
int yAux = 0;
double rotX = 0.0;
double rotY = 0.0;
double panX = 0.0;
double panY = 0.0;
double zoomZ = 0.0;
bool setCam = false;
bool viewports = false;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -8.0); // Posición inicial de la cámara

}

void drawAxis(double length){

	glColor3f(1.,0.,0.);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(length,0.0,0.0);
	glEnd();

		glColor3f(0.,1.,0.);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.,length,0.0);
	glEnd();

		glColor3f(0.,0.,1.);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,length);
	glEnd();

	glColor3f(1.0,1.0,1.0);

}

void reshapeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (height == 0)
	{
		height = 1;
	}
	gluPerspective(25.0, width / height, 0.1, 1000.0);	//proyección en perspectiva
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y){
	//printf("%i",key);
	if(key == 32){
		viewports =!viewports;
	}
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	if(viewports){
		//Viewport1
		glViewport(0, 0, width, height);
		glPushMatrix();
			glTranslatef(panX, panY, zoomZ);
			glRotatef(rotY, 1.0, 0.0, 0.0);
			glRotatef(rotX, 0.0, 1.0, 0.0);
			glutWireTeapot(1.0);
			drawAxis(1.5);
		glPopMatrix();
	}else{
	//Viewport1
	glViewport(width/2, height/2, width/2, height/2);
	glPushMatrix();
		glTranslatef(panX, panY, zoomZ);
		glRotatef(rotY, 1.0, 0.0, 0.0);
		glRotatef(rotX, 0.0, 1.0, 0.0);
		glutWireTeapot(1.0);
		drawAxis(1.5);
	glPopMatrix();
	//Viewport2
	glViewport(0, height/2, width/2, height/2);
	glPushMatrix();
		glTranslatef(panX, panY, zoomZ);
		glRotatef(-90,0.0,1.0,0.0);
		glutWireTeapot(1.0);
		drawAxis(1.5);
	glPopMatrix();
	//Viewport3
	glViewport(0, 0, width/2, height/2);
	glPushMatrix();
		glTranslatef(panX, panY, zoomZ);
		glutWireTeapot(1.0);
		drawAxis(1.5);
	glPopMatrix();
	//Viewport4
	glViewport(width/2, 0, width/2, height/2);
	glPushMatrix();
		glTranslatef(panX, panY, zoomZ);
		glRotatef(90, 1.0, 0.0, 0.0);
		glutWireTeapot(1.0);
		drawAxis(1.5);
	glPopMatrix();
	
	}
	glPopMatrix();

	glutSwapBuffers();	// Swap buffers
}

void mouseEvents(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
	//mouseRotate = true;
	mouseZoom = false;
	mousePan = false;
	xClick = x;
	yClick = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux = rotX;
		yAux = rotY;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		mouseZoom = true;
		xAux = zoomZ;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;	
		xAux = panX;
		yAux = panY;
	}
}

void mouseMotionEvents(int x, int y)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick + xAux) > 360.0)
			{
				xAux = xAux - 360.0;
			}
			if ((x - xClick + xAux) < 0.0)
			{
				xAux = xAux + 360.0;
			}
			if ((y - yClick + yAux) > 360.0)
			{
				yAux = yAux - 360.0;
			}
			if ((y - yClick + yAux) < 0.0)
			{
				yAux = yAux + 360.0;
			}
			rotX = x - xClick + xAux;
			rotY = y - yClick + yAux;
		}
	}
	else if (mouseZoom == true)
	{
		if (mouseButton == GLUT_RIGHT_BUTTON)
		{
			zoomZ = ((x - xClick) / 10.0) + xAux;
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX = ((x - xClick) / 63.0) + xAux;
			panY = ((y - yClick) / (-63.0)) + yAux;
		}
	}
}

int main(int argc, char** argv)
{
					// GLUT Initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Viewports Transformation");
	init();			// OpenGL initialization code
					// Callback functions registration 
	glutReshapeFunc(reshapeViewport);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutMouseFunc(mouseEvents);
	glutMotionFunc(mouseMotionEvents);
	glutKeyboardFunc(processNormalKeys);
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
					// Waiting for events
	glutMainLoop();
	return 0;
}
