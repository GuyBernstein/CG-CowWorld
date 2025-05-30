//
// Created by Guy Bernstein on 29/05/2025.
//

#ifndef COWHEAD_H
#define COWHEAD_H

#include "CowComponent.h"
#include "Constants.h"

class CowHead : public CowComponent
{
public:
    void render(const WcPt3D& position, GLfloat rotation) override;

    // Movement control
    void moveUp() { m_verticalAngle = std::min(m_verticalAngle + Cow::HEAD_MOVEMENT_SPEED, Cow::HEAD_MAX_VERTICAL_ANGLE); }
    void moveDown() { m_verticalAngle = std::max(m_verticalAngle - Cow::HEAD_MOVEMENT_SPEED, -Cow::HEAD_MAX_VERTICAL_ANGLE); }
    void turnLeft() { m_horizontalAngle = std::min(m_horizontalAngle + Cow::HEAD_MOVEMENT_SPEED, Cow::HEAD_MAX_HORIZONTAL_ANGLE); }
    void turnRight() { m_horizontalAngle = std::max(m_horizontalAngle - Cow::HEAD_MOVEMENT_SPEED, -Cow::HEAD_MAX_HORIZONTAL_ANGLE); }
    void reset() { m_horizontalAngle = 0.0f; m_verticalAngle = 0.0f; }

    GLfloat getHorizontalAngle() const { return m_horizontalAngle; }
    GLfloat getVerticalAngle() const { return m_verticalAngle; }

private:
    void renderMainHead();
    void renderHorns();
    void renderEars();
    void renderNose();
    void renderEyes();

    GLfloat m_horizontalAngle{0.0f};
    GLfloat m_verticalAngle{0.0f};

    // Material colors
    static constexpr GLfloat COW_BROWN[] = {RGB_COLOR_COW_BROWN, 1.0f};
    static constexpr GLfloat IVORY[] = {RGB_COLOR_IVORY, 1.0f};
    static constexpr GLfloat PINK[] = {RGB_COLOR_PINK, 1.0f};
    static constexpr GLfloat DARK_GRAY[] = {RGB_COLOR_DARK_GRAY, 1.0f};
};
#endif //COWHEAD_H
