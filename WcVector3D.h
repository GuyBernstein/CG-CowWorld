//
// Created by Guy Bernstein on 29/05/2025.
//

#ifndef WCVECTOR3D_H
#define WCVECTOR3D_H


#include <cmath>
#include "WcPt3D.h"

class WcVector3D :
    public WcPt3D
{
public:
    WcVector3D() : WcPt3D(0.0, 0.0, 0.0) {}
    WcVector3D(const GLfloat x, const GLfloat y, const GLfloat z) : WcPt3D(x, y, z) {}
    void normalize()
    {
        const GLfloat size = sqrt(_x * _x + _y * _y + _z * _z);
        _x = _x / size;
        _y = _y / size;
        _z = _z / size;
    }
};

#endif //WCVECTOR3D_H
