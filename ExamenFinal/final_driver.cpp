#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>

#include "scene_graph.h"
#include "sphere.h"
#include "box.h"
#include "Root.h"
#include "Cone.h"
#include "Cilinder.h"
#include "Octahedron.h"
#include "Dodecahedron.h"
#include "Torus.h"

using namespace std;

const int MAX = 10;
int objetosActual = 0;
int width = 800;
int height = 600;
int mainWindow;
int subWindow0;
int subWindow1;
int mouseButton = 0;
bool mouseRotate = false;
bool mouseZoom = false;
bool mousePan = false;
int xClick[4] = { 0, 0, 0, 0 };
int yClick[4] = { 0, 0, 0, 0 };
int xAux[4] = { 0, 0, 0, 0 };
int yAux[4] = { 0, 0, 0, 0 };
double rotX[4] = { 0., 0., 0., 0. };
double rotY[4] = { 0., 0., 0., 0. };
double panX[4] = { 0., 0., 0., 0. };
double panY[4] = { 0., 0., 0., 0. };
double zoomZ[4] = { -6., -6., -6., -6. };
double translate[10][2];
double color[10][3];
int shape = 99;
double xD1;
double yD1;

Root *raiz = new Root();
SceneGraph *scene = new SceneGraph(raiz);

bool add;
SceneNode *arreglo[MAX];
int index = 0;


void init0()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ[0]); // Camera inicialization
}

void init1()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ[1]); // Camera inicialization
	xD1 = 0;
	yD1 = 0;
}

void reshape(int w, int h)
{
	glutReshapeWindow(width, height);
}

void reshape0(int w, int h)
{
	glutSetWindow(subWindow0);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
	{
		h = 1;
	}
	gluPerspective(25.0, (double)w / h, 0.1, 1000.0);	//proyección en perspectiva
	glMatrixMode(GL_MODELVIEW);
}

void reshape1(int w, int h)
{
	glutSetWindow(subWindow1);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
	{
		h = 1;
	}
	gluPerspective(25.0, (double)w / h, 0.1, 1000.0);	//proyección en perspectiva
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

void display0()
{
	glutSetWindow(subWindow0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX[0], panY[0], zoomZ[0]);
	glRotatef(rotY[0], 1.0, 0.0, 0.0);
	glRotatef(rotX[0], 0.0, 1.0, 0.0);

	// Scene Model
	glPushMatrix();						//Sphere
		glTranslatef(0, 2.3, 0);
		glutWireSphere(0.2, 20, 20);
	glPopMatrix();
	glPushMatrix();						//Cube
		glTranslatef(0, 1.7, 0);
		glutWireCube(0.3);
	glPopMatrix();
	glPushMatrix();						//Cone
		glTranslatef(0, 1.3, 0);
		glRotatef(90, 1, 0, 0);
		glutWireCone(0.2, 0.5, 20, 20);
	glPopMatrix();						//Cylinder
	glPushMatrix();
		glTranslatef(0, 0.6, 0);
		glRotatef(90, 1, 0, 0);
		glutWireCylinder(0.2, 0.4, 20, 20);
	glPopMatrix();
	glPushMatrix();						//Octahedron
		glTranslatef(0, -0.2 , 0);
		glScalef(0.2, 0.2, 0.2);
		glutWireOctahedron();
	glPopMatrix();
	glPushMatrix();						//Dodecahedron
		glTranslatef(0, -0.8 , 0);
		glScalef(0.1, 0.1, 0.1);
		glutWireDodecahedron();
	glPopMatrix();
	glPushMatrix();						//Torus
		glTranslatef(0, -1.5 , 0);
		glutWireTorus(0.1, 0.2, 20, 20);
	glPopMatrix();
	//End Scene Model

	glPopMatrix();
	
	glutSwapBuffers();	// Swap buffers
}

void display1()
{
	glutSetWindow(subWindow1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	// Scene Model

	if(shape == 0){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Sphere *temp0 = new Sphere("Esfera");
		temp0->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp0->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp0->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp0->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp0);
		temp->draw();

		if(add){
			raiz->addChild(temp0);
			add = false;
		}
	}
	if(shape == 1){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Box *temp1 = new Box("Caja");
		temp1->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp1->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp1->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp1->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp1);
		temp->draw();
		if(add){
			raiz->addChild(temp1);
			add = false;
		}
	}
	if(shape == 2){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Cone *temp2 = new Cone("Cono");
		temp2->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp2->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp2->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp2->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp2);
		temp->draw();
		if(add){
			raiz->addChild(temp2);
			add = false;
		}
	}
	if(shape == 3){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Cilinder *temp3 = new Cilinder("Cilindro");
		temp3->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp3->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp3->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp3->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp3);
		temp->draw();
		if(add){
			raiz->addChild(temp3);
			add = false;
		}
	}
	if(shape == 4){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Octahedron *temp4 = new Octahedron("Octaedro");
		temp4->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp4->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp4->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp4->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp4);
		temp->draw();
		if(add){
			raiz->addChild(temp4);
			add = false;
		}
	}
	if(shape == 5){
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		Dodecahedron *temp5 = new Dodecahedron("Dodecaedro");
		temp5->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp5->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp5->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp5->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp5);
		temp->draw();
		if(add){
			raiz->addChild(temp5);
			add = false;
		}
	}
	if(shape == 6){
		Torus *temp6 = new Torus("Toroide");
		glColor3f(color[shape][0], color[shape][1], color[shape][2]);
		temp6->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		temp6->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		temp6->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		temp6->instanceTranslate(translate[shape][0], translate[shape][1], 0);
		SceneGraph *temp = new SceneGraph(temp6);
		temp->draw();
		if(add){
			raiz->addChild(temp6);
			add = false;
		}
	}
	//End Scene Model

	scene -> draw();

	glPopMatrix();
	glutSwapBuffers();	// Swap buffers
}

