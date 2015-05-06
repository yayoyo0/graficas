#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

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

void drawFace(double size){
	glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(size,0.0,0.0);
		glVertex3f(size,size,0.0);
		glVertex3f(0.0,size,0.0);
	glEnd();
}

void drawCube(double size){

	glPolygonMode(GL_FRONT,GL_LINE);
	//Frente
	glPushMatrix();
		glTranslatef(0.0, 0.0, size);
		drawFace(size);
	glPopMatrix();
	//FinFrente

	//Atras
	glPushMatrix();
		glTranslatef(size, 0.0, 0);
		glRotatef(180,0.0,size,0.0);
		drawFace(size);
	glPopMatrix();
	//FinAtras

	//Izquierdo
	glPushMatrix();
		//glTranslatef(size, 0.0, 0);
		glRotatef(-90.0,0.0,size,0.0);
		drawFace(size);
	glPopMatrix();
	//FinIzquierdo

	//Derecho
	glPushMatrix();
		glTranslatef(size, 0.0, 0);
		glRotatef(90.0,0.0,size,0.0);
		glTranslatef(-size, 0.0, 0.0);
		drawFace(size);
	glPopMatrix();
	//FinDerecho

	//Fondo
	glPushMatrix();
		glRotatef(90.0,size,0.0,0.0);
		drawFace(size);
	glPopMatrix();
	//FinFondo

	//Techo
	glPushMatrix();
		glRotatef(90.0,-size,0.0,0.0);
		glTranslatef(0.0, -size, size);
		drawFace(size);
	glPopMatrix();
	//FinTecho

}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., 0.0); // Posición inicial de la cámara
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

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	drawAxis(2.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	drawCube(1.0);


	//glutWireTeapot(0.5);	// Model

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
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Viewer");
	init();			// OpenGL initialization code
					// Callback functions registration 
	glutReshapeFunc(reshapeViewport);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutMouseFunc(mouseEvents);
	glutMotionFunc(mouseMotionEvents);

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
