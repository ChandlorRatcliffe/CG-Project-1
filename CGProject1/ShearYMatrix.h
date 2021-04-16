#pragma once
#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
class ShearYMatrix :
    public TransformationMatrix
{
public:
    /**
     * ShearYMatrix constructs a homogeneous linear transformation matrix
     * intended to shear a 3 vector in the y direction with respect to the x-axis.
     */
    ShearYMatrix(float sy);
    /**
     * ShearYMatrix constructs a homogeneous linear transformation matrix
     * intended to shear a 3 vector in the y direction with respect to an
     * alternative horizontal line specified by xAxis.
     */
    ShearYMatrix(float sy, float xAxis);
};

