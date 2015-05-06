#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

// Global variables for definining foreground Color
float red = 1.0;
float green = 1.0;
float blue = 1.0;
const int SHAPE = 1;
const int DRAW_MODE = 2;
const int TEAPOT = 1;
const int SPHERE = 2;
const int CONE = 3;
const int WIREFRAME = 1;
const int SOLID = 2;
int modelShape = TEAPOT;
int drawMode = WIREFRAME;

// This function is called each time the window is resized
void reshapeViewport(int w, int h){
	glViewport(0, 0, w, h);
}

// This function is called each time the window needs to be redrawn.
void drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(red, green, blue);
	if (modelShape == TEAPOT){
		if (drawMode == WIREFRAME){
			glutWireTeapot(0.5);
		}
		else if (drawMode == SOLID){
			glutSolidTeapot(0.5);
		}
	}
	else if (modelShape == CONE){
		if (drawMode == WIREFRAME){
			glutWireCone(0.5, 0.5, 100, 100);
		}
		else if (drawMode == SOLID){
			glutSolidCone(0.5, 0.5, 100, 100);
		}
	}
	else{
		if (drawMode == WIREFRAME){
			glutWireSphere(0.5, 100, 100);
		}
		else if (drawMode == SOLID){
			glutSolidSphere(0.5, 100, 100);
		}
	}
	glutSwapBuffers();
}

//Function in charge of process the inputs for the change of color
void processNormalKeys(unsigned char key, int x, int y){
	if (key == 114 || key == 82){ // Red Color
		red = 1.0;
		green = 0.0;
		blue = 0.0;
	}
	else if (key == 71 || key == 103){ // Green Color
		red = 0.0;
		green = 1.0;
		blue = 0.0;
	}
	else if (key == 66 || key == 98){ // Blue Color
		red = 0.0;
		green = 0.0;
		blue = 1.0;
	}
	else if (key == 27){ // Close the app
		exit(0);
	}
}

void processSpecialKeys(int key, int x, int y){
	if (key == GLUT_KEY_F1){
		cout << "Option Menu:" << endl;
		cout << "Esc key - Close the application" << endl;
		cout << "r/R keys - Draw the shape in Red Color" << endl;
		cout << "g/G keys - Draw the shape in Green Color" << endl;
		cout << "b/B keys - Draw the shape in Blue Color" << endl;
	}
}

void processShapeMenuEvents(int option){	
	switch(option){
		case TEAPOT:
			modelShape = TEAPOT;
		break;
		case SPHERE:
			modelShape = SPHERE;
		break;
		case CONE:
			modelShape = CONE;
		break;
	}
}

//Function used to process the events from the menu related to the mode of draw
void processDrawModeMenuEvents(int option){
	if (option == WIREFRAME)
		drawMode = WIREFRAME;
	else if (option == SOLID)
		drawMode = SOLID;
}
//Function used to change tha figure that will be drawn
void processMainMenuEvents(int option){
	if (option == SHAPE)
		modelShape = TEAPOT;
	else
		modelShape = DRAW_MODE;
}

void createGLUTMenus(){
	// creates the menu and tells glut that the function "processMenuEvents" will handle the events
	int shapeMenu = glutCreateMenu(processShapeMenuEvents);
	//add entries to the Shape menu
	glutAddMenuEntry("Teapot", TEAPOT);
	glutAddMenuEntry("Sphere", SPHERE);
	glutAddMenuEntry("Cone", CONE);
	//add entries to the Draw Mode menu
	int drawModeMenu = glutCreateMenu(processDrawModeMenuEvents);
	glutAddMenuEntry("Wireframe", WIREFRAME);
	glutAddMenuEntry("Solid", SOLID);
	//add both submenus to the main menu
	int mainMenu = glutCreateMenu(processMainMenuEvents);
	glutAddSubMenu("Shape", shapeMenu);
	glutAddSubMenu("Draw Mode", drawModeMenu);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){
	// Init GLUT & Create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Menus with GLUT");

	// register callbacks
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshapeViewport);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(drawScene);

	//creates the menus
	createGLUTMenus();

	// This initializes the entry points in the OpenGL driver
	GLenum err = glewInit();
	if (GLEW_OK != err){
		fprintf(stderr, "GLEW error");
		return 1;
	}
	// Enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}