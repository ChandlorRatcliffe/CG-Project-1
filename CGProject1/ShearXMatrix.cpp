#include "ShearXMatrix.h"
#include "TranslationMatrix.h"
#include "CompositeMatrix.h"
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
	CompositeMatrix       C = CompositeMatrix();
	TranslationMatrix   Tup = TranslationMatrix(0.0, yAxis);
	TranslationMatrix Tdown = TranslationMatrix(0.0, -yAxis);
	ShearXMatrix          S = ShearXMatrix(sx);
	C.composeWith(&Tdown);
	C.composeWith(&S);
	C.composeWith(&Tup);
	copyFrom(&C);
}