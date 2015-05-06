#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Global variables for object's rotation
double rotBody;
double rotHead;
double rotLeftArm;
double rotLeftHand;
double rotRightArm;
double rotRightHand;
double rotLeftLeg;
double rotRightLeg;
double rotLeftFoot;
double rotRightFoot;


double deltaRotBody;
double xBody;
double deltaXBody;
double yBody;
double deltaYBody;

double deltaRotHead;
double xHead;
double deltaXHead;
double yHead;
double deltaYHead;

double deltaRotLeftArm;
double xLeftArm;
double deltaXLeftArm;
double yLeftArm;
double deltaYLeftArm;

double deltaRotLeftHand;
double xLeftHand;
double deltaXLeftHand;
double yLeftHand;
double deltaYLeftHand;

double deltaRotRightArm;
double xRightArm;
double deltaXRightArm;
double yRightArm;
double deltaYRightArm;

double deltaRotRightHand;
double xRightHand;
double deltaXRightHand;
double yRightHand;
double deltaYRightHand;

double deltaRotRightLeg;
double xRightLeg;
double deltaXRightLeg;
double yRightLeg;
double deltaYRightLeg;

double deltaRotLeftLeg;
double xLeftLeg;
double deltaXLeftLeg;
double yLeftLeg;
double deltaYLeftLeg;

double deltaRotLeftFoot;
double xLeftFoot;
double deltaXLeftFoot;
double yLeftFoot;
double deltaYLeftFoot;

double deltaRotRightFoot;
double xRightFoot;
double deltaXRightFoot;
double yRightFoot;
double deltaYRightFoot;

int part;

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
	glTranslatef(0.0, 0., -20.); // Posición inicial de la cámara

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

void processNormalKeys(unsigned char key, int x, int y){
	//printf("%i",key);
	if (key == 48){ //0
		part = 0;
		//printf("%i", part);
	}
	if (key == 49){ //1
		part = 1;
		//printf("1");
	}
	if (key == 50){ //2
		part = 2;
		//printf("2");
	}
	if (key == 51){ //3
		part = 3;
		//printf("3");
	}
	if (key == 52){ //4
		part = 4;
		//printf("4");
	}
	if (key == 53){ //5
		part = 5;
		//printf("5");
	}
	if (key == 54){ //6
		part = 6;
		//printf("6");
	}
	if (key == 55){ //7
		part = 7;
		//printf("7");
	}
	if (key == 56){ //8
		part = 8;
		//printf("8");
	}
	if (key == 57){ //9
		part = 9;
		//printf("9");
	}
}

