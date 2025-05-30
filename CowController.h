//
// Created by Guy Bernstein on 29/05/2025.
// Cow class using component-based architecture

#ifndef COWCONTROLLER_H
#define COWCONTROLLER_H


#include <memory>
#include "Movement.h"
#include "CowHead.h"
// #include "CowTail.h"
// #include "CowBody.h"
// #include "CameraController.h"

class CowController
{
public:
    CowController();
    explicit CowController(const WcPt3D& position);

    // Rendering
    void render();

    // Movement delegation
    void moveForward() { m_movement.moveForward(); }
    void moveBackward() { m_movement.moveBackward(); }
    void turnLeft() { m_movement.turnLeft(); }
    void turnRight() { m_movement.turnRight(); }

    // Head control delegation
    void moveHeadUp() { m_head.moveUp(); }
    void moveHeadDown() { m_head.moveDown(); }
    void turnHeadLeft() { m_head.turnLeft(); }
    void turnHeadRight() { m_head.turnRight(); }
    void resetHead() { m_head.reset(); }

    // // Tail control delegation
    // void moveTailUp() { m_tail.moveUp(); }
    // void moveTailDown() { m_tail.moveDown(); }
    // void turnTailLeft() { m_tail.turnLeft(); }
    // void turnTailRight() { m_tail.turnRight(); }
    // void resetTail() { m_tail.reset(); }

    // // Camera access
    // CameraController& getCamera() { return m_camera; }
    // const CameraController& getCamera() const { return m_camera; }

    // Position info
    WcPt3D getPosition() const { return m_movement.getPosition(); }

private:
    // Components
    Movement m_movement;
    CowHead m_head;
    // CowTail m_tail;
    // CowBody m_body;
    // CameraController m_camera;
};
#endif //COWCONTROLLER_H
