#include "ScaleMatrix.h"
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