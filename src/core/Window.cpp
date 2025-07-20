//==============================================================================
// File: core/Window.cpp
// Purpose: Window management implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "core/Window.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

namespace CowGL {
    Window::DisplayCallback Window::s_displayCallback = nullptr;
    Window::KeyboardCallback Window::s_keyboardCallback = nullptr;
    Window::MouseCallback Window::s_mouseCallback = nullptr;

    Window::Window(const std::string &title, int width, int height)
        : m_width(width), m_height(height) {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        m_windowHandle = glutCreateWindow(title.c_str());

        // Set callbacks
        glutDisplayFunc(displayCallbackWrapper);
        glutKeyboardFunc(keyboardCallbackWrapper);
        glutMouseFunc(mouseCallbackWrapper);

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Set clear color
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Sky blue
    }

    void Window::setDisplayCallback(DisplayCallback callback) {
        s_displayCallback = callback;
    }

    void Window::setKeyboardCallback(KeyboardCallback callback) {
        s_keyboardCallback = callback;
    }

    void Window::setMouseCallback(MouseCallback callback) {
        s_mouseCallback = callback;
    }



    void Window::swapBuffers() {
        glutSwapBuffers();
    }

    void Window::requestRedraw() {
        glutPostRedisplay();
    }

    void Window::displayCallbackWrapper() {
        if (s_displayCallback) {
            s_displayCallback();
        }
    }

    void Window::keyboardCallbackWrapper(unsigned char key, int x, int y) {
        if (s_keyboardCallback) {
            s_keyboardCallback(key, x, y);
        }
    }

    void Window::mouseCallbackWrapper(int button, int state, int x, int y) {
        if (s_mouseCallback) {
            s_mouseCallback(button, state, x, y);
        }
    }

} // namespace CowGL
