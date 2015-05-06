#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <string>

#include "scene_graph.h"
#include "sphere.h"
#include "box.h"

using namespace std;

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

// Global variable for animation

double rot;
double deltaRot;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., -10.); // Posición inicial de la cámara
	
	// Intialize frame count
	frameCount = 0;
	oldTime = 0.0;
	fps = 0;

	// Animation
	rot = 0.;
	deltaRot = 0.0005;
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

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Model

	drawAxis(2.);

	// Building the Scene Graph

	Sphere *sun = new Sphere("The Sun");		// Create the root
	Box *temp = new Box("Temp");
	Sphere *earth = new Sphere("The Earth");
	earth->instanceScale(0.5, 0.5, 0.5);		// Scale instance to the proper size
	sun->addChild(earth);						// add to hierarchy
	Sphere *moon = new Sphere("The Moon");
	moon->instanceScale(0.15, 0.15, 0.15);		// Scale instance to the proper size
	earth->addChild(moon);						// add to hierarchy
	Sphere *sat = new Sphere("Voyager");
	sat->instanceScale(0.05, 0.05, 0.05);		// Scale instance to the proper size
	moon->addChild(sat);						// add to hierarchy
	Sphere *mars = new Sphere("Mars");
	mars->instanceScale(0.25, 0.25, 0.25);		// Scale instance to the proper size
	//sun->addChild(mars);						// add to hierarchy
	temp->instanceScale(0.5, 1, 1);
	sat->addChild(temp);
	SceneGraph *scene = new SceneGraph(sun);	// Add the root to the scene graph

												// Set relationships:
	earth->incrementalRotate(rot, 0., 1., 0.);	// Rotate the Earth and children respect the Sun
	earth->incrementalTranslate(3., 0., 0.);	// Locate the Earth from the Sun
	moon->incrementalRotate(rot, 0., 1., 0.);	// Rotate the Moon and children respect the Earth
	moon->incrementalTranslate(1.5, 0., 0.);	// Locate the Moon from the Earth
	sat->incrementalRotate(rot, 0., 1., 0.);	// Rotate the Sat and children respect the Moon
	sat->incrementalTranslate(.5, 0., 0.);		// Locate the Satellite from the Moon

	scene->draw();	// draw the scene graph!

	//End Model

	// For animation:
	rot = rot + deltaRot;
	if (rot > 360.)
	{
		rot = fmod(rot, 360.);
	}
	else
	{

	}
	string str = to_string(fps) + " fps";
	glutSetWindowTitle(str.c_str());

	glPopMatrix();

	glutSwapBuffers();	// Swap buffers
	delete scene;
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
	glutInitWindowSize(800, 600);
	glutCreateWindow("Scene Graph");
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