void processSpecialKeys(int key, int x, int y){
	//printf("%i", part);
	if (key == 100){ //Left
		if(part == 0){
			//printf("Left Body");
			deltaXBody = 0.0;
			deltaYBody = 1.0;
			deltaRotBody = -1.0;
		}
		if(part == 1){
			//printf("Left Head");
			deltaXHead = 0.0;
			deltaYHead = 1.0;
			deltaRotHead = -1.0;
		}
	}
	if (key == 101){ //Up
		if(part == 0){
			//printf("Up Body");
			deltaXBody = 1.0;
			deltaYBody = 0.0;
			deltaRotBody = -1.0;
		}
		if(part == 1){
			//printf("Up Head");
			deltaXHead = 1.0;
			deltaYHead = 0.0;
			deltaRotHead = -1.0;
		}
		if(part == 2){
			//printf("Up LeftArm");
			deltaXLeftArm = 1.0;
			deltaYLeftArm = 0.0;
			deltaRotLeftArm = -1.0;
		}
		if(part == 3){
			//printf("Up LeftHand");
			deltaXLeftHand = 1.0;
			deltaYLeftHand = 0.0;
			deltaRotLeftHand = -1.0;
		}
		if(part == 4){
			//printf("Up RightArm");
			deltaXRightArm = 1.0;
			deltaYRightArm = 0.0;
			deltaRotRightArm = -1.0;
		}
		if(part == 5){
			//printf("Up RightHand");
			deltaXRightHand = 1.0;
			deltaYRightHand = 0.0;
			deltaRotRightHand = -1.0;
		}
		if(part == 6){
			//printf("Up LeftLeg");
			deltaXLeftLeg = 1.0;
			deltaYLeftLeg = 0.0;
			deltaRotLeftLeg = -1.0;
		}
		if(part == 7){
			//printf("Up LeftFoot");
			deltaXLeftFoot = 1.0;
			deltaYLeftFoot = 0.0;
			deltaRotLeftFoot = -1.0;
		}
		if(part == 8){
			//printf("Up RightLeg");
			deltaXRightLeg = 1.0;
			deltaYRightLeg = 0.0;
			deltaRotRightLeg = -1.0;
		}
		if(part == 9){
			//printf("Up RightFoot");
			deltaXRightFoot = 1.0;
			deltaYRightFoot = 0.0;
			deltaRotRightFoot = -1.0;
		}
	}
	if (key == 102){ //Right
		if(part == 0){
			//printf("Right Body");
			deltaXBody = 0.0;
			deltaYBody = 1.0;
			deltaRotBody = 1.0;
		}
		if(part == 1){
			//printf("Right Head");
			deltaXHead = 0.0;
			deltaYHead = 1.0;
			deltaRotHead = 1.0;
		}
	}
	if (key == 103){ //Down
		if(part == 0){
			//printf("Down Body");
			deltaXBody = 1.0;
			deltaYBody = 0.0;
			deltaRotBody = 1.0;
		}
		if(part == 1){
			//printf("Down Head");
			deltaXHead = 1.0;
			deltaYHead = 0.0;
			deltaRotHead = 1.0;
		}
		if(part == 2){
			//printf("Down LeftArm");
			deltaXLeftArm = 1.0;
			deltaYLeftArm = 0.0;
			deltaRotLeftArm = 1.0;
		}
		if(part == 3){
			//printf("Down LeftHand");
			deltaXLeftHand = 1.0;
			deltaYLeftHand = 0.0;
			deltaRotLeftHand = 1.0;
		}
		if(part == 4){
			//printf("Down RightArm");
			deltaXRightArm = 1.0;
			deltaYRightArm = 0.0;
			deltaRotRightArm = 1.0;
		}
		if(part == 5){
			//printf("Down RightHand");
			deltaXRightHand = 1.0;
			deltaYRightHand = 0.0;
			deltaRotRightHand = 1.0;
		}
		if(part == 6){
			//printf("Down LeftLeg");
			deltaXLeftLeg = 1.0;
			deltaYLeftLeg = 0.0;
			deltaRotLeftLeg = 1.0;
		}
		if(part == 7){
			//printf("Down LeftFoot");
			deltaXLeftFoot = 1.0;
			deltaYLeftFoot = 0.0;
			deltaRotLeftFoot = 1.0;
		}
		if(part == 8){
			//printf("Down RightLeg");
			deltaXRightLeg = 1.0;
			deltaYRightLeg = 0.0;
			deltaRotRightLeg = 1.0;
		}
		if(part == 9){
			//printf("Down RightFoot");
			deltaXRightFoot = 1.0;
			deltaYRightFoot = 0.0;
			deltaRotRightFoot = 1.0;
		}
	}
}

