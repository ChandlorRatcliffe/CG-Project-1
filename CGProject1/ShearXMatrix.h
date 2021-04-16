#pragma once
#include "TransformationMatrix.h"
class ShearXMatrix :
    public TransformationMatrix
{
public:
    /**
     * ShearYMatrix constructs a homogeneous linear transformation matrix
     * intended to shear a 3 vector in the x direction with respect to the y-axis.
     */
    ShearXMatrix(float sx);
    /**
     * ShearYMatrix constructs a homogeneous linear transformation matrix
     * intended to shear a 3 vector in the x direction with respect to an
     * alternative vertical line specified by yAxis.
     */
    ShearXMatrix(float sx, float yAxis);
};

