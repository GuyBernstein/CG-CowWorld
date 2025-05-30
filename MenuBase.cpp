//
// Created by Guy Bernstein on 29/05/2025.
//

#include "MenuBase.h"
#include "Constants.h"

constexpr GLfloat MenuBase::BACKGROUND_COLOR[];

MenuBase::MenuBase(GLint width, GLint height, const std::string& title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
{
}

void MenuBase::render()
{
    if (!m_visible) return;

    // Save current viewport
    GLint oldViewport[4];
    glGetIntegerv(GL_VIEWPORT, oldViewport);

    // Center the menu
    centerMenu();

    // Setup viewport and projection
    glViewport(m_viewportX, m_viewportY, m_width, m_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, m_width, 0.0, m_height);

    // Render background
    glColor3fv(BACKGROUND_COLOR);
    glRectf(0.0f, 0.0f, static_cast<GLfloat>(m_width), static_cast<GLfloat>(m_height));

    // Render frame and title
    renderFrame();
    renderTitle();

    // Render menu-specific content
    renderContent();

    // Render buttons
    for (auto& button : m_buttons)
    {
        button->render();
    }

    // Restore state
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
}

void MenuBase::handleMouse(int button, int state, int x, int y)
{
    if (!m_visible) return;

    // Convert to menu coordinates
    const GLint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    y = windowHeight - y;

    // Check button clicks
    for (auto& btn : m_buttons)
    {
        if (btn->isClicked(x - m_viewportX, y - m_viewportY))
        {
            btn->handleClick();
            break;
        }
    }
}

void MenuBase::centerMenu()
{
    const GLint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    const GLint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    m_viewportX = (windowWidth - m_width) / 2;
    m_viewportY = (windowHeight - m_height) / 2;
}

void MenuBase::renderFrame()
{
    glColor3f(RGB_COLOR_BLACK);
    glLineWidth(FRAME_WIDTH);

    glBegin(GL_LINE_LOOP);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(static_cast<GLfloat>(m_width), 1.0f);
    glVertex2f(static_cast<GLfloat>(m_width), static_cast<GLfloat>(m_height));
    glVertex2f(1.0f, static_cast<GLfloat>(m_height));
    glEnd();
}

void MenuBase::renderTitle()
{
    const GLfloat centerX = m_width / 2.0f - (m_title.length() * 5.0f); // Approximate centering
    renderText(m_title, centerX, m_height - TITLE_OFFSET_Y, GLUT_BITMAP_HELVETICA_18);
}

void MenuBase::renderText(const std::string& text, GLfloat x, GLfloat y, void* font)
{
    glColor3f(RGB_COLOR_BLACK);
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(font, c);
    }
}
