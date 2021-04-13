#pragma once
#include "commonLibs.h"
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
	void applyTo(float[]);
	void composeWith(TransformationMatrix*);
protected:
	float matrix[3][3];
};

