#include "ShearXMatrix.h"
#include "TranslationMatrix.h"
#include "CompositeMatrix.h"
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix
 * intended to shear a 3 vector in the x direction with respect to the y-axis.
 */
ShearXMatrix::ShearXMatrix(float sx) {
	this->matrix[0][0] = 1.0;
	this->matrix[0][1] = sx;
	this->matrix[0][2] = 0.0;
	this->matrix[1][0] = 0.0;
	this->matrix[1][1] = 1.0;
	this->matrix[1][2] = 0.0;
	this->matrix[2][0] = 0.0;
	this->matrix[2][1] = 0.0;
	this->matrix[2][2] = 1.0;
	this->type = Type::SHEARX;
}
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix
 * intended to shear a 3 vector in the x direction with respect to an
 * alternative vertical line specified by yAxis.
 */
ShearXMatrix::ShearXMatrix(float sx, float yAxis) {
	CompositeMatrix       C = CompositeMatrix();
	TranslationMatrix   Tup = TranslationMatrix(0.0, yAxis);
	TranslationMatrix Tdown = TranslationMatrix(0.0, -yAxis);
	ShearXMatrix          S = ShearXMatrix(sx);
	C.composeWith(&Tdown);
	C.composeWith(&S);
	C.composeWith(&Tup);
	copyFrom(&C);
}