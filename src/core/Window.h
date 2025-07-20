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

        Window(const std::string &title, int width, int height);

        ~Window() = default;

        void setDisplayCallback(DisplayCallback callback);

        void setKeyboardCallback(KeyboardCallback callback);

        void setMouseCallback(MouseCallback callback);



        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void swapBuffers();

        void requestRedraw();

    private:
        static void displayCallbackWrapper();

        static void keyboardCallbackWrapper(unsigned char key, int x, int y);

        static void mouseCallbackWrapper(int button, int state, int x, int y);


        static DisplayCallback s_displayCallback;
        static KeyboardCallback s_keyboardCallback;
        static MouseCallback s_mouseCallback;

        int m_width;
        int m_height;
        int m_windowHandle;
    };
} // namespace CowGL


#endif //WINDOW_H
