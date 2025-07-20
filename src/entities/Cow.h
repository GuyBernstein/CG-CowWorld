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
        explicit Cow(const std::string &name = "Cow");

        ~Cow() override = default;

        void update(float deltaTime) override;

        // Movement controls
        void moveForward();

        void moveBackward();

        void turnLeft();

        void turnRight();

        // Head controls
        void moveHeadUp();

        void moveHeadDown();

        void turnHeadLeft();

        void turnHeadRight();

        void resetHead();

        // Tail controls
        void moveTailUp();

        void moveTailDown();

        void turnTailLeft();

        void turnTailRight();

        void resetTail();

        // Getters for camera
        glm::vec3 getEyePosition() const;

        glm::vec3 getLookDirection() const;

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
    };
} // namespace CowGL


#endif //COW_H