void display()
{
	display0();
	display1();
}

void idle()
{
	glutPostRedisplay();    // call display
}

void mouse(int button, int state, int x, int y, int i)
{
	mouseButton = button;
	mouseRotate = false;
	mouseZoom = false;
	mousePan = false;
	xClick[i] = x;
	yClick[i] = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux[i] = rotX[i];
		yAux[i] = rotY[i];
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		mouseZoom = true;
		xAux[i] = zoomZ[i];
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;
		xAux[i] = panX[i];
		yAux[i] = panY[i];
	}
}

void mouse0(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if(x < 100 && y <= 70){
			shape = 0;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);

		}
		if(x < 100 && y > 70 && y <= 140){
			shape = 1;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
		if(x < 100 && y > 140 && y <= 215){
			shape = 2;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
		if(x < 100 && y > 215 && y <= 290){
			shape = 3;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
		if(x < 100 && y > 290 && y <= 355){
			shape = 4;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
		if(x < 100 && y > 355 && y <= 420){
			shape = 5;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
		if(x < 100 && y >420){
			shape = 6;
			glutSetWindow(subWindow1);
			glutPostRedisplay();
			glutSetWindow(subWindow0);
		}
	}

}

void mouse1(int button, int state, int x, int y)
{
	mouse(button, state, x, y, 1);
}

void mouseMotion(int x, int y, int i)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick[i] + xAux[i]) > 360.0)
			{
				xAux[i] = xAux[i] - 360.0;
			}
			if ((x - xClick[i] + xAux[i]) < 0.0)
			{
				xAux[i] = xAux[i] + 360.0;
			}
			if ((y - yClick[i] + yAux[i]) > 360.0)
			{
				yAux[i] = yAux[i] - 360.0;
			}
			if ((y - yClick[i] + yAux[i]) < 0.0)
			{
				yAux[i] = yAux[i] + 360.0;
			}
			rotX[i] = x - xClick[i] + xAux[i];
			rotY[i] = y - yClick[i] + yAux[i];
		}
	}
	else if (mouseZoom == true)
	{
		if (mouseButton == GLUT_RIGHT_BUTTON)
		{
			zoomZ[i] = ((x - xClick[i]) / 10.0) + xAux[i];
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX[i] = ((x - xClick[i]) / 63.0) + xAux[i];
			panY[i] = ((y - yClick[i]) / (-63.0)) + yAux[i];
		}
	}
}

void mouseMotion1(int x, int y)
{
	mouseMotion(x, y, 1);
}

void processNormalKeys(unsigned char key, int x, int y){
	//Process escape key
	if (key == 27){ // Close the app
		exit(0);
	}
}

void processNormalKeys1(unsigned char key, int x, int y){
	if(key == 13){
		add = true;
	}

	if(key == 114){
		if(shape == 0){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 1){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 2){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 3){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 4){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 5){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
		if(shape == 6){
			if(color[shape][0] >= 1.0){
				color[shape][0] = 0.0;
			}else{
				color[shape][0] = color[shape][0] + 0.1;
			}
		}
	}
	if(key == 103){
		if(shape == 0){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 1){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 2){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 3){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 4){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 5){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
		if(shape == 6){
			if(color[shape][1] >= 1.0){
				color[shape][1] = 0.0;
			}else{
				color[shape][1] = color[shape][1] + 0.1;
			}
		}
	}
	if(key == 98){
		if(shape == 0){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 1){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 2){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 3){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 4){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 5){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
		if(shape == 6){
			if(color[shape][2] >= 1.0){
				color[shape][2] = 0.0;
			}else{
				color[shape][2] = color[shape][2] + 0.1;
			}
		}
	}
}

void processSpecialKeys1(int key, int x, int y){

	if (key == 100){ //Left
		if(shape == 0){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 1){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 2){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 3){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 4){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 5){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 6){
			xD1 = xD1 + 0.1;
			translate[shape][0] = xD1;
		}
	}
	if (key == 101){ //up
		if(shape == 0){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 1){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 2){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 3){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 4){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 5){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 6){
			yD1 = yD1 + 0.1;
			translate[shape][1] = yD1;
		}
	}
	if (key == 102){ //right
		if(shape == 0){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 1){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 2){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 3){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 4){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 5){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
		if(shape == 6){
			xD1 = xD1 - 0.1;
			translate[shape][0] = xD1;
		}
	}
	if (key == 103){ //up
		if(shape == 0){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 1){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 2){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 3){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 4){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 5){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
		if(shape == 6){
			yD1 = yD1 - 0.1;
			translate[shape][1] = yD1;
		}
	}
}

int main(int argc, char** argv)
{
	// Init Window (GLUT)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	mainWindow = glutCreateWindow("Examen Final A01221156");
	subWindow0 = glutCreateSubWindow(mainWindow, 0, 0, 100, height);
	subWindow1 = glutCreateSubWindow(mainWindow, 101, 0, width - 101, height);

	// Callback functions registration (GLUT) for main window
	glutSetWindow(mainWindow);
	glutDisplayFunc(display);		// display scene function
	glutReshapeFunc(reshape);		// reshape window function
	glutIdleFunc(idle);				// idle function
	glutKeyboardFunc(processNormalKeys);

	// Callback functions registration (GLUT) for subwindows
	glutSetWindow(subWindow0);
	glutDisplayFunc(display0);		// display scene function
	glutReshapeFunc(reshape0);		// reshape window function
	glutMouseFunc(mouse0);			// mouse events processing function

	
	glutSetWindow(subWindow1);
	glutDisplayFunc(display1);		// display scene function
	glutReshapeFunc(reshape1);		// reshape window function
	glutMouseFunc(mouse1);			// mouse events processing function
	glutMotionFunc(mouseMotion1);	// mouse motion processing function
	glutKeyboardFunc(processNormalKeys1);
	glutSpecialFunc(processSpecialKeys1);

								// init OpenGL context
	glutSetWindow(subWindow0);
	init0();
	glutSetWindow(subWindow1);
	init1();
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();					// Main loop waiting for events!
	return 0;
}
