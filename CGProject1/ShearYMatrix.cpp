#include "ShearYMatrix.h"
#include "CompositeMatrix.h"
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix 
 * intended to shear a 3 vector in the y direction with respect to the x-axis
 * by a factor of sy.
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
 * alternative horizontal line specified by xAxis by a factor of sy.
 */
ShearYMatrix::ShearYMatrix(float sy, float xAxis) {
	CompositeMatrix       composite  = CompositeMatrix();
	TranslationMatrix translateLeft  = TranslationMatrix(0.0, xAxis);
	TranslationMatrix translateRight = TranslationMatrix(0.0, -xAxis);
	ShearYMatrix              shear  = ShearYMatrix(sy);
	composite.composeWith(&translateRight);
	composite.composeWith(&shear);
	composite.composeWith(&translateLeft);
	copyFrom(&composite);
}