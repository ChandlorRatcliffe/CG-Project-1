#include <vector>
#include <windows.h>
#include <stdio.h>
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
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);

	glutCreateWindow("CG-Project-1");

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

int oldmain() {
	float v1[2] = { 1.8, 6.2 };
	float v2[2] = { 1.8, 6.2 };
	float v3[2] = { 1.8, 6.2 };
	TranslationMatrix T = TranslationMatrix(1.5, 6.2);
	RotationMatrix    R = RotationMatrix(45.0);
	ScaleMatrix       S = ScaleMatrix(2.0, 3.0);
	ShearXMatrix     SX = ShearXMatrix(1.25, 1.0);
	ShearYMatrix     SY = ShearYMatrix(1.25, -2.0);
	CompositeMatrix   C = CompositeMatrix();

	std::vector<TransformationMatrix> transformations = std::vector<TransformationMatrix>();
	transformations.push_back(T);
	transformations.push_back(R);
	transformations.push_back(S);
	transformations.push_back(SX);
	transformations.push_back(SY);

	for (int i = 0; i < transformations.size(); ++i)
		C.composeWith(&transformations[i]);

	C.applyTo(v1);

	for (int i = 0; i < transformations.size(); ++i)
		transformations[i].applyTo(v2);

	for (int i = transformations.size() - 1; i > -1; --i)
		transformations[i].applyTo(v3);

	std::cout << "v1 = <" << v1[0] << ", " << v1[1] << ">\r\n";
	std::cout << "v2 = <" << v2[0] << ", " << v2[1] << ">\r\n";
	std::cout << "v3 = <" << v3[0] << ", " << v3[1] << ">\r\n";

	//v1 should equal v3. v2 should be the odd one out.

	return 0;
}