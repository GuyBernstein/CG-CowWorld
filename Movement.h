//
// Created by Guy Bernstein on 29/05/2025.
// Movement component for handling position and rotation.

#ifndef MOVEMENT_H
#define MOVEMENT_H


#include "WcPt3D.h"
#include "Constants.h"
#include <cmath>

class Movement
{
public:
    Movement(const WcPt3D& initialPosition = WcPt3D());

    // Position control
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();

    // Getters
    const WcPt3D& getPosition() const { return m_position; }
    GLfloat getDirection() const { return m_directionAngle; }

    // Calculated positions
    WcPt3D getForwardPosition(GLfloat distance) const;

private:
    bool isValidPosition(GLfloat x, GLfloat y) const;

    WcPt3D m_position;
    GLfloat m_directionAngle{0.0f};
};

#endif //MOVEMENT_H
