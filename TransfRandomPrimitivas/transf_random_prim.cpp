#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

// Global variable for FPS
int m;
int n;

int frameCount;
int fps;
double currentTime;
double oldTime;

// Global variables for moving camera
double x;
double y;
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

// Global variables for random numbers
int *arrRandom;
int size = 1.0;


void init()
{
	frameCount = 0;
	oldTime = 0.0;
	fps = 0;
	x = 0.0;
	y = 0.0;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., -10.); // Posición inicial de la cámara

	m = 4;	// Input
	n = 4;  // input
	arrRandom = new int[m * n];
	srand(time(NULL));
	for (int i = 0; i < m*n;  i++)
	{
		arrRandom[i] = rand() % 10;
	}
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

void drawRandomBuilding(int size, int index){
	for(int i = 1; i <= arrRandom[index]; i++){
		glutWireCube(size/2.0);
		glTranslatef(0, size/2.0, 0);
		glScalef(size - 0.1, size - 0.1, size - 0.1);
	}
}

void drawRandomApple(double size, int k)
{
	int k2 = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			glPushMatrix();
			glTranslatef(size * j, 0., size * i);
			switch (arrRandom[k])
			{
			case 0:
				drawRandomBuilding(size, k2);
				break;
			case 1:
				drawRandomBuilding(size, k2);
				break;
			case 2:
				drawRandomBuilding(size, k2);
				break;
			case 3:
				drawRandomBuilding(size, k2);
				break;
			case 4:
				drawRandomBuilding(size, k2);
				break;
			case 5:
				drawRandomBuilding(size, k2);
				break;
			}
			glPopMatrix();
			k2++;
		}
	}
}

void drawRandomCity(double size)
{
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			glPushMatrix();
			glTranslatef(size * j * m, 0., size * i* n);
			switch (arrRandom[k])
			{
			case 0:
				drawRandomApple(size, k);
				break;
			case 1:
				drawRandomApple(size, k);
				break;
			case 2:
				drawRandomApple(size, k);
				break;
			case 3:
				drawRandomApple(size, k);
				break;
			case 4:
				drawRandomApple(size, k);
				break;
			case 5:
				drawRandomApple(size, k);
				break;
			}
			k++;
			glPopMatrix();
		}
	}
}


void drawScene()
{
	int size = 1.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Model
	//drawAxis(1.0);
	//drawRandomBuilding(1.0, 1);
	//drawRandomApple(size,0);
	drawRandomCity(size);
	

		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
			glTranslatef(0.5 + x, 0.0 + y, 0.0);
			glutSolidCube(0.5);
		glPopMatrix();
		glColor3f(1.0, 1.0, 1.0);


	//End Model

	glPopMatrix();

	glutSwapBuffers();	// Swap buffers
}

void idle()
{
													// calculate FPS
	x++;									// Increase frame count
	currentTime = glutGet(GLUT_ELAPSED_TIME);		// Get the number of ms since glutInit called
	int timeInterval = currentTime - oldTime;		// Calculate time passed
	if (timeInterval > 1000)
	{
		fps = frameCount / (timeInterval / 1000.);	// Calculate fps
		oldTime = currentTime;						// Set time
		frameCount = 0;								// Reset frame count
		if(x <= x * m && y <= y * n)
		{
			x = x + 0.5;
			y = y + 0.5;
		}
		else
		{
		x = 0;
		}
		
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
	glutCreateWindow("City & Car");
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
