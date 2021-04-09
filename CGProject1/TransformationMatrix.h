#pragma once
class TransformationMatrix
{
public:
	enum Type{
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

