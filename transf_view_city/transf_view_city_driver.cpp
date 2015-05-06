#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "car_gl.h"
#include "grid_gl.h"

using namespace std;

// Global variables for camera movement
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

// Global variable for FPS
int frameCount = 0;
int fps = 0;
double currentTime = 0.;
double oldTime = 0.;

// Global variables for car's translation
CarGL *car;
GridGL *grid;
double rot = 0.;
double tX = 0.;
double tY = 0.;
double tZ = 0.;
double deltaT = 0.01;
double deltaRot = 0.01;

// Global variables for random generation
int m = 3;					// Number of rows (buildings in a block and blocks in a city)
int n = 3;					// Number of columns (buildings in a block and blocks in a city)
int minNumFloors = 1;
int maxNumFloors = 10;
double offsetSize = 10.;// Reducción de los pisos superiores. Default: 10
double size = 1.;		// Building's parameter
int **arrNumFloors;		// Matrix (m x n) of (random) floors in a block
int ****arrBlocks;		// Matrix (m x n) of blocks (each element is a matrix of number of floors) in a city

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ); // Posición inicial de la cámara
	glEnable(GL_CULL_FACE);

	srand(time(NULL));
	arrBlocks = new int ***[m];
	for (int i = 0; i < m; i++)
	{
		arrBlocks[i] = new int **[n];
	}
	int numRandom;
	for (int k = 0; k < m; k++)
	{
		for (int l = 0; l < n; l++)
		{
			arrNumFloors = new int *[m];
			for (int i = 0; i < m; i++)
			{
				arrNumFloors[i] = new int[n];
			}
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					numRandom = rand() % maxNumFloors + minNumFloors;
					if (numRandom >(maxNumFloors / 2 + 1))
					{
						arrNumFloors[i][j] = rand() % maxNumFloors + minNumFloors;
					}
					else
					{
						arrNumFloors[i][j] = numRandom;
					}
				}
			}
			arrBlocks[k][l] = arrNumFloors;
		}
	}
	grid = new GridGL(m, n, size);
	car = new CarGL(size/3.0);
	car->addGrid(grid);
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

void drawFace(double size)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0., 0., 0.);
	glVertex3f(size, 0., 0.);
	glVertex3f(size, size, 0.);
	glVertex3f(0., size, 0.);
	glEnd();
}

void drawCube(double size)
{
	glCullFace(GL_BACK);
	glPushMatrix();
	glTranslatef(-size / 2., -size / 2., -size / 2.);
	// front face
	glPushMatrix();
	glTranslatef(0., 0., size);
	drawFace(size);
	glPopMatrix();
	// back face
	glPushMatrix();
	glTranslatef(size, 0., 0.);
	glRotatef(180., 0., 1., 0.);
	drawFace(size);
	glPopMatrix();
	// left & right faces
	glPushMatrix();
	// left face
	glRotatef(-90., 0., 1., 0.);
	drawFace(size);
	glPopMatrix();
	// right face
	glPushMatrix();
	glTranslatef(0., 0., size);
	glTranslatef(size, 0., 0.);
	glRotatef(90., 0., 1., 0.);
	drawFace(size);
	glPopMatrix();

	// Bottom face
	glPushMatrix();
	glRotatef(90., 1., 0., 0.);
	drawFace(size);
	glPopMatrix();
	// Upper face
	glPushMatrix();
	glTranslatef(0., size, 0.);
	glTranslatef(0., 0., size);
	glRotatef(-90., 1., 0., 0.);
	drawFace(size);
	glPopMatrix();
	glPopMatrix();
}

void drawBox(double length, double width, double height)
{
	glPushMatrix();
	glScalef(length, width, height);
	drawCube(1.0);
	glPopMatrix();
}

void drawBuilding(int numFloors, double size)
{
	double height = 2. * size;
	double minHeight = size / 2.;
	double acumSize = 0.;
	for (int i = 1; i <= numFloors; i++)
	{
		glPushMatrix();
		glTranslatef(0., acumSize + height / 2., 0.);
		drawBox(size, height, size);
		glPopMatrix();
		acumSize = acumSize + height;
		size = size - size / offsetSize;
		if (height > minHeight)
		{
			height = height - height / offsetSize;
		}
		else
		{

		}
	}
}

void drawBlock(int m, int n, int i, int j, double size)
{
	glPushMatrix();
	for (int k = 0; k < m; k++)
	{
		for (int l = 0; l < n; l++)
		{
			glPushMatrix();
			glTranslatef(size * l, 0., size * k);
			drawBuilding(arrBlocks[k][l][i][j], size);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawCity(int m, int n, double size)
{
	glPushMatrix();
	glTranslatef(size, 0., size);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			glPushMatrix();
			glTranslatef((n + 1) * size * j, 0., (m + 1) * size * i);
			drawBlock(m, n, i, j, size);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawStreetNodes()
{
	double x;
	double z = 0.;
	Point ***e = new Point **[m + 1];
	for (int i = 0; i <= m; i++)
	{
		e[i] = new Point *[n + 1];
	}
	for (int i = 0; i <= m; i++)
	{
		x = 0.;
		z = (m * size + size) * i;
		for (int j = 0; j <= n; j++)
		{
			x = (n * size + size) * j;
			e[i][j] = new Point(x, 0., z);
		}
	}
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			glPushMatrix();
			glTranslatef(e[i][j]->x, 0., e[i][j]->z);
			glutSolidSphere(size / 10., 10, 10);
			glPopMatrix();
		}
	}
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	gluLookAt(0,10,10,car->loc->x,car->loc->y,car->loc->z,0,1,0); //Vista aerea
	//gluLookAt(car->loc->x, car->loc->y, car->loc->z, car->grid->e[car->iTo][car->jTo]->x,car->grid->e[car->iTo][car->jTo]->y,car->grid->e[car->iTo][car->jTo]->z,0,1,0); Vista adentro del coche
	//gluLookAt(1+car->loc->x, 1+car->loc->y, 1+car->loc->z, car->grid->e[car->iTo][car->jTo]->x,car->grid->e[car->iTo][car->jTo]->y,car->grid->e[car->iTo][car->jTo]->z,0,1,0); Vista afuera del coche

	// Model
	drawAxis(10.);
	drawCity(m, n, size);
	grid->draw();
	car->animate();
	car->draw();
	// End Model


	rot = rot + deltaRot;

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
	glutCreateWindow("gluLookAt");
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
