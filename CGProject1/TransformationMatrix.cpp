#include "TransformationMatrix.h"
#include "commonLibs.h"

/**
 * Instatiate a new TransformationMatrix as an identity matrix.
 */
TransformationMatrix::TransformationMatrix() {
	for (int row = 0; row < 3; ++row)
		for (int column = 0; column < 3; ++column)
			this->matrix[row][column] = float(row == column);
	this->type = Type::IDENTITY;
}
/**
 * Take a vector float[2] by reference, and modify it to contain
 * the result of the application of the transformation matrix to it.
 */
void TransformationMatrix::applyTo(float vector[2]) {
	//The only time apply should change the vector given is if 
	//this isn't an identity matrix.
	if (this->type != Type::IDENTITY) {
		//Extend the vector
		float homogeneousVector[3][1] = { {vector[0]}, {vector[1]}, {1.0} };
		//Create a place for the result
		float product[3][1] = { {0},{0},{0} };
		//Perform the multiplication
		for (int row = 0; row < 3; ++row)
			for (int column = 0; column < 1; ++column)
				for (int common = 0; common < 3; ++common)
					product[row][column] += this->matrix[row][common] * homogeneousVector[common][column];
		//extract the result, and store in the given vector
		vector[0] = product[0][0];
		vector[1] = product[1][0];
	}
}
/**
 * Compose this TransformationMatrix (A) with another TransformationMatrix (B)
 * such that the result of AB is stored in this TransofrmationMatrix.
 */
void TransformationMatrix::composeWith(TransformationMatrix *other) {
	//added optimization to remove matrix mulitplication steps from identity matrix results.
	//If neither transformation matrix is an identity matrix, proceed as normal.
	if (other->type != Type::IDENTITY && this->type != Type::IDENTITY) {
		//Create a place for the result
		float product[3][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0} };
		//Perform the multiplication
		for (int row = 0; row < 3; ++row)
			for (int column = 0; column < 3; ++column)
				for (int common = 0; common < 3; ++common)
					product[row][column] += this->matrix[row][common] * other->matrix[common][column];
		//Store the result in this TransformationMatrix
		for (int row = 0; row < 3; ++row)
			for (int column = 0; column < 3; ++column)
				this->matrix[row][column] = product[row][column];
		this->type = Type::COMPOSITE;
	}
	//If this is an identity matrix but the other one isn't, copy that matrix and type to this one.
	else if (this->type == Type::IDENTITY) {
		for (int row = 0; row < 3; ++row)
			for (int column = 0; column < 3; ++column)
				this->matrix[row][column] = other->matrix[row][column];
		this->type = other->type;
	}
	//Otherwise, compose should make no change because the identity matrix makes no change.
}
void TransformationMatrix::printMatrix() {
	std::string output = "";
	for (int row = 0; row < 3; ++row) {
		output += "[" + std::to_string(this->matrix[row][0]);
		for (int column = 1; column < 3; ++column) {
			output += ", " + std::to_string(this->matrix[row][column]);
		}
		output += "]\r\n";
	}
	std::cout << output;
}
