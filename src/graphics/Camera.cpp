//==============================================================================
// File: graphics/Camera.cpp
// Purpose: Camera implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "graphics/Camera.h"
#include "core/Application.h"
#include "scene/Scene.h"
#include "entities/Cow.h"
#include <algorithm>

namespace CowGL {
    Camera::Camera()
        : m_position(0.0f, -10.0f, 5.0f)
          , m_target(0.0f, 0.0f, 0.0f)
          , m_up(0.0f, 0.0f, 1.0f)
          , m_mode(Mode::ThirdPerson)
          , m_fov(60.0f)
          , m_nearPlane(0.1f)
          , m_farPlane(200.0f)
          , m_yaw(0.0f)
          , m_pitch(0.0f)
          , m_followTarget(nullptr)
          , m_orbitDistance(10.0f)
          , m_orbitHorizontalAngle(180.0f)
          , m_orbitVerticalAngle(35.0f) {
    }

    void Camera::update(float deltaTime) {
        switch (m_mode) {
            case Mode::FirstPerson:
                updateFirstPerson();
                break;
            case Mode::ThirdPerson:
                updateThirdPerson();
                break;
        }

    }
    void Camera::updateFirstPerson() {
        if (m_followTarget) {
            // Get cow to determine eye position and look direction
            auto scene = Application::getInstance()->getScene();
            auto cowObj = scene->findGameObject("MainCow");
            if (cowObj) {
                auto cow = std::dynamic_pointer_cast<Cow>(cowObj);
                if (cow) {
                    m_position = cow->getEyePosition();
                    m_target = m_position + cow->getLookDirection();
                }
            }
        }
    }

    void Camera::updateThirdPerson() {
        if (m_followTarget) {
            m_target = *m_followTarget + glm::vec3(0.0f, 0.0f, 1.0f);

            // Calculate camera position based on orbit angles
            float hAngleRad = glm::radians(m_orbitHorizontalAngle);
            float vAngleRad = glm::radians(m_orbitVerticalAngle);

            m_position = m_target + glm::vec3(
                             m_orbitDistance * std::sin(vAngleRad) * std::cos(hAngleRad),
                             m_orbitDistance * std::sin(vAngleRad) * std::sin(hAngleRad),
                             m_orbitDistance * std::cos(vAngleRad)
                         );
        }
    }

    void Camera::rotate(float yaw, float pitch) {
        if (m_mode == Mode::FirstPerson) {
            m_yaw += yaw;
            m_pitch = std::clamp(m_pitch + pitch, -89.0f, 89.0f);
        } else {
            m_orbitHorizontalAngle += yaw;
            m_orbitVerticalAngle = std::clamp(m_orbitVerticalAngle + pitch, 15.0f, 89.0f);
        }
    }

    void Camera::zoom(float delta) {
        if (m_mode == Mode::ThirdPerson) {
            m_orbitDistance = std::clamp(m_orbitDistance + delta, 2.0f, 20.0f);
        } else {
            m_fov = std::clamp(m_fov + delta, 30.0f, 90.0f);
        }
    }

    void Camera::setOrbitAngles(float horizontal, float vertical) {
        m_orbitHorizontalAngle = horizontal;
        m_orbitVerticalAngle = std::clamp(vertical, 15.0f, 89.0f);
    }
} // namespace CowGL
