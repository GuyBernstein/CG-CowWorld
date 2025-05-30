//
// Created by Guy Bernstein on 29/05/2025.
//

#include "Movement.h"
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Movement::Movement(const WcPt3D& initialPosition)
    : m_position(initialPosition)
{
}

void Movement::moveForward()
{
    const GLfloat radians = (m_directionAngle * M_PI) / 180.0f;
    const GLfloat newX = m_position.getX() + std::cos(radians) * Cow::MOVEMENT_SPEED;
    const GLfloat newY = m_position.getY() + std::sin(radians) * Cow::MOVEMENT_SPEED;

    if (isValidPosition(newX, newY))
    {
        m_position.setX(newX);
        m_position.setY(newY);
    }
}

void Movement::moveBackward()
{
    const GLfloat radians = (m_directionAngle * M_PI) / 180.0f;
    const GLfloat newX = m_position.getX() - std::cos(radians) * Cow::MOVEMENT_SPEED;
    const GLfloat newY = m_position.getY() - std::sin(radians) * Cow::MOVEMENT_SPEED;

    if (isValidPosition(newX, newY))
    {
        m_position.setX(newX);
        m_position.setY(newY);
    }
}

void Movement::turnLeft()
{
    m_directionAngle += Cow::ROTATION_SPEED;
    if (m_directionAngle >= 360.0f)
    {
        m_directionAngle -= 360.0f;
    }
}

void Movement::turnRight()
{
    m_directionAngle -= Cow::ROTATION_SPEED;
    if (m_directionAngle < 0.0f)
    {
        m_directionAngle += 360.0f;
    }
}

bool Movement::isValidPosition(const GLfloat x, const GLfloat y)
{
    return x >= World::MIN_COORD && x <= World::MAX_COORD &&
           y >= World::MIN_COORD && y <= World::MAX_COORD;
}

WcPt3D Movement::getForwardPosition(const GLfloat distance) const
{
    const GLfloat radians = (m_directionAngle * M_PI) / 180.0f;
    return {
        m_position.getX() + std::cos(radians) * distance,
        m_position.getY() + std::sin(radians) * distance,
        m_position.getZ()
    };
}