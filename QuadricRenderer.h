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
    void cylinder(const GLdouble base, const GLdouble top, const GLdouble height, const GLint slices = 20, const GLint stacks = 20) const {
        gluCylinder(m_quadric, base, top, height, slices, stacks);
    }

    // Disk rendering
    void disk(const GLdouble inner, const GLdouble outer, const GLint slices = 20, const GLint loops = 20) const {
        gluDisk(m_quadric, inner, outer, slices, loops);
    }

    // Sphere rendering
    void sphere(const GLdouble radius, const GLint slices = 20, const GLint stacks = 20) const {
        gluSphere(m_quadric, radius, slices, stacks);
    }

    // Configuration
    void setNormals(const GLenum normals) const { gluQuadricNormals(m_quadric, normals); }
    void setTexture(const GLboolean texture) const { gluQuadricTexture(m_quadric, texture); }
    void setOrientation(const GLenum orientation) const { gluQuadricOrientation(m_quadric, orientation); }

private:
    GLUquadric* m_quadric;
};
#endif //QUADRICRENDERER_H
