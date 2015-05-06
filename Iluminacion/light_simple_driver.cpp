// Iluminación de ambiente : default en OpenGL
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

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

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ); // Camera inicialization

	// 1. Enabling the lights, but none light sources is enabled, just ambient illumination
	glEnable(GL_LIGHTING); // So lighting models are used

	// 2. Specifying the shading model
	glShadeModel(GL_SMOOTH); // The default in OpenGL, try with GL_FLAT

	// 4. Defining the lights
	// 4.1 The color of the light sources
	// 4.2 The light position(not apply for ambient illumination)
	// 4.3 The ambient light
	float ambient_light[] = { 1., 1., 1., 1.0 }; // White color
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	// 5. Defining the material properties for SILVER(see table properties for GOLD material)
	float ambient_mat[] = { 0.19225, 0.19225, 0.19225, 1. };
	float diffuse_mat[] = { 0.50754, 0.50754, 0.50754, 1. };
	float specular_mat[] = { 0.508273, 0.508273, 0.508273, 1. };
	float shininess_mat[] = { 128 * .4 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess_mat);
	glDisable(GL_LIGHTING);
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

void drawCube()
{
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	// 3. Defining Normals to surfaces
	// Front
	glBegin(GL_QUADS);
	glNormal3f(0., 0., 1.);
	glVertex3f(0., 0., 1.);
	glNormal3f(0., 0., 1.);
	glVertex3f(1., 0., 1.);
	glNormal3f(0., 0., 1.);
	glVertex3f(1., 1., 1.);
	glNormal3f(0., 0., 1.);
	glVertex3f(0., 1., 1.);
	glEnd();
		// Back
	glBegin(GL_QUADS);
	glNormal3f(0., 0., -1.);
	glVertex3f(0., 0., 0.);
	glNormal3f(0., 0., -1.);
	glVertex3f(0., 1., 0.);
	glNormal3f(0., 0., -1.);
	glVertex3f(1., 1., 0.);
	glNormal3f(0., 0., -1.);
	glVertex3f(1., 0., 0.);
	glEnd();
		//Bottom
	glBegin(GL_QUADS);
	glNormal3f(0., -1., 0.);
	glVertex3f(0., 0., 0.);
	glNormal3f(0., -1., 0.);
	glVertex3f(1., 0., 0.);
	glNormal3f(0., -1., 0.);
	glVertex3f(1., 0., 1.);
	glNormal3f(0., -1., 0.);
	glVertex3f(0., 0., 1.);
	glEnd();
		//Top
	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0.);
	glVertex3f(0., 1., 0.);
	glNormal3f(0., 1., 0.);
	glVertex3f(0., 1., 1.);
	glNormal3f(0., 1., 0.);
	glVertex3f(1., 1., 1.);
	glNormal3f(0., 1., 0.);
	glVertex3f(1., 1., 0.);
	glEnd();
	//Left
	glBegin(GL_QUADS);
	glNormal3f(-1., 0., 0.);
	glVertex3f(0., 0., 0.);
	glNormal3f(-1., 0., 0.);
	glVertex3f(0., 0., 1.);
	glNormal3f(-1., 0., 0.);
	glVertex3f(0., 1., 1.);
	glNormal3f(-1., 0., 0.);
	glVertex3f(0., 1., 0.);
	glEnd();
	// Right
	glBegin(GL_QUADS);
	glNormal3f(1., 0., 0.);
	glVertex3f(1., 0., 0.);
	glNormal3f(1., 0., 0.);
	glVertex3f(1., 1., 0.);
	glNormal3f(1., 0., 0.);
	glVertex3f(1., 1., 1.);
	glNormal3f(1., 0., 0.);
	glVertex3f(1., 0., 1.);
	glEnd();
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
	drawAxis(2.);       // Drawing global coordinate system

	glEnable(GL_LIGHTING);
	drawCube();
	glDisable(GL_LIGHTING);
	
	//End Scene Model

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
	glutCreateWindow("3D Viewer");

	// Callback functions registration (GLUT)
	glutDisplayFunc(display);		// display scene function
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
