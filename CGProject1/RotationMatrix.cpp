#include "RotationMatrix.h"
RotationMatrix::RotationMatrix(float angle) {
	this->matrix[0][0] =  cos(angle);
	this->matrix[0][1] = -sin(angle);
	this->matrix[0][2] =  0.0;
	this->matrix[1][0] =  sin(angle);
	this->matrix[1][1] =  cos(angle);
	this->matrix[1][2] =  0.0;
	this->matrix[2][0] =  0.0;
	this->matrix[2][1] =  0.0;
	this->matrix[2][2] =  1.0;
	this->type = Type::ROTATION;
}