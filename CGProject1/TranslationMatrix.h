#pragma once
#include "TransformationMatrix.h"
class TranslationMatrix :
    public TransformationMatrix
{
public:
    TranslationMatrix(float tx, float ty);
};

