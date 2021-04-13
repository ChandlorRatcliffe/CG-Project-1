#include "ShearXMatrix.h"
#include "TranslationMatrix.h"
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
ShearXMatrix::ShearXMatrix(float sx, float yAxis) {
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
	TranslationMatrix T = TranslationMatrix(0.0, -yAxis);
	this->composeWith(&T);

}