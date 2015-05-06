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

//Maximo numero de objetos en la escena de cada tipo
const int MAX = 10;
int objetosActual = 0;


//Objetos a instanciar
Root *root = new Root("Root");
Box *cajas[MAX];
Sphere *esferas[MAX];
Cilinder *cilindros[MAX];
Cone *conos[MAX];
Octahedron *octaedros[MAX];
Dodecahedron *dodecaedros[MAX];
Torus *toroides[MAX];

//Previous object drawn
SceneNode *hierarchy[MAX];

// Global variables for window's size
int width = 800;
int height = 600;

// Global variables for subwindows
int mainWindow;
int subWindow0;
int subWindow1;
int subWindow2;
int subWindow3;

// Global variables for moving camera
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

//Get the shape to be draw
int shape = 0;

//Parte a mover
int part;

void init0()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ[0]); // Camera inicialization
}

void init1()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ[1]); // Camera inicialization
}

void init2()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoomZ[2]); // Camera inicialization
}

void init3()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., zoomZ[3]); // Camera inicialization
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

void reshape2(int w, int h)
{
	glutSetWindow(subWindow2);
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

void reshape3(int w, int h)
{
	glutSetWindow(subWindow3);
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

void drawObjects(SceneNode *father, SceneNode *child){
		father->addChild(child);
}

void drawObjects(SceneNode * node){
	SceneGraph *scene = new SceneGraph(root);
	if(node == NULL){
		scene->draw();	// draw the scene graph!
	}
	else{
		drawObjects(root, node);
		scene->draw();
	}
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
	drawAxis(2.);       // Drawing global coordinate system

	if(shape == 0){
		esferas[objetosActual] = new Sphere("Esfera");
		esferas[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		esferas[objetosActual]->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		esferas[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(esferas[objetosActual]);
		tempScene->draw();	// draw the scene graph!
		
	}
	if(shape == 1){
		cajas[objetosActual] = new Box("Caja");
		cajas[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		cajas[objetosActual]->instanceRotate(rotY[1], 1.0, 0.0, 0.0);
		cajas[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(cajas[objetosActual]);
		tempScene->draw();	// draw the scene graph!
	}
	if(shape == 2){
		conos[objetosActual] = new Cone("Cono");
		conos[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		conos[objetosActual]->instanceRotate(rotY[1], 1.0, 0.0, 0.0);
		conos[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(conos[objetosActual]);
		tempScene->draw();	// draw the scene graph!
	}
	if(shape == 3){
		cilindros[objetosActual] = new Cilinder("Cilindro");
		cilindros[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		cilindros[objetosActual]->instanceRotate(rotY[1], 1.0, 0.0, 0.0);
		cilindros[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(cilindros[objetosActual]);
		tempScene->draw();	// draw the scene graph!
	}
	if(shape == 4){
		octaedros[objetosActual] = new Octahedron("Octaedro");
		octaedros[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		octaedros[objetosActual]->instanceRotate(rotY[1], 1.0, 0.0, 0.0);
		octaedros[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(octaedros[objetosActual]);
		tempScene->draw();	// draw the scene graph!
	}
	if(shape == 5){
		dodecaedros[objetosActual] = new Dodecahedron("Dodecahedro");
		dodecaedros[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		dodecaedros[objetosActual]->instanceRotate(rotY[1], 1.0, 0.0, 0.0);
		dodecaedros[objetosActual]->instanceRotate(rotX[1], 0.0, 1.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(dodecaedros[objetosActual]);
		tempScene->draw();	// draw the scene graph!
	}
	if(shape == 6){
		toroides[objetosActual] = new Torus("Toroide");
		toroides[objetosActual]->instanceScale(zoomZ[1], zoomZ[1], zoomZ[1]);
		toroides[objetosActual]->instanceRotate(1.0, rotY[1], 0.0, 0.0);
		toroides[objetosActual]->instanceRotate(rotX[1], 1.0, 0.0, 0.0);
		SceneGraph *tempScene = new SceneGraph(toroides[objetosActual]);
		tempScene->draw();	// draw the scene graph!

	}

	//End Scene Model

	glPopMatrix();
	glutSwapBuffers();	// Swap buffers
}

void display2()
{
	glutSetWindow(subWindow2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX[2], panY[2], zoomZ[2]);


	SceneGraph *hierarchy = new SceneGraph(root);
	hierarchy->draw();

	glPopMatrix();
	glutSwapBuffers();	// Swap buffers
	//delete hierarchy;
}

void display3()
{
	glutSetWindow(subWindow3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX[3], panY[3], zoomZ[3]);

	drawAxis(1.0);
	drawObjects(NULL);

	glPopMatrix();
	glutSwapBuffers();	// Swap buffers
	
}

void display()
{
	display0();
	display1();
	display2();
	display3();
}

void idle()
{
	glutPostRedisplay();    // call display
}

// i- current subwindow
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

void mouse2(int button, int state, int x, int y)
{
	mouse(button, state, x, y, 2);
}

void mouse3(int button, int state, int x, int y)
{
	mouse(button, state, x, y, 3);
}

// i- current subwindow
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

void mouseMotion2(int x, int y)
{
	mouseMotion(x, y, 2);
}

void mouseMotion3(int x, int y)
{
	mouseMotion(x, y, 3);

	if(part <= objetosActual)
	{
		hierarchy[part]->incrementalRotate(rotY[3], 1.0, 0.0, 0.0);
		hierarchy[part]->incrementalRotate(rotX[3], 0.0, 1.0, 0.0);
	}
}

void processNormalKeys(unsigned char key, int x, int y){
	//Process escape key
	if (key == 27){ // Close the app
		exit(0);
	}
}

void processNormalKeys1(unsigned char key, int x, int y){
	//Process enter key
	if(key == 13){
		if(shape == 0)
		{
			if(objetosActual == 0)
			{
				drawObjects(esferas[objetosActual]);
				hierarchy[objetosActual] = esferas[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],esferas[objetosActual]);
				hierarchy[objetosActual] = esferas[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 1)
		{
			if(objetosActual == 0)
			{
				drawObjects(cajas[objetosActual]);
				hierarchy[objetosActual] = cajas[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],cajas[objetosActual]);
				hierarchy[objetosActual] = cajas[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 2)
		{
			if(objetosActual == 0)
			{
				drawObjects(conos[objetosActual]);
				hierarchy[objetosActual] = conos[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],conos[objetosActual]);
				hierarchy[objetosActual] = conos[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 3)
		{
			if(objetosActual == 0)
			{
				drawObjects(cilindros[objetosActual]);
				hierarchy[objetosActual] = cilindros[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],cilindros[objetosActual]);
				hierarchy[objetosActual] = cilindros[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 4)
		{
			if(objetosActual == 0)
			{
				drawObjects(octaedros[objetosActual]);
				hierarchy[objetosActual] = octaedros[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],octaedros[objetosActual]);
				hierarchy[objetosActual] = octaedros[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 5)
		{
			if(objetosActual == 0)
			{
				drawObjects(dodecaedros[objetosActual]);
				hierarchy[objetosActual] = dodecaedros[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],dodecaedros[objetosActual]);
				hierarchy[objetosActual] = dodecaedros[objetosActual];
			}
			objetosActual++;
		}
		if(shape == 6)
		{
			if(objetosActual == 0)
			{
				drawObjects(toroides[objetosActual]);
				hierarchy[objetosActual] = toroides[objetosActual];
			}
			else
			{
				drawObjects(hierarchy[objetosActual-1],toroides[objetosActual]);
				hierarchy[objetosActual] = toroides[objetosActual];
			}
			objetosActual++;
		}
	}
}

void processNormalKeys3(unsigned char key, int x, int y){;
	if (key == 48){ //0
		part = 0;
	}
	if (key == 49){ //1
		part = 1;
	}
	if (key == 50){ //2
		part = 2;
	}
	if (key == 51){ //3
		part = 3;
	}
	if (key == 52){ //4
		part = 4;
	}
	if (key == 53){ //5
		part = 5;
	}
	if (key == 54){ //6
		part = 6;
	}
	if (key == 55){ //7
		part = 7;
	}
	if (key == 56){ //8
		part = 8;
	}
	if (key == 57){ //9
		part = 9;
	}
}

void processSpecialKeys3(int key, int x, int y){
	if (key == 100){ //Left
		if(part <= objetosActual)
		{
			hierarchy[part]->incrementalTranslate(-0.1, 0.0, 0.0);
			//hierarchy[part]->incrementalRotate(0.1, 0.0, 1.0, 0.0);
		}
	}
	if (key == 101){ //Up
		if(part <= objetosActual)
		{
			hierarchy[part]->incrementalTranslate(0.0, 0.1, 0.0);
			//hierarchy[part]->incrementalRotate(0.1, 1.0, 0.0, 0.0);
		}
	}
	if (key == 102){ //Right
		if(part <= objetosActual)
		{
			hierarchy[part]->incrementalTranslate(0.1, 0.0, 0.0);
			//hierarchy[part]->incrementalRotate(-0.1, 0.0, 1.0, 0.0);
		}
	}
	if (key == 103){ //Down
		if(part <= objetosActual)
		{
			hierarchy[part]->incrementalTranslate(0.0, -0.1, 0.0);
			//hierarchy[part]->incrementalRotate(-0.1, 1.0, 0.0, 0.0);
		}
	}
}

int main(int argc, char** argv)
{
	// Init Window (GLUT)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	mainWindow = glutCreateWindow("Examen 2 parcial A01221156");
	subWindow0 = glutCreateSubWindow(mainWindow, 0, 0, 100, height);
	subWindow1 = glutCreateSubWindow(mainWindow, 101, 0, width / 2, height / 2);
	subWindow2 = glutCreateSubWindow(mainWindow, (width / 2) + 102, 0, (width / 2) - 102, height / 2);
	subWindow3 = glutCreateSubWindow(mainWindow, 101, height / 2 + 1, width, height / 2);

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

	glutSetWindow(subWindow2);
	glutDisplayFunc(display2);		// display scene function
	glutReshapeFunc(reshape2);		// reshape window function
	glutMouseFunc(mouse2);			// mouse events processing function
	glutMotionFunc(mouseMotion2);	// mouse motion processing function

	glutSetWindow(subWindow3);
	glutDisplayFunc(display3);		// display scene function
	glutReshapeFunc(reshape3);		// reshape window function
	glutMouseFunc(mouse3);			// mouse events processing function
	glutMotionFunc(mouseMotion3);	// mouse motion processing function
	glutKeyboardFunc(processNormalKeys3);
	glutSpecialFunc(processSpecialKeys3);

								// init OpenGL context
	glutSetWindow(subWindow0);
	init0();
	glutSetWindow(subWindow1);
	init1();
	glutSetWindow(subWindow2);
	init2();
	glutSetWindow(subWindow3);
	init3();
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();					// Main loop waiting for events!
	return 0;
}
