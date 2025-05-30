//
// Created by Guy Bernstein on 29/05/2025.
//

#include "House.h"
// #include "SceneObjects.h" // For getNormalVector

House::House(const WcPt3D& position, GLfloat rotation)
    : SceneObject(position, rotation)
{
}

void House::doRender()
{
    renderWalls();
    renderRoof();
    renderDoor();
    renderWindows();
}

void House::renderWalls()
{
    using namespace Objects;

    setMaterial(WALL_COLOR);

    // Front wall
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(HOUSE_WIDTH / 2.0f, -HOUSE_LENGTH / 2.0f, 0.0f);
    glVertex3f(-HOUSE_WIDTH / 2.0f, -HOUSE_LENGTH / 2.0f, 0.0f);
    glVertex3f(-HOUSE_WIDTH / 2.0f, -HOUSE_LENGTH / 2.0f, HOUSE_WALL_HEIGHT);
    glVertex3f(HOUSE_WIDTH / 2.0f, -HOUSE_LENGTH / 2.0f, HOUSE_WALL_HEIGHT);
    glEnd();

    // Similar for other walls...
}

void House::renderDoor()
{
    using namespace Objects;

    setMaterial(DOOR_COLOR, Materials::WHITE_SPECULAR, 10.0f);

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(HOUSE_WIDTH / 2.0f + 0.01f, HOUSE_DOOR_WIDTH / 2.0f, 0.0f);
    glVertex3f(HOUSE_WIDTH / 2.0f + 0.01f, -HOUSE_DOOR_WIDTH / 2.0f, 0.0f);
    glVertex3f(HOUSE_WIDTH / 2.0f + 0.01f, -HOUSE_DOOR_WIDTH / 2.0f, HOUSE_DOOR_HEIGHT);
    glVertex3f(HOUSE_WIDTH / 2.0f + 0.01f, HOUSE_DOOR_WIDTH / 2.0f, HOUSE_DOOR_HEIGHT);
    glEnd();
}