#pragma once
#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
class ShearYMatrix :
    public TransformationMatrix
{
public:
    ShearYMatrix(float sy);
    ShearYMatrix(float sy, float xAxis);
};

