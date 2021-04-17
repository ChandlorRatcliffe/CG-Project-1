#include <vector>
#include <GL/glut.h>
#include "commonLibs.h"
#include "interactions.h"

using namespace Interactions;

GLsizei Interactions::WINDOW_WIDTH = 1280;
GLsizei Interactions::WINDOW_HEIGHT = 1024;

void resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);


	// Pass the size of the OpenGL window to globals.
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// centers the window on any monitor size
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);

	glutCreateWindow("CG-Project-1");

	// default window and drawing colors if none specified else where
	glClearColor(0.5f, 0.2f, 0.1f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);


	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(handleMouseEvent);
	glutMotionFunc(handleMotionEvent);
	glutMainLoop();

	return 0;
}