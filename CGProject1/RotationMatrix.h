#pragma once
#include "TransformationMatrix.h"
class RotationMatrix :
    public TransformationMatrix
{
public: 
    RotationMatrix(float angle);
private:
    const float PI = 3.14159265358979323846;
    float deg2rad(float angle);
};

