#pragma once
#include "TransformationMatrix.h"
class TranslationMatrix :
    public TransformationMatrix
{
public:
    /**
     * This constructs a homogeneous linear transformation matrix
     * intended to translate a 3d homogeneous extension of a 2d vector
     * by some x shift tx, and some y shift ty as required. 
     */
    TranslationMatrix(float tx, float ty);
};

