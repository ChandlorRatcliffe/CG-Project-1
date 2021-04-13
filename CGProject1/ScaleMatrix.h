#pragma once
#include "TransformationMatrix.h"
class ScaleMatrix :
    public TransformationMatrix
{
public:
    ScaleMatrix(float sx, float sy);
};

