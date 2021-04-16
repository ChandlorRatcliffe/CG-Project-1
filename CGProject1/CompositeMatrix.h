#pragma once
#include "TransformationMatrix.h"
class CompositeMatrix :
    public TransformationMatrix
{
public:
    /**
     * Since the TransformationMatrix class is not meant to be
     * directly called, the CompisiteMatrix class is intended to 
     * fill the role of generic identity matrix designed to house
     * whatever compositition with other matrcies may be desired.
     */
    CompositeMatrix();
};

