//==============================================================================
// File: ui/Button.cpp
// Purpose: UI Button implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#include "ui/Button.h"
#include "core/Application.h"
#include "core/Input.h"
#include "core/Window.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

namespace CowGL {
    Button::Button(const std::string &label, int x, int y, int width, int height)
        : m_label(label)
          , m_x(x)
          , m_y(y)
          , m_width(width)
          , m_height(height)
          , m_hovered(false)
          , m_pressed(false) {
    }

    void Button::update() {
        Input *input = Application::getInstance()->getInput();
        Window *window = Application::getInstance()->getWindow();

        glm::vec2 mousePos = input->getMousePosition();
        int windowHeight = window->getHeight();

        // Mouse coordinates are already in window space (0,0 is top-left)
        // Button coordinates are in OpenGL space (0,0 is bottom-left)
        // So we need to convert mouse Y coordinate
        int mouseY = windowHeight - mousePos.y;

        // Check if mouse is over button
        m_hovered = (mousePos.x >= m_x && mousePos.x <= m_x + m_width &&
                     mouseY >= m_y && mouseY <= m_y + m_height);

        // Check for click
        if (m_hovered && input->isMouseButtonJustPressed(Input::MouseButton::Left)) {
            m_pressed = true;
            if (m_callback) {
                m_callback();
            }
        } else if (!input->isMouseButtonPressed(Input::MouseButton::Left)) {
            m_pressed = false;
        }
    }

    void Button::render() {
        // Button background
        if (m_pressed) {
            glColor3f(0.5f, 0.5f, 0.5f);
        } else if (m_hovered) {
            glColor3f(0.7f, 0.7f, 0.7f);
        } else {
            glColor3f(0.85f, 0.85f, 0.85f);
        }

        glBegin(GL_QUADS);
        glVertex2f(m_x, m_y);
        glVertex2f(m_x + m_width, m_y);
        glVertex2f(m_x + m_width, m_y + m_height);
        glVertex2f(m_x, m_y + m_height);
        glEnd();

        // Button frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(m_x + 1, m_y + 1);
        glVertex2f(m_x + m_width - 1, m_y + 1);
        glVertex2f(m_x + m_width - 1, m_y + m_height - 1);
        glVertex2f(m_x + 1, m_y + m_height - 1);
        glEnd();

        // Button label
        glColor3f(0.0f, 0.0f, 0.0f);
        int textWidth = m_label.length() * 9; // Approximate
        int textX = m_x + (m_width - textWidth) / 2;
        int textY = m_y + (m_height / 2) - 5; // Center vertically

        glRasterPos2f(textX, textY);
        for (char c: m_label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    bool Button::isClicked(int mouseX, int mouseY) const {
        return (mouseX >= m_x && mouseX <= m_x + m_width &&
                mouseY >= m_y && mouseY <= m_y + m_height);
    }
} // namespace CowGL
