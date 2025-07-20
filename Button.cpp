/*****************************************************************//**
 * \file   Button.cpp
 * \brief  Class Button definition.
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include "Button.h"

/******************************
*          METHODS            *
*******************************/
Button::Button() :
    _x(0),
    _y(0),
    _width(0),
    _height(0),
    _label("")
{
}


Button::Button(GLint x, GLint y, GLint w, GLint h, std::string label) :
    _x(x),
    _y(y),
    _width(w),
    _height(h),
    _label(label)
{
}


void Button::render() const
{
    static const GLfloat FRAME_WIDTH = 3.0;
    static const GLfloat LABEL_MARGIN_LEFT = 6.0;
    static const GLfloat LABEL_MARGIN_BOTTOM = 9.0;

    /* Create viewport for button */
    glViewport(_x, _y, _width, _height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, _width, 0.0, _height);

    /* Add background color */
    glColor3f(RGB_COLOR_WHITE);
    glRectf(0.0, 0.0, _width, _height);

    /* Add frame */
    glColor3f(RGB_COLOR_BLACK);
    glLineWidth(FRAME_WIDTH);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.0, 1.0);
    glVertex2f(_width, 1.0);
    glVertex2f(_width, _height);
    glVertex2f(1.0, _height);
    glEnd();

    /* Add label */
    glRasterPos2f(LABEL_MARGIN_LEFT, LABEL_MARGIN_BOTTOM);
    for (const char& c : _label)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}


bool Button::clicked(GLint x, GLint y) const
{
    return (_x <= x) && (x <= (_x + _width)) && 
           (_y <= y) && (y <= (_y + _height));
}


void Button::setPosition(GLint x, GLint y)
{
    _x = x;
    _y = y;
}


void Button::setWidth(GLint w)
{
    _width = w;
}


void Button::setHeight(GLint h)
{
    _height = h;
}
