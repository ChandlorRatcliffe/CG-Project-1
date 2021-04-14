#include "TranslationMatrix.h"
TranslationMatrix::TranslationMatrix(float tx, float ty) {
	this->matrix[0][0] = 1.0;
	this->matrix[0][1] = 0.0;
	this->matrix[0][2] = 0.0;
	this->matrix[1][0] = tx;
	this->matrix[1][1] = 1.0;
	this->matrix[1][2] = ty;
	this->matrix[2][0] = 0.0;
	this->matrix[2][1] = 0.0;
	this->matrix[2][2] = 1.0;
	this->type = Type::TRANSLATION;
}