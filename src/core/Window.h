//==============================================================================
// File: core/Window.h
// Purpose: Window management class
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef WINDOW_H
#define WINDOW_H


#include <string>
#include <functional>

namespace CowGL {
    class Window {
    public:
        using DisplayCallback = std::function<void()>;
        using KeyboardCallback = std::function<void(unsigned char, int, int)>;
        using MouseCallback = std::function<void(int, int, int, int)>;
        using MouseMoveCallback = std::function<void(int, int)>;

        Window(const std::string &title, int width, int height);

        ~Window() = default;

        void setDisplayCallback(DisplayCallback callback);

        void setKeyboardCallback(KeyboardCallback callback);

        void setKeyboardUpCallback(KeyboardCallback callback);

        void setMouseCallback(MouseCallback callback);

        void setMouseMoveCallback(MouseMoveCallback callback);

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void swapBuffers();

        void requestRedraw();

    private:
        static void displayCallbackWrapper();

        static void keyboardCallbackWrapper(unsigned char key, int x, int y);

        static void keyboardUpCallbackWrapper(unsigned char key, int x, int y);

        static void mouseCallbackWrapper(int button, int state, int x, int y);

        static void mouseMoveCallbackWrapper(int x, int y);

        static DisplayCallback s_displayCallback;
        static KeyboardCallback s_keyboardCallback;
        static KeyboardCallback s_keyboardUpCallback;
        static MouseCallback s_mouseCallback;
        static MouseMoveCallback s_mouseMoveCallback;

        int m_width;
        int m_height;
        int m_windowHandle;
    };
} // namespace CowGL


#endif //WINDOW_H
