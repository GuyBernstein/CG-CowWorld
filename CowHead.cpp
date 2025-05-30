//
// Created by Guy Bernstein on 29/05/2025.
//

#include "CowHead.h"
#include "QuadricRenderer.h"

// Static member definitions
constexpr GLfloat CowHead::COW_BROWN[];
constexpr GLfloat CowHead::IVORY[];
constexpr GLfloat CowHead::PINK[];
constexpr GLfloat CowHead::DARK_GRAY[];
constexpr GLfloat CowComponent::BLACK_COLOR[];
constexpr GLfloat CowComponent::WHITE_COLOR[];

void CowHead::render(const WcPt3D& position, const GLfloat rotation)
{
    glPushMatrix();

    // Apply position and rotation
    glTranslatef(position.getX(), position.getY(), position.getZ());
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);

    // Apply head movement
    glRotatef(m_horizontalAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(m_verticalAngle, 0.0f, 1.0f, 0.0f);

    // Render head components
    renderMainHead();
    renderHorns();
    renderEars();
    renderNose();
    renderEyes();

    glPopMatrix();
}

void CowHead::renderMainHead()
{
    QuadricRenderer quad;

    setMaterial(COW_BROWN);

    // Head sphere
    glPushMatrix();
    glScalef(1.0f, 0.8f, 1.0f); // Slightly flattened
    quad.sphere(Cow::HEAD_RADIUS);
    glPopMatrix();
}

void CowHead::renderHorns()
{
    QuadricRenderer quad;

    setMaterial(IVORY);

    // Left horn
    glPushMatrix();
    glTranslatef(-Cow::HEAD_RADIUS * 0.5f, 0.0f, Cow::HEAD_RADIUS * 0.8f);
    glRotatef(-80.0f, 1.0f, 0.0f, 0.0f);
    quad.cylinder(0.05f, 0.02f, 0.3f, 8, 8);
    glPopMatrix();

    // Right horn
    glPushMatrix();
    glTranslatef(Cow::HEAD_RADIUS * 0.5f, 0.0f, Cow::HEAD_RADIUS * 0.8f);
    glRotatef(-80.0f, 1.0f, 0.0f, 0.0f);
    quad.cylinder(0.05f, 0.02f, 0.3f, 8, 8);
    glPopMatrix();
}

void CowHead::renderEars()
{
    setMaterial(COW_BROWN);

    // Left ear
    glPushMatrix();
    glTranslatef(-Cow::HEAD_RADIUS * 0.8f, 0.0f, Cow::HEAD_RADIUS * 0.3f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.1f, 0.5f);
    glutSolidSphere(0.2, 8, 8);
    glPopMatrix();

    // Right ear
    glPushMatrix();
    glTranslatef(Cow::HEAD_RADIUS * 0.8f, 0.0f, Cow::HEAD_RADIUS * 0.3f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.1f, 0.5f);
    glutSolidSphere(0.2, 8, 8);
    glPopMatrix();
}

void CowHead::renderNose()
{
    setMaterial(PINK);

    // Nose/snout
    glPushMatrix();
    glTranslatef(0.0f, -Cow::HEAD_RADIUS * 0.8f, -Cow::HEAD_RADIUS * 0.2f);
    glScalef(1.5f, 1.0f, 0.8f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
}

void CowHead::renderEyes()
{
    QuadricRenderer quad;

    // Eye whites
    setMaterial(WHITE_COLOR);

    // Left eye
    glPushMatrix();
    glTranslatef(-Cow::HEAD_RADIUS * 0.4f, -Cow::HEAD_RADIUS * 0.3f, Cow::HEAD_RADIUS * 0.2f);
    quad.sphere(0.08, 8, 8);
    glPopMatrix();

    // Right eye
    glPushMatrix();
    glTranslatef(Cow::HEAD_RADIUS * 0.4f, -Cow::HEAD_RADIUS * 0.3f, Cow::HEAD_RADIUS * 0.2f);
    quad.sphere(0.08, 8, 8);
    glPopMatrix();

    // Pupils
    setMaterial(BLACK_COLOR);

    // Left pupil
    glPushMatrix();
    glTranslatef(-Cow::HEAD_RADIUS * 0.4f, -Cow::HEAD_RADIUS * 0.35f, Cow::HEAD_RADIUS * 0.25f);
    quad.sphere(0.04, 6, 6);
    glPopMatrix();

    // Right pupil
    glPushMatrix();
    glTranslatef(Cow::HEAD_RADIUS * 0.4f, -Cow::HEAD_RADIUS * 0.35f, Cow::HEAD_RADIUS * 0.25f);
    quad.sphere(0.04, 6, 6);
    glPopMatrix();
}

void CowComponent::setMaterial(const GLfloat* ambient, const GLfloat* emission, const GLfloat* specular)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient);

    if (emission)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
    else
    {
        GLfloat blackEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, blackEmission);
    }

    if (specular)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    }
    else
    {
        constexpr GLfloat blackSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, blackSpecular);
    }
}