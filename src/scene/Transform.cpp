//==============================================================================
// File: scene/Transform.cpp
// Purpose: Transform component implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "scene/Transform.h"

namespace CowGL {
    Transform::Transform()
        : m_position(0.0f, 0.0f, 0.0f)
          , m_rotation(0.0f, 0.0f, 0.0f)
          , m_scale(1.0f, 1.0f, 1.0f) {
    }

    glm::vec3 Transform::getForward() const {
        float yaw = glm::radians(m_rotation.z);
        float pitch = glm::radians(m_rotation.x);

        return glm::vec3(
            std::cos(yaw) * std::cos(pitch),
            std::sin(yaw) * std::cos(pitch),
            std::sin(pitch)
        );
    }

    glm::vec3 Transform::getRight() const {
        float yaw = glm::radians(m_rotation.z + 90.0f);

        return glm::vec3(
            std::cos(yaw),
            std::sin(yaw),
            0.0f
        );
    }

    glm::vec3 Transform::getUp() const {
        return glm::vec3(0.0f, 0.0f, 1.0f);
    }
} // namespace CowGL
