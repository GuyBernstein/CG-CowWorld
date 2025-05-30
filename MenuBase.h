//
// Created by Guy Bernstein on 29/05/2025.
// Base class for all menu types using State pattern

#ifndef MENUBASE_H
#define MENUBASE_H

#include <string>
#include <vector>
#include <memory>
#include "Button.h"
#include "WcPt3D.h"

/******************************
*     CLASS DECLARATION       *
*******************************/
class MenuBase
{
public:
    MenuBase(GLint width, GLint height, const std::string& title);
    virtual ~MenuBase() = default;

    // Core functionality
    virtual void render();
    virtual void handleMouse(int button, int state, int x, int y);
    virtual void handleKeyboard(unsigned char key, int x, int y);

    // Visibility control
    void show() { m_visible = true; }
    void hide() { m_visible = false; }
    void toggle() { m_visible = !m_visible; }
    bool isVisible() const { return m_visible; }

protected:
    // Override these in derived classes
    virtual void renderContent() = 0;
    virtual void setupButtons() {}

    // Helper methods
    void renderFrame();
    void renderTitle();
    void renderText(const std::string& text, GLfloat x, GLfloat y, void* font = GLUT_BITMAP_HELVETICA_12);
    void centerMenu();

    // Properties
    GLint m_width;
    GLint m_height;
    std::string m_title;
    bool m_visible{false};

    // Viewport info
    GLint m_viewportX{0};
    GLint m_viewportY{0};

    // UI elements
    std::vector<std::unique_ptr<Button>> m_buttons;

    // Style constants
    static constexpr GLfloat FRAME_WIDTH = 7.0f;
    static constexpr GLfloat TITLE_OFFSET_Y = 40.0f;
    static constexpr GLfloat BACKGROUND_COLOR[] = {0.8f, 0.8f, 0.8f};
};


#endif //MENUBASE_H
