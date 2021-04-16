#pragma once
#include "TransformationMatrix.h"
class ScaleMatrix :
    public TransformationMatrix
{
public:
    /**
     * This constructs a homogeneous linear transformation matrix
     * intended to scale a 3d homogeneous extension of a 2d vector
     * from the origin by scaling factor sx in the x direction and 
     * scaling factor sy in the y direction. 
     */
    ScaleMatrix(float sx, float sy);
};

