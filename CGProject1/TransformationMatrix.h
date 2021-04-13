#pragma once
#include "TransformationMatrix.h"
class TransformationMatrix
{
public:
	enum class Type{
		IDENTITY,
		ROTATION,
		TRANSLATION,
		SCALE,
		SHEARX,
		SHEARY,
		COMPOSITE
	};
	Type type;
	TransformationMatrix();
	void applyTo(float[2]);
	void composeWith(TransformationMatrix*);
	void printMatrix();
	float matrix[3][3];
};

