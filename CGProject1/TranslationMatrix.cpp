#include "TranslationMatrix.h"
/**
 * This constructs a homogeneous linear transformation matrix
 * intended to translate a 3d homogeneous extension of a 2d vector
 * by some x shift tx, and some y shift ty as required.
 */
TranslationMatrix::TranslationMatrix(float tx, float ty) {
	this->matrix[0][0] = 1.0;
	this->matrix[0][1] = 0.0;
	this->matrix[0][2] = tx;
	this->matrix[1][0] = 0.0;
	this->matrix[1][1] = 1.0;
	this->matrix[1][2] = ty;
	this->matrix[2][0] = 0.0;
	this->matrix[2][1] = 0.0;
	this->matrix[2][2] = 1.0;
	this->type = Type::TRANSLATION;
}