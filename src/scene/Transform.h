//==============================================================================
// File: scene/Transform.h
// Purpose: Transform component for game objects
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "utils/Math.h"

namespace CowGL {
    class Transform {
    public:
        Transform();

        ~Transform() = default;

        // Position
        const glm::vec3 &getPosition() const { return m_position; }
        glm::vec3 &getPositionRef() { return m_position; }
        void setPosition(const glm::vec3 &position) { m_position = position; }
        void translate(const glm::vec3 &delta) { m_position = m_position + delta; }

        // Rotation (Euler angles in degrees)
        const glm::vec3 &getRotation() const { return m_rotation; }
        void setRotation(const glm::vec3 &rotation) { m_rotation = rotation; }
        void rotate(const glm::vec3 &delta) { m_rotation = m_rotation + delta; }

        // Scale
        const glm::vec3 &getScale() const { return m_scale; }
        void setScale(const glm::vec3 &scale) { m_scale = scale; }
        void setUniformScale(float scale) { m_scale = glm::vec3(scale); }

        // Direction vectors
        glm::vec3 getForward() const;

        glm::vec3 getRight() const;

        glm::vec3 getUp() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation; // Euler angles in degrees
        glm::vec3 m_scale;
    };
} // namespace CowGL


#endif //TRANSFORM_H
