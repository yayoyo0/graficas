#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>

#include "SOIL.h"

using namespace std;

// Global variables for window's size
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
double rotX = 0.;
double rotY = 0.;
double panX = 0.;
double panY = 0.;
double zoomZ = -6.;

// Global variable for texture
std::string textureFileName1;
std::string textureFileName2;
GLuint texID1;
GLuint texID2;
GLUquadric *quad;
float rot = 0.;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ); // Camera inicialization

	// Texture Initialization
	textureFileName1 = "earth.bmp";
	textureFileName2 = "moon.jpg";
	texID1 = SOIL_load_OGL_texture(
		textureFileName1.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);
	if (texID1 > 0)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID1);
		//glTexParameteri();
		quad = gluNewQuadric();
		gluQuadricTexture(quad, 1);
	}
	else
	{
		std::cout << "Texture File: " << textureFileName1 << " not found!" << std::endl;
	}


	texID2 = SOIL_load_OGL_texture(
		textureFileName2.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);
	if (texID2 > 0)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID2);
		quad = gluNewQuadric();
		gluQuadricTexture(quad, 1);
	}
	else
	{
		std::cout << "Texture File: " << textureFileName2 << " not found!" << std::endl;
	}
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (height == 0)
	{
		height = 1;
	}
	gluPerspective(25.0, (double)width / height, 0.1, 1000.0);	//proyección en perspectiva
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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Scene Model
	drawAxis(2.5);
	
	glEnable(GL_TEXTURE_2D);
	//Earth
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texID1);
		glRotatef(rot, 0., 1., 0.);
		gluSphere(quad, 2, 100, 100);
		//Moon
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texID2);
			glTranslatef(3.2,0.0,0.0);
			glRotatef(rot * 3, 0., 1., 0.);
			gluSphere(quad,0.5,100,100);
		glPopMatrix();
	glPopMatrix();

	
	glDisable(GL_TEXTURE_2D);
	//gluCylinder(quad,2,2,3,20,20);

	//End Scene Model
	
	rot = rot + 0.01;

	glPopMatrix();
	glutSwapBuffers();	// Swap buffers
}

void idle()
{
	glutPostRedisplay();    // call display
}

void mouse(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
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

void mouseMotion(int x, int y)
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
	// Init Window (GLUT)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Simple Texture");

	// Callback functions registration (GLUT)
	glutDisplayFunc(display);		// display scene functon
	glutReshapeFunc(reshape);		// reshape window function
	glutIdleFunc(idle);				// idle function
	glutMouseFunc(mouse);			// processing mouse events function
	glutMotionFunc(mouseMotion);	// processing mouse motion function

	init();							// init OpenGL context

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();					// Main loop waiting for events!
	return 0;
}