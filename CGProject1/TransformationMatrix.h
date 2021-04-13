#pragma once
#include "TransformationMatrix.h"
class TransformationMatrix
{
public:
	//For the purposes of optimization, this meta data is being tracked.
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
	/**
	 * Instatiate a new TransformationMatrix as an identity matrix.
	 */
	TransformationMatrix();
	/**
	 * Take a vector float[2] by reference, and modify it to contain
	 * the result of the application of the transformation matrix to it.
	 */
	void applyTo(float[2]);

	/**
	 * Compose this TransformationMatrix (A) with another TransformationMatrix (B)
	 * such that the result of AB is stored in this TransofrmationMatrix.
	 */
	void composeWith(TransformationMatrix*);
	/**
	 * copy the matrix from another Transformation Matrix to this one.
	 */
	void copyFrom(TransformationMatrix*);
	/**
	 * Print this transformation to console.
	 * This function is intended for debug purposes only.
	 */
	void printMatrix();
protected:
	float matrix[3][3];
};

