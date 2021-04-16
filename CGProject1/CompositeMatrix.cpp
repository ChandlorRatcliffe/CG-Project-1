#include "CompositeMatrix.h"
/**
 * Since the TransformationMatrix class is not meant to be
 * directly called, the CompisiteMatrix class is intended to
 * fill the role of generic identity matrix designed to house
 * whatever compositition with other matrcies may be desired.
 */
CompositeMatrix::CompositeMatrix() {
	TransformationMatrix::TransformationMatrix();
}