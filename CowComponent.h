//
// Created by Guy Bernstein on 29/05/2025.
// Base class for cow body

#ifndef COWCOMPONENT_H
#define COWCOMPONENT_H

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "WcPt3D.h"

class CowComponent
{
public:
    CowComponent() = default;
    virtual ~CowComponent() = default;

    virtual void render(const WcPt3D& position, GLfloat rotation) = 0;
    virtual void update(float deltaTime) {}

protected:
    // Common rendering helpers
    static void setMaterial(const GLfloat* ambient, const GLfloat* emission = nullptr, const GLfloat* specular = nullptr);

    static constexpr GLfloat BLACK_COLOR[] = {0.0f, 0.0f, 0.0f, 1.0f};
    static constexpr GLfloat WHITE_COLOR[] = {1.0f, 1.0f, 1.0f, 1.0f};
};
#endif //COWCOMPONENT_H
