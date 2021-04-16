#include "ShearYMatrix.h"
#include "CompositeMatrix.h"
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix 
 * intended to shear a 3 vector in the y direction with respect to the x-axis.
 */
ShearYMatrix::ShearYMatrix(float sy) {
	this->matrix[0][0] = 1.0;
	this->matrix[0][1] = 0.0;
	this->matrix[0][2] = 0.0;
	this->matrix[1][0] = sy;
	this->matrix[1][1] = 1.0;
	this->matrix[1][2] = 0.0;
	this->matrix[2][0] = 0.0;
	this->matrix[2][1] = 0.0;
	this->matrix[2][2] = 1.0;
	this->type = Type::SHEARY;
}
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix
 * intended to shear a 3 vector in the y direction with respect to an
 * alternative horizontal line specified by xAxis.
 */
ShearYMatrix::ShearYMatrix(float sy, float xAxis) {
	CompositeMatrix       C  = CompositeMatrix();
	TranslationMatrix Tleft  = TranslationMatrix(0.0, xAxis);
	TranslationMatrix Tright = TranslationMatrix(0.0, -xAxis);
	ShearYMatrix          S  = ShearYMatrix(sy);
	C.composeWith(&Tright);
	C.composeWith(&S);
	C.composeWith(&Tleft);
	copyFrom(&C);
}