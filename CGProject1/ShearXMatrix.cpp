#include "ShearXMatrix.h"
#include "TranslationMatrix.h"
#include "CompositeMatrix.h"
/**
 * ShearYMatrix constructs a homogeneous linear transformation matrix
 * intended to shear a 3 vector in the x direction with respect to the y-axis
 * by a factor of sx.
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
 * alternative vertical line specified by yAxis by a factor of sx.
 */
ShearXMatrix::ShearXMatrix(float sx, float yAxis) {
	CompositeMatrix       composite = CompositeMatrix();
	TranslationMatrix   translateUp = TranslationMatrix(0.0, yAxis);
	TranslationMatrix translateDown = TranslationMatrix(0.0, -yAxis);
	ShearXMatrix              shear = ShearXMatrix(sx);
	composite.composeWith(&translateDown);
	composite.composeWith(&shear);
	composite.composeWith(&translateUp);
	copyFrom(&composite);
}