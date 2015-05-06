#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Global variables for object's rotation
double rot;
double deltaRot;

// Global variable for FPS
int frameCount;
int fps;
double currentTime;
double oldTime;


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

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., -10.); // Posición inicial de la cámara
	// Initialize object's rotation
	rot = 0.0;
	deltaRot = 0.01;
	// Intialize frame count
	frameCount = 0;
	oldTime = 0.0;
	fps = 0;
}

void drawAxis(double length)
{
	glColor3f(1., 0., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(length, 0., 0.);
	glEnd();
	glColor3f(0., 1., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., length, 0.);
	glEnd();
	glColor3f(0., 0., 1.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., length);
	glEnd();
	glColor3f(1., 1., 1.);
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

void drawSolarSystem()
{
	glPushMatrix();
		//Sun
		glPushMatrix();
		glRotatef(rot, 0.0, 1.0, 0.0);
			glutWireSphere(1.0, 20, 20);
		glPopMatrix();
		{
			glRotatef(rot, 0.0, 1.0, 0.0);
			//Earth
			glTranslated(5.0, 0.0, 0.0);
			glPushMatrix();
				glRotatef(rot, 0.0, 1.0, 0.0);
				glutWireSphere(0.3, 20, 20);
			glPopMatrix();
			{
				glRotatef(rot, 0.0, 1.0, 0.0);
				//Moon
				glTranslatef(1.0, 0.0, 0.0);
				glutWireSphere(0.1, 20, 20);
				{
					glRotatef(rot, 0.0, 1.0, 0.0);
					//Satelite
					glTranslatef(0.2, 0.0, 0.0);
					glutWireSphere(0.01, 20, 20);
				}
			}
		}
	glPopMatrix();
}
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Model
	drawAxis(2.0);
	drawSolarSystem();

	//End Model

	rot = rot + deltaRot;
	if (rot > 360.)
	{
		rot = fmod(rot, 360.);
	}

	string str = to_string(fps) + " fps";
	glutSetWindowTitle(str.c_str());

	glPopMatrix();

	glutSwapBuffers();	// Swap buffers
}

void idle()
{
													// calculate FPS
	frameCount++;									// Increase frame count
	currentTime = glutGet(GLUT_ELAPSED_TIME);		// Get the number of ms since glutInit called
	int timeInterval = currentTime - oldTime;		// Calculate time passed
	if (timeInterval > 1000)
	{
		fps = frameCount / (timeInterval / 1000.);	// Calculate fps
		oldTime = currentTime;						// Set time
		frameCount = 0;								// Reset frame count
	}
	else
	{

	}
	glutPostRedisplay();							// Call display function (draw the current frame)
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
	glutInitWindowSize(800, 800);
	glutCreateWindow("Sistema Solar");
	init();			// OpenGL initialization code
	// Callback functions registration 
	glutReshapeFunc(reshapeViewport);
	glutDisplayFunc(drawScene);
	glutIdleFunc(idle);
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