void drawRobot()
{
	glPushMatrix();
		//Body
		glPushMatrix();
			glRotatef(rotBody, xBody, yBody, 0.0);
			glutWireCube(1.6);
		glPopMatrix();
		{
			//Head
			glTranslatef(0.0, 1.3, 0.0);
			glPushMatrix();
			glColor3f(0.0, 1.0, 1.0);
				glRotatef(rotHead, xHead, yHead, 0.0);
				glutWireSphere(0.5, 20, 20);
			glPopMatrix();
		}
			{
				//LeftArm
				glTranslatef(-1.1, -1.0, 0.0);
				glPushMatrix();
					glColor3f(0.0, 1.0, 0.0);
					glRotatef(rotLeftArm, xLeftArm, yLeftArm, 0.0);
					glutWireCube(0.7);
					//Left Hand
					glTranslatef(0.0, -0.6, 0.0);
						glPushMatrix();
							glColor3f(0.0, 1.0, 0.0);
							glRotatef(rotLeftHand, xLeftHand, yLeftHand, 0.0);
							glutWireCube(0.4);
						glPopMatrix();
				glPopMatrix();
			}
			{
				//RightArm
				glTranslatef(2.2, 0.0, 0.0);
				glPushMatrix();	
					glRotatef(rotRightArm, xRightArm, yRightArm, 0.0);
					glutWireCube(0.7);
					//Right Hand
					glTranslatef(0.0, -0.6, 0.0);
						glPushMatrix();	
							glRotatef(rotRightHand, xRightHand, yRightHand, 0.0);
							glutWireCube(0.4);
						glPopMatrix();
				glPopMatrix();
			}
			{
				//LeftLeg
				glTranslatef(-1.5, -1.4, 0.0);
				glPushMatrix();	
					glRotatef(rotLeftLeg, xLeftLeg, yLeftLeg, 0.0);
					glutWireCube(0.7);
					//Left Foot
					glTranslatef(0.0, -0.6, 0.0);
						glPushMatrix();	
							glRotatef(rotLeftFoot, xLeftFoot, yLeftFoot, 0.0);
							glutWireCube(0.4);
						glPopMatrix();
				glPopMatrix();
			}
			{
				//RightLeg
				glTranslatef(0.8, 0.0, 0.0);
				glPushMatrix();	
					glRotatef(rotRightLeg, xRightLeg, yRightLeg, 0.0);
					glutWireCube(0.7);
					//Left Foot
					glTranslatef(0.0, -0.6, 0.0);
						glPushMatrix();	
							glRotatef(rotRightFoot, xRightFoot, yRightFoot, 0.0);
							glutWireCube(0.4);
						glPopMatrix();
				glPopMatrix();
			}
	glPopMatrix();
	
	rotBody = rotBody + deltaRotBody;
	rotHead = rotHead + deltaRotHead;
	rotLeftArm = rotLeftArm + deltaRotLeftArm;
	rotRightArm = rotRightArm + deltaRotRightArm;
	rotLeftHand = rotLeftHand + deltaRotLeftHand;
	rotRightHand = rotRightHand + deltaRotRightHand;
	rotLeftLeg = rotLeftLeg + deltaRotLeftLeg;
	rotLeftFoot = rotLeftFoot + deltaRotLeftFoot;
	rotRightLeg = rotRightLeg + deltaRotRightLeg;
	rotRightFoot = rotRightFoot + deltaRotRightFoot;

	xHead = xHead + deltaXHead;
	yHead = yHead + deltaYHead;

	xBody = xBody + deltaXBody;
	yBody = yBody + deltaYBody;

	xLeftArm = xLeftArm + deltaXLeftArm;
	yLeftArm = yLeftArm + deltaYLeftArm;
	
	xLeftHand = xLeftHand + deltaXLeftHand;
	yLeftHand = yLeftHand + deltaYLeftHand;

	xRightArm = xRightArm + deltaXRightArm;
	yRightArm = yRightArm + deltaYRightArm;

	xRightHand = xRightHand + deltaXRightHand;
	yRightHand = yRightHand + deltaYRightHand;

	xRightLeg = xRightLeg + deltaXRightLeg;
	yRightLeg = yRightLeg + deltaYRightLeg;

	xRightFoot = xRightFoot + deltaXRightFoot;
	yRightFoot = yRightFoot + deltaYRightFoot;

	xLeftLeg = xLeftLeg + deltaXLeftLeg;
	yLeftLeg = yLeftLeg + deltaYLeftLeg;

	xLeftFoot = xLeftFoot + deltaXLeftFoot;
	yLeftFoot = yLeftFoot + deltaYLeftFoot;
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
	drawAxis(4.0);
	drawRobot();

	//End Model

	string str = to_string(fps) + " fps";
	glutSetWindowTitle(str.c_str());

	glPopMatrix();

	glutSwapBuffers();	// Swap buffers
}

void idle()
{
	//Reset de variables de movimiento
	deltaRotHead = 0.0;
	deltaRotBody = 0.0;
	deltaRotLeftArm = 0.0;
	deltaRotLeftHand = 0.0;
	deltaRotRightArm = 0.0;
	deltaRotRightHand = 0.0;
	deltaRotLeftFoot = 0.0;
	deltaRotLeftLeg = 0.0;
	deltaRotRightLeg = 0.0;
	deltaRotRightFoot = 0.0;

	deltaXBody = 0.0;
	deltaYBody = 0.0;

	deltaXHead = 0.0;
	deltaYHead = 0.0;

	deltaXLeftArm = 0.0;
	deltaYLeftArm = 0.0;

	deltaXLeftHand = 0.0;
	deltaYLeftHand = 0.0;

	deltaXRightArm = 0.0;
	deltaRotRightArm = 0.0;
	
	deltaXRightHand = 0.0;
	deltaYRightHand = 0.0;

	deltaXRightLeg = 0.0;
	deltaXRightLeg = 0.0;

	deltaXRightFoot = 0.0;
	deltaYRightFoot = 0.0;

	deltaXLeftLeg = 0.0;
	deltaYLeftLeg = 0.0;

	deltaXLeftFoot = 0.0;
	deltaYLeftFoot = 0.0;
	
	//calculate FPS
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
	glutInitWindowSize(800, 700);
	glutCreateWindow("Sistema Solar");
	init();			// OpenGL initialization code
	// Callback functions registration 
	glutReshapeFunc(reshapeViewport);
	glutDisplayFunc(drawScene);
	glutIdleFunc(idle);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
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
