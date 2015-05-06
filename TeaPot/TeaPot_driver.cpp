#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

// This function is called each time the window is resized
void reshapeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

// This function is called each time the window needs to be redrawn.
// It is the "paint" method for our OpenGL program.
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window
	glutCreateWindow("TeaPot :D");
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(reshapeViewport);
	glutDisplayFunc(drawScene);

	// This initializes the entry points in the OpenGL driver
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
	// Start up a loop that runs in the background
	glutMainLoop();
	return 0;
}
