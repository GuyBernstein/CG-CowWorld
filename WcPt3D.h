#pragma once
/*****************************************************************//**
 * \file   WcPt3D.h
 * \brief  Class WcPt3D declaration and definition.
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

/**
 * Class definition for WcPt3D.
 * Represents a 3D world coordinate point.
 */
class WcPt3D
{
public:
    WcPt3D() : _x(0.0), _y(0.0), _z(0.0) {}
    WcPt3D(GLfloat x, GLfloat y, GLfloat z) : _x(x), _y(y), _z(z) {}

    GLfloat getX() const { return _x; }
    GLfloat getY() const { return _y; }
    GLfloat getZ() const { return _z; }

    void setX(GLfloat x) { _x = x; }
    void setY(GLfloat y) { _y = y; }
    void setZ(GLfloat z) { _z = z; }

protected:
    GLfloat _x, _y, _z;
};
