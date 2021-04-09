#include "TransformationMatrix.h"


/**
 * Instatiate a new TransformationMatrix as an identity matrix.
 */
TransformationMatrix::TransformationMatrix() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			this->matrix[i][j] = float(i == j);
	this->type = IDENTITY;
}
/**
 * Take a vector float[2] by reference, and modify it to contain
 * the result of the application of the transformation matrix to it.
 */
void TransformationMatrix::applyTo(float v[2]) {
	//Extend the vector
	float h[3][1] = { {v[0]}, {v[1]}, {1.0} };
	//Create a place for the result
	float r[3][1] = { {0},{0},{0} };
	//Perform the multiplication
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 1; ++j)
			for (int k = 0; k < 3; ++k)
				r[i][j] += this->matrix[i][j] * h[i][j];
	//extract the result, and store in the given vector
	v[0] = h[0][0];
	v[1] = h[1][0];
}
/**
 * Compose this Transformatrix (A) with another TransformationMatrix (B)
 * such that the result of AB is stored in this TransofrmationMatrix.
 */
void TransformationMatrix::composeWith(TransformationMatrix *T) {
	//Create a place for the result
	float r[3][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0} };
	//Perform the multiplication
	for(int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				r[i][j] += this->matrix[i][j] * T->matrix[i][j];
	//Store the result in this TransformationMatrix
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			this->matrix[i][j] = r[i][j];
}