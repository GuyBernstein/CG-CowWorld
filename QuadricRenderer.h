//
// Created by Guy Bernstein on 29/05/2025.
// RAII wrapper for quadric rendering operations.

#ifndef QUADRICRENDERER_H
#define QUADRICRENDERER_H


#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "ResourceManager.h"

class QuadricRenderer
{
public:
    QuadricRenderer() : m_quadric(ResourceManager::getInstance().getQuadric()) {}

    // Cylinder rendering
    void cylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices = 20, GLint stacks = 20)
    {
        gluCylinder(m_quadric, base, top, height, slices, stacks);
    }

    // Disk rendering
    void disk(GLdouble inner, GLdouble outer, GLint slices = 20, GLint loops = 20)
    {
        gluDisk(m_quadric, inner, outer, slices, loops);
    }

    // Sphere rendering
    void sphere(GLdouble radius, GLint slices = 20, GLint stacks = 20)
    {
        gluSphere(m_quadric, radius, slices, stacks);
    }

    // Configuration
    void setNormals(GLenum normals) { gluQuadricNormals(m_quadric, normals); }
    void setTexture(GLboolean texture) { gluQuadricTexture(m_quadric, texture); }
    void setOrientation(GLenum orientation) { gluQuadricOrientation(m_quadric, orientation); }

private:
    GLUquadric* m_quadric;
};
#endif //QUADRICRENDERER_H
