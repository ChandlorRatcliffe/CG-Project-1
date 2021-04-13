#pragma once
#include "TransformationMatrix.h"
class RotationMatrix :
    public TransformationMatrix
{
public: 
    RotationMatrix(float angle);
};

