#include "RotationMatrix.h"
#include "commonLibs.h"
RotationMatrix::RotationMatrix(float angle) {
	this->matrix[0][0] =  cos(deg2rad(angle));
	this->matrix[0][1] = -sin(deg2rad(angle));
	this->matrix[0][2] =  0.0;
	this->matrix[1][0] =  sin(deg2rad(angle));
	this->matrix[1][1] =  cos(deg2rad(angle));
	this->matrix[1][2] =  0.0;
	this->matrix[2][0] =  0.0;
	this->matrix[2][1] =  0.0;
	this->matrix[2][2] =  1.0;
	this->type = Type::ROTATION;
}
float RotationMatrix::deg2rad(float angle) {
	return angle * PI / 180;
}