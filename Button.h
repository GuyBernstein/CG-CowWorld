#pragma once
/*****************************************************************//**
 * \file   Button.h
 * \brief  Class Button declaration.
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <string>
#include "RGBColor.h"

/******************************
*     CLASS DECLARATIONS      *
*******************************/
class Button
{
public:
    Button();
    Button(GLint x, GLint y, GLint w, GLint h, std::string label);

    void render() const;
    bool clicked(GLint x, GLint y) const;

    void setPosition(GLint x, GLint y);
    void setWidth(GLint w);
    void setHeight(GLint h);

private:
    GLint _x, _y;   // Pixel position
    GLint _width;   // Pixel width
    GLint _height;  // Pixel Height
    std::string _label;
};
