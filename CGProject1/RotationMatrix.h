#pragma once
#include "TransformationMatrix.h"
class RotationMatrix :
    public TransformationMatrix
{
public: 
    /**
     * This constructs a homogeneous linear transformation matrix 
     * intended to rotate a 3d homogeneous extension of a 2d vector
     * around the origin of the coordinate system anti-clockwise by
     * the given angle in degrees. Conversion to radians is handled 
     * internally.
     */
    RotationMatrix(float angle);
private:
    /**
     * This level of detail for pi should be good enough
     * for our purposes.
     */
    const float PI = 3.14159265358979323846;
    /**
     * This helper function accounts for the expectation that
     * angles received by the class will likely be in degrees.
     * Since C++ uses math libraries that compute with radians,
     * conversion is necessary.
     */
    float deg2rad(float angle);
};

