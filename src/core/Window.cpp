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
    Window::KeyboardCallback Window::s_keyboardUpCallback = nullptr;
    Window::MouseCallback Window::s_mouseCallback = nullptr;
    Window::MouseMoveCallback Window::s_mouseMoveCallback = nullptr;
    Window::ReshapeCallback Window::s_reshapeCallback = nullptr;


    Window::Window(const std::string &title, int width, int height)
        : m_width(width), m_height(height) {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        m_windowHandle = glutCreateWindow(title.c_str());

        // Set callbacks
        glutDisplayFunc(displayCallbackWrapper);
        glutKeyboardFunc(keyboardCallbackWrapper);
        glutKeyboardUpFunc(keyboardUpCallbackWrapper);
        glutMouseFunc(mouseCallbackWrapper);
        glutPassiveMotionFunc(mouseMoveCallbackWrapper);
        glutMotionFunc(mouseMoveCallbackWrapper);

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Set clear color
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Sky blue
        glutReshapeFunc(reshapeCallbackWrapper);
    }

    void Window::reshapeCallbackWrapper(int width, int height) {
        if (s_reshapeCallback) {
            s_reshapeCallback(width, height);
        }
    }

    void Window::setReshapeCallback(ReshapeCallback callback) {
        s_reshapeCallback = callback;
    }

    void Window::setDisplayCallback(DisplayCallback callback) {
        s_displayCallback = callback;
    }

    void Window::setKeyboardCallback(KeyboardCallback callback) {
        s_keyboardCallback = callback;
    }

    void Window::setKeyboardUpCallback(KeyboardCallback callback) {
        s_keyboardUpCallback = callback;
    }

    void Window::setMouseCallback(MouseCallback callback) {
        s_mouseCallback = callback;
    }

    void Window::setMouseMoveCallback(MouseMoveCallback callback) {
        s_mouseMoveCallback = callback;
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

    void Window::keyboardUpCallbackWrapper(unsigned char key, int x, int y) {
        if (s_keyboardUpCallback) {
            s_keyboardUpCallback(key, x, y);
        }
    }

    void Window::mouseCallbackWrapper(int button, int state, int x, int y) {
        if (s_mouseCallback) {
            s_mouseCallback(button, state, x, y);
        }
    }

    void Window::mouseMoveCallbackWrapper(int x, int y) {
        if (s_mouseMoveCallback) {
            s_mouseMoveCallback(x, y);
        }
    }
} // namespace CowGL
