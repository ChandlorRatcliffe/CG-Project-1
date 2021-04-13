#pragma once
#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
class ShearXMatrix :
    public TransformationMatrix
{
public:
    ShearXMatrix(float sx);
    ShearXMatrix(float sx, float yAxis);
};

