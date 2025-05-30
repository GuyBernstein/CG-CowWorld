//
// Created by Guy Bernstein on 29/05/2025.
//

#include "CowController.h"
#include "QuadricRenderer.h"
#include "Constants.h"
#include "RGBColor.h"

CowController::CowController()
    : m_movement(WcPt3D(0, 0, 0))
{
}

CowController::CowController(const WcPt3D& position)
    : m_movement(position)
{
}

void CowController::render()
{
    // Save current state
    glPushMatrix();

    // Apply cow position and rotation
    const WcPt3D& pos = m_movement.getPosition();
    glTranslatef(pos.getX(), pos.getY(), pos.getZ());
    glRotatef(m_movement.getDirection(), 0.0f, 0.0f, 1.0f);

    // Enable lighting for cow
    glEnable(GL_LIGHTING);

    // Render cow body (simple version for now)
    QuadricRenderer quad;

    // Set material for cow body
    constexpr GLfloat cowBrown[] = {RGB_COLOR_COW_BROWN, 1.0f};
    constexpr GLfloat blackEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cowBrown);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackEmission);

    // Body
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    quad.cylinder(Cow::BODY_RADIUS, Cow::BODY_RADIUS, Cow::BODY_LENGTH);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(Cow::BODY_LENGTH / 2.0f, 0.0f, 0.2f);
    m_head.render(WcPt3D(0, 0, 0), 0);
    glPopMatrix();

    // Simple legs (4 cylinders)
    GLfloat legPositions[4][2] = {
        {Cow::BODY_LENGTH * 0.3f, Cow::BODY_RADIUS * 0.7f},
        {Cow::BODY_LENGTH * 0.3f, -Cow::BODY_RADIUS * 0.7f},
        {-Cow::BODY_LENGTH * 0.3f, Cow::BODY_RADIUS * 0.7f},
        {-Cow::BODY_LENGTH * 0.3f, -Cow::BODY_RADIUS * 0.7f}
    };

    for (const auto & legPosition : legPositions)
    {
        glPushMatrix();
        glTranslatef(legPosition[0], legPosition[1], -Cow::LEG_HEIGHT);
        quad.cylinder(Cow::LEG_RADIUS, Cow::LEG_RADIUS, Cow::LEG_HEIGHT);
        glPopMatrix();
    }

    glDisable(GL_LIGHTING);

    // Restore state
    glPopMatrix();
}