//==============================================================================
// File: core/Input.h
// Purpose: Input management system
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef INPUT_H
#define INPUT_H


#include <unordered_map>
#include <array>
#include "utils/Math.h"

namespace CowGL {
    class Input {
    public:
        enum class MouseButton {
            Left = 0,
            Middle = 1,
            Right = 2,
            Count
        };

        Input() : m_mouseButtonStates{},
                  m_mouseButtonJustPressed{},
                  m_mousePosition(0.0f, 0.0f),
                  m_lastMousePosition(0.0f, 0.0f),
                  m_mouseDelta(0.0f, 0.0f) {
            m_mouseButtonStates.fill(false);
            m_mouseButtonJustPressed.fill(false);
        }

        ~Input() = default;

        void update();

        // Keyboard
        void onKeyPress(unsigned char key, int x, int y);

        void onKeyRelease(unsigned char key, int x, int y);

        bool isKeyPressed(unsigned char key) const;

        bool isKeyJustPressed(unsigned char key) const;

        // Mouse
        void onMouseButton(int button, int state, int x, int y);

        void onMouseMove(int x, int y);

        bool isMouseButtonPressed(MouseButton button) const;

        bool isMouseButtonJustPressed(MouseButton button) const;

        glm::vec2 getMousePosition() const { return m_mousePosition; }
        glm::vec2 getMouseDelta() const { return m_mouseDelta; }

    private:
        std::unordered_map<unsigned char, bool> m_keyStates;
        std::unordered_map<unsigned char, bool> m_keyJustPressed;

        std::array<bool, static_cast<size_t>(MouseButton::Count)> m_mouseButtonStates;
        std::array<bool, static_cast<size_t>(MouseButton::Count)> m_mouseButtonJustPressed;

        glm::vec2 m_mousePosition;
        glm::vec2 m_lastMousePosition;
        glm::vec2 m_mouseDelta;
    };
} // namespace CowGL


#endif //INPUT_H
