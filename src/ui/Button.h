//==============================================================================
// File: ui/Button.h
// Purpose: UI Button class
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "utils/Math.h"

namespace CowGL {
    class Button {
    public:
        using Callback = std::function<void()>;

        Button(const std::string &label, int x, int y, int width, int height);

        ~Button() = default;

        void update();

        void render();

        void setCallback(Callback callback) { m_callback = callback; }

        void setPosition(int x, int y) {
            m_x = x;
            m_y = y;
        }

        void setSize(int width, int height) {
            m_width = width;
            m_height = height;
        }

        void setLabel(const std::string &label) { m_label = label; }

        int getX() const { return m_x; }
        int getY() const { return m_y; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        bool isClicked(int mouseX, int mouseY) const;

    private:
        std::string m_label;
        int m_x, m_y;
        int m_width, m_height;
        Callback m_callback;
        bool m_hovered;
        bool m_pressed;
    };
} // namespace CowGL
#endif //BUTTON_H
