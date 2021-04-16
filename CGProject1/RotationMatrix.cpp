#include "RotationMatrix.h"
#include "commonLibs.h"
/**
 * This constructs a homogeneous linear transformation matrix
 * intended to rotate a 3d homogeneous extension of a 2d vector
 * around the origin of the coordinate system anti-clockwise by
 * the given angle in degrees. Conversion to radians is handled
 * internally.
 */
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
/**
 * This helper function accounts for the expectation that
 * angles received by the class will likely be in degrees.
 * Since C++ uses math libraries that compute with radians,
 * conversion is necessary.
 */
float RotationMatrix::deg2rad(float angle) {
	return angle * PI / 180;
}