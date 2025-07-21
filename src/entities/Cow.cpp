//==============================================================================
// File: entities/Cow.cpp
// Purpose: Cow entity implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "entities/Cow.h"
#include "core/Application.h"
#include "core/Input.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "graphics/Camera.h"

namespace CowGL {
    namespace {
        // Colors
        const GLfloat COW_BROWN[] = {0.42f, 0.18f, 0.12f, 1.0f};
        const GLfloat DARK_GRAY[] = {0.3f, 0.3f, 0.3f, 1.0f};
        const GLfloat PINK[] = {1.0f, 0.75f, 0.79f, 1.0f};
        const GLfloat IVORY[] = {1.0f, 1.0f, 0.94f, 1.0f};
        const GLfloat WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};
        const GLfloat BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};

        // Movement constants
        const float MOVE_SPEED = 5.0f;
        const float TURN_SPEED = 90.0f;
        const float HEAD_TURN_SPEED = 60.0f;
        const float TAIL_TURN_SPEED = 60.0f;

        // Angle limits
        const float HEAD_MAX_HORIZONTAL = 80.0f;
        const float HEAD_MAX_VERTICAL = 60.0f;
        const float TAIL_MAX_HORIZONTAL = 45.0f;
        const float TAIL_MAX_VERTICAL = 45.0f;
    }

    Cow::Cow(const std::string &name)
        : GameObject(name)
          , m_moveSpeed(MOVE_SPEED)
          , m_turnSpeed(TURN_SPEED)
          , m_headHorizontalAngle(0.0f)
          , m_headVerticalAngle(0.0f)
          , m_tailHorizontalAngle(0.0f)
          , m_tailVerticalAngle(-30.0f)
          , m_animationTime(0.0f)
          , m_eyePosition(0.0f, 0.0f, 0.0f)
          , m_controlMode(ControlMode::Movement) {
    }

    void Cow::update(float deltaTime) {
        // Calculate eye position with head rotation
        glm::vec3 headOffset(1.1f, 0.0f, 1.3f);
        float headYaw = glm::radians(m_headHorizontalAngle);
        float headPitch = glm::radians(m_headVerticalAngle);

        glm::vec3 rotatedOffset(
            headOffset.x * std::cos(headYaw) - headOffset.y * std::sin(headYaw),
            headOffset.x * std::sin(headYaw) + headOffset.y * std::cos(headYaw),
            headOffset.z + headOffset.x * std::sin(headPitch)
        );

        m_eyePosition = m_transform.getPosition() + rotatedOffset;
        m_animationTime += deltaTime;

        // Handle input
        Input *input = Application::getInstance()->getInput();

        // Toggle control modes
        if (input->isKeyJustPressed('t') || input->isKeyJustPressed('T')) {
            m_controlMode = ControlMode::Tail;
        } else if (input->isKeyJustPressed('h') || input->isKeyJustPressed('H')) {
            m_controlMode = ControlMode::Head;
        } else if (input->isKeyJustPressed('m') || input->isKeyJustPressed('M')) {
            m_controlMode = ControlMode::Movement;
        }

        // Movement controls (always active)
        if (input->isKeyPressed('w') || input->isKeyPressed('W')) moveForward(deltaTime);
        if (input->isKeyPressed('s') || input->isKeyPressed('S')) moveBackward(deltaTime);
        if (input->isKeyPressed('a') || input->isKeyPressed('A')) turnLeft(deltaTime);
        if (input->isKeyPressed('d') || input->isKeyPressed('D')) turnRight(deltaTime);

        // Context-sensitive controls (I,J,K,L)
        switch (m_controlMode) {
            case ControlMode::Head:
                if (input->isKeyPressed('i') || input->isKeyPressed('I')) moveHeadUp(deltaTime);
                if (input->isKeyPressed('k') || input->isKeyPressed('K')) moveHeadDown(deltaTime);
                if (input->isKeyPressed('j') || input->isKeyPressed('J')) turnHeadLeft(deltaTime);
                if (input->isKeyPressed('l') || input->isKeyPressed('L')) turnHeadRight(deltaTime);
                break;

            case ControlMode::Tail:
                if (input->isKeyPressed('i') || input->isKeyPressed('I')) moveTailUp(deltaTime);
                if (input->isKeyPressed('k') || input->isKeyPressed('K')) moveTailDown(deltaTime);
                if (input->isKeyPressed('j') || input->isKeyPressed('J')) turnTailLeft(deltaTime);
                if (input->isKeyPressed('l') || input->isKeyPressed('L')) turnTailRight(deltaTime);
                break;

            default:
                break;
        }

        // Reset controls
        if (input->isKeyPressed('r') || input->isKeyPressed('R')) {
            resetHead();
            resetTail();
        }

        // Reset with numpad 5
        if (input->isKeyPressed('5')) {
            resetHead();
            resetTail();
        }
    }

    void Cow::moveForward(float deltaTime) {
        glm::vec3 forward = m_transform.getForward();
        m_transform.translate(forward * m_moveSpeed * deltaTime);
    }

    void Cow::moveBackward(float deltaTime) {
        glm::vec3 forward = m_transform.getForward();
        m_transform.translate(forward * -m_moveSpeed * deltaTime);
    }

    void Cow::turnLeft(float deltaTime) {
        m_transform.rotate(glm::vec3(0.0f, 0.0f, m_turnSpeed * deltaTime));
    }

    void Cow::turnRight(float deltaTime) {
        m_transform.rotate(glm::vec3(0.0f, 0.0f, -m_turnSpeed * deltaTime));
    }

    void Cow::moveHeadUp(float deltaTime) {
        m_headVerticalAngle = std::min(m_headVerticalAngle + HEAD_TURN_SPEED * deltaTime, HEAD_MAX_VERTICAL);
    }

    void Cow::moveHeadDown(float deltaTime) {
        m_headVerticalAngle = std::max(m_headVerticalAngle - HEAD_TURN_SPEED * deltaTime, -HEAD_MAX_VERTICAL);
    }

    void Cow::turnHeadLeft(float deltaTime) {
        m_headHorizontalAngle = std::min(m_headHorizontalAngle + HEAD_TURN_SPEED * deltaTime, HEAD_MAX_HORIZONTAL);
    }

    void Cow::turnHeadRight(float deltaTime) {
        m_headHorizontalAngle = std::max(m_headHorizontalAngle - HEAD_TURN_SPEED * deltaTime, -HEAD_MAX_HORIZONTAL);
    }

    void Cow::resetHead() {
        m_headHorizontalAngle = 0.0f;
        m_headVerticalAngle = 0.0f;
    }

    void Cow::moveTailUp(float deltaTime) {
        m_tailVerticalAngle = std::min(m_tailVerticalAngle + TAIL_TURN_SPEED * deltaTime, TAIL_MAX_VERTICAL);
    }

    void Cow::moveTailDown(float deltaTime) {
        m_tailVerticalAngle = std::max(m_tailVerticalAngle - TAIL_TURN_SPEED * deltaTime, -TAIL_MAX_VERTICAL);
    }

    void Cow::turnTailLeft(float deltaTime) {
        m_tailHorizontalAngle = std::min(m_tailHorizontalAngle + TAIL_TURN_SPEED * deltaTime, TAIL_MAX_HORIZONTAL);
    }

    void Cow::turnTailRight(float deltaTime) {
        m_tailHorizontalAngle = std::max(m_tailHorizontalAngle - TAIL_TURN_SPEED * deltaTime, -TAIL_MAX_HORIZONTAL);
    }

    void Cow::resetTail() {
        m_tailHorizontalAngle = 0.0f;
        m_tailVerticalAngle = -30.0f;
    }

    glm::vec3 Cow::getEyePosition() const {
        return m_eyePosition;
    }

    glm::vec3 Cow::getLookDirection() const {
        float yaw = glm::radians(m_transform.getRotation().z + m_headHorizontalAngle);
        float pitch = glm::radians(m_headVerticalAngle);

        return glm::vec3(
            std::cos(yaw) * std::cos(pitch),
            std::sin(yaw) * std::cos(pitch),
            std::sin(pitch)
        );
    }

    void Cow::onRender() {
        // Don't render the cow in first-person view
        auto scene = Application::getInstance()->getScene();
        Camera* camera = scene->getActiveCamera();
        if (camera && camera->getMode() == Camera::Mode::FirstPerson) {
            // Skip rendering the cow when in first-person mode
            return;
        }

        glEnable(GL_LIGHTING);

        renderBody();
        renderHead();
        renderTail();

        glDisable(GL_LIGHTING);

    }

    void Cow::renderBody() {
        GLUquadric *quadric = gluNewQuadric();

        // Body
        glPushMatrix();
        glTranslatef(-0.7f, 0.0f, 1.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COW_BROWN);

        // Add specular highlight to make lighting more visible
        GLfloat cowSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, cowSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

        gluCylinder(quadric, 0.5f, 0.5f, 1.4f, 20, 20);

        // Udder
        glPushMatrix();
        glTranslatef(-0.25f, 0.0f, 0.5f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PINK);
        glutSolidSphere(0.35f, 20, 20);
        glPopMatrix();

        // Legs
        renderLeg(glm::vec3(-0.6f, 0.4f, 0.0f));
        renderLeg(glm::vec3(-0.6f, -0.4f, 0.0f));
        renderLeg(glm::vec3(0.6f, 0.4f, 0.0f));
        renderLeg(glm::vec3(0.6f, -0.4f, 0.0f));

        gluDeleteQuadric(quadric);
    }

    void Cow::renderHead() {
        GLUquadric *quadric = gluNewQuadric();

        glPushMatrix();
        glTranslatef(1.1f, 0.0f, 1.3f);
        glRotatef(m_headHorizontalAngle, 0.0f, 0.0f, 1.0f);
        glRotatef(m_headVerticalAngle, 0.0f, -1.0f, 0.0f);

        // Head
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COW_BROWN);
        glutSolidSphere(0.4f, 20, 20);

        // Horns
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, IVORY);
        glPushMatrix();
        glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.15f, 0.6f, 20, 20);
        glPopMatrix();
        glPushMatrix();
        glRotatef(20.0f, -1.0f, 0.0f, 0.0f);
        glutSolidCone(0.15f, 0.6f, 20, 20);
        glPopMatrix();
        glPopMatrix();

        // Ears
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COW_BROWN);
        glPushMatrix();
        glTranslatef(0.0f, 0.34f, 0.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(quadric, 0.0f, 0.1f, 20, 20);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, -0.34f, 0.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(quadric, 0.0f, 0.1f, 20, 20);
        glPopMatrix();

        // Nose
        glPushMatrix();
        glTranslatef(0.25f, 0.0f, -0.2f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, PINK);
        glutSolidSphere(0.25f, 20, 20);
        glPopMatrix();

        // Eyes
        glPushMatrix();
        glRotatef(80.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.40001f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);
        gluDisk(quadric, 0.0f, 0.04f, 20, 20);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BLACK);
        glTranslatef(0.0f, 0.0f, 0.001f);
        gluDisk(quadric, 0.0f, 0.025f, 20, 20);
        glPopMatrix();
        glPushMatrix();
        glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.40001f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);
        gluDisk(quadric, 0.0f, 0.04f, 20, 20);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BLACK);
        glTranslatef(0.0f, 0.0f, 0.001f);
        gluDisk(quadric, 0.0f, 0.025f, 20, 20);
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        gluDeleteQuadric(quadric);
    }

    void Cow::renderTail() {
        GLUquadric *quadric = gluNewQuadric();

        glPushMatrix();
        glTranslatef(-0.69f, 0.0f, 1.45f);
        glRotatef(m_tailHorizontalAngle, 0.0f, 0.0f, -1.0f);
        glRotatef(m_tailVerticalAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COW_BROWN);
        glutSolidSphere(0.05f, 20, 20);
        gluCylinder(quadric, 0.05f, 0.05f, 0.75f, 20, 20);

        glTranslatef(0.0f, 0.0f, 0.75f);
        GLfloat walnutColor[] = {0.26f, 0.15f, 0.06f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, walnutColor);
        glutSolidSphere(0.075f, 20, 20);

        glPopMatrix();
        gluDeleteQuadric(quadric);
    }

    void Cow::renderLeg(const glm::vec3 &position) {
        GLUquadric *quadric = gluNewQuadric();

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, COW_BROWN);
        gluCylinder(quadric, 0.1f, 0.1f, 1.0f, 20, 20);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, DARK_GRAY);
        gluCylinder(quadric, 0.10002f, 0.10002f, 0.15f, 20, 20);

        glPopMatrix();
        gluDeleteQuadric(quadric);
    }
} // namespace CowGL
