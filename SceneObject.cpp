//
// Created by Guy Bernstein on 29/05/2025.
//

#include "SceneObject.h"

constexpr GLfloat SceneObject::Materials::BLACK_EMISSION[];
constexpr GLfloat SceneObject::Materials::BLACK_SPECULAR[];
constexpr GLfloat SceneObject::Materials::WHITE_SPECULAR[];

SceneObject::SceneObject(const WcPt3D& position, GLfloat rotation)
    : m_position(position)
    , m_rotation(rotation)
{
}

void SceneObject::render()
{
    beginLighting();
    pushTransform();

    glTranslatef(m_position.getX(), m_position.getY(), m_position.getZ());
    glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

    doRender();

    popTransform();
    endLighting();
}

void SceneObject::beginLighting()
{
    if (!m_lightingEnabled)
    {
        glEnable(GL_LIGHTING);
        m_lightingEnabled = true;
    }
}

void SceneObject::endLighting()
{
    if (m_lightingEnabled)
    {
        glDisable(GL_LIGHTING);
        m_lightingEnabled = false;
    }
}

void SceneObject::setMaterial(const GLfloat* color, const GLfloat* specular, GLfloat shininess)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_EMISSION, Materials::BLACK_EMISSION);

    if (specular)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        if (shininess > 0.0f)
        {
            glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        }
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, Materials::BLACK_SPECULAR);
    }
}

void SceneObject::pushTransform()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    m_matrixStackDepth++;
}

void SceneObject::popTransform()
{
    if (m_matrixStackDepth > 0)
    {
        glPopMatrix();
        m_matrixStackDepth--;
    }
}