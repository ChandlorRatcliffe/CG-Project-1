#include "ScaleMatrix.h"
/**
 * This constructs a homogeneous linear transformation matrix
 * intended to scale a 3d homogeneous extension of a 2d vector
 * from the origin by scaling factor sx in the x direction and
 * scaling factor sy in the y direction.
 */
ScaleMatrix::ScaleMatrix(float sx, float sy) {
	this->matrix[0][0] = sx;
	this->matrix[0][1] = 0.0;
	this->matrix[0][2] = 0.0;
	this->matrix[1][0] = 0.0;
	this->matrix[1][1] = sy;
	this->matrix[1][2] = 0.0;
	this->matrix[2][0] = 0.0;
	this->matrix[2][1] = 0.0;
	this->matrix[2][2] = 1.0;
	this->type = Type::SCALE;
}