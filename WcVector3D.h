#pragma once
/*****************************************************************//**
 * \file   WcVector3D.h
 * \brief  Class WcVector3D declaration and definition.
 * 
 * \author aaron
 * \date   June 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <cmath>
#include "WcPt3D.h"

class WcVector3D :
    public WcPt3D
{
public:
    WcVector3D() : WcPt3D(0.0, 0.0, 0.0) {}
    WcVector3D(GLfloat x, GLfloat y, GLfloat z) : WcPt3D(x, y, z) {}
    void normalize()
    {
        const GLfloat size = sqrt(_x * _x + _y * _y + _z * _z);
        _x = _x / size;
        _y = _y / size;
        _z = _z / size;
    }
};

