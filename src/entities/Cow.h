//==============================================================================
// File: entities/Cow.h
// Purpose: Cow entity class
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef COW_H
#define COW_H


#include "scene/GameObject.h"
#include "utils/Math.h"

namespace CowGL {
    class Cow : public GameObject {
    public:
        enum class ControlMode {
            Movement,
            Head,
            Tail
        };

        explicit Cow(const std::string &name = "Cow");

        ~Cow() override = default;

        void update(float deltaTime) override;

        // Movement controls
        void moveForward(float deltaTime);

        void moveBackward(float deltaTime);

        void turnLeft(float deltaTime);

        void turnRight(float deltaTime);

        // Head controls
        void moveHeadUp(float deltaTime);

        void moveHeadDown(float deltaTime);

        void turnHeadLeft(float deltaTime);

        void turnHeadRight(float deltaTime);

        void resetHead();

        // Tail controls
        void moveTailUp(float deltaTime);

        void moveTailDown(float deltaTime);

        void turnTailLeft(float deltaTime);

        void turnTailRight(float deltaTime);

        void resetTail();

        // Getters for camera
        glm::vec3 getEyePosition() const;

        glm::vec3 getLookDirection() const;

        const glm::vec3 &getEyePositionRef() const { return m_eyePosition; }

        ControlMode getControlMode() const { return m_controlMode; }

    protected:
        void onRender() override;

    private:
        void renderBody();

        void renderHead();

        void renderTail();

        void renderLeg(const glm::vec3 &position);

        // Movement
        float m_moveSpeed;
        float m_turnSpeed;

        // Head state
        float m_headHorizontalAngle;
        float m_headVerticalAngle;

        // Tail state
        float m_tailHorizontalAngle;
        float m_tailVerticalAngle;

        // Animation
        float m_animationTime;

        // Camera support
        glm::vec3 m_eyePosition;

        // Control mode
        ControlMode m_controlMode;
    };
} // namespace CowGL


#endif //COW_H
