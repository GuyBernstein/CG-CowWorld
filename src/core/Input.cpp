//==============================================================================
// File: core/Input.cpp
// Purpose: Input management implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "core/Input.h"
#include <GLUT/glut.h>

namespace CowGL {
    void Input::update() {
        // Clear just pressed states
        m_keyJustPressed.clear();
        m_mouseButtonJustPressed.fill(false);

        // Update mouse delta
        m_mouseDelta = m_mousePosition - m_lastMousePosition;
        m_lastMousePosition = m_mousePosition;
    }

    void Input::onKeyPress(unsigned char key, int x, int y) {
        if (!m_keyStates[key]) {
            m_keyJustPressed[key] = true;
        }
        m_keyStates[key] = true;
    }

    void Input::onKeyRelease(unsigned char key, int x, int y) {
        m_keyStates[key] = false;
    }

    bool Input::isKeyPressed(unsigned char key) const {
        auto it = m_keyStates.find(key);
        return it != m_keyStates.end() && it->second;
    }

    bool Input::isKeyJustPressed(unsigned char key) const {
        auto it = m_keyJustPressed.find(key);
        return it != m_keyJustPressed.end() && it->second;
    }

    void Input::onMouseButton(int button, int state, int x, int y) {
        MouseButton mb;
        switch (button) {
            case GLUT_LEFT_BUTTON: mb = MouseButton::Left;
                break;
            case GLUT_MIDDLE_BUTTON: mb = MouseButton::Middle;
                break;
            case GLUT_RIGHT_BUTTON: mb = MouseButton::Right;
                break;
            default: return;
        }

        size_t index = static_cast<size_t>(mb);
        bool pressed = (state == GLUT_DOWN);

        if (pressed && !m_mouseButtonStates[index]) {
            m_mouseButtonJustPressed[index] = true;
        }

        m_mouseButtonStates[index] = pressed;
        m_mousePosition = glm::vec2(x, y);
    }

    void Input::onMouseMove(int x, int y) {
        m_mousePosition = glm::vec2(x, y);
    }

    bool Input::isMouseButtonPressed(MouseButton button) const {
        return m_mouseButtonStates[static_cast<size_t>(button)];
    }

    bool Input::isMouseButtonJustPressed(MouseButton button) const {
        return m_mouseButtonJustPressed[static_cast<size_t>(button)];
    }
} // namespace CowGL
