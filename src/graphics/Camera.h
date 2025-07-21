//==============================================================================
// File: graphics/Camera.h
// Purpose: Camera class for view management
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef CAMERA_H
#define CAMERA_H


#include "entities/Cow.h"
#include "scene/Scene.h"
#include "utils/Math.h"

namespace CowGL {
    class Camera {
    public:
        enum class Mode {
            FirstPerson,
            ThirdPerson
        };

        Camera();

        ~Camera() = default;

        void update(float deltaTime);

        // Setters
        void setPosition(const glm::vec3 &position) { m_position = position; }
        void setTarget(const glm::vec3 &target) { m_target = target; }
        void setUp(const glm::vec3 &up) { m_up = up; }
        void setMode(Mode mode) { m_mode = mode; }
        void setFOV(float fov) { m_fov = fov; }
        void setNearPlane(float near) { m_nearPlane = near; }
        void setFarPlane(float far) { m_farPlane = far; }

        // Getters
        const glm::vec3 &getPosition() const { return m_position; }
        const glm::vec3 &getTarget() const { return m_target; }
        const glm::vec3 &getUp() const { return m_up; }
        Mode getMode() const { return m_mode; }
        float getFOV() const { return m_fov; }
        float getNearPlane() const { return m_nearPlane; }
        float getFarPlane() const { return m_farPlane; }

        // Camera controls
        void rotate(float yaw, float pitch);

        void zoom(float delta);

        void setFollowTarget(const glm::vec3 *target) { m_followTarget = target; }

        // Third person camera controls
        void setOrbitDistance(float distance) { m_orbitDistance = distance; }

        void setOrbitAngles(float horizontal, float vertical);

        float getOrbitDistance() const { return m_orbitDistance; }


    private:
        void updateFirstPerson();

        void updateThirdPerson();

        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up;

        Mode m_mode;
        float m_fov;
        float m_nearPlane;
        float m_farPlane;

        // First person
        float m_yaw;
        float m_pitch;

        // Third person
        const glm::vec3 *m_followTarget;
        float m_orbitDistance;
        float m_orbitHorizontalAngle;
        float m_orbitVerticalAngle;
    };
} // namespace CowGL


#endif //CAMERA_H
