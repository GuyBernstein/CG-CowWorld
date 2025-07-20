//==============================================================================
// File: scene/GameObject.cpp
// Purpose: Base game object implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "scene/GameObject.h"
#include <OpenGL/gl.h>

namespace CowGL {

    GameObject::GameObject(const std::string& name)
        : m_name(name)
        , m_active(true) {
    }

    void GameObject::render() {
        if (!m_active) return;

        glPushMatrix();

        // Apply transform
        glm::vec3 pos = m_transform.getPosition();
        glm::vec3 rot = m_transform.getRotation();
        glm::vec3 scale = m_transform.getScale();

        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
        glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
        glScalef(scale.x, scale.y, scale.z);

        // Render the object
        onRender();

        glPopMatrix();
    }

} // namespace CowGL