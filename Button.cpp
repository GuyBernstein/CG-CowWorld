//
// Created by Guy Bernstein on 29/05/2025.
//

#include "Button.h"
#include <algorithm>

#include "RGBColor.h"


Button::Button(GLint x, GLint y, GLint width, GLint height, std::string  label)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
    , m_label(std::move(label))
    , m_enabled(true)
{
}

void Button::render() const
{
    // Save current viewport
    GLint oldViewport[4];
    glGetIntegerv(GL_VIEWPORT, oldViewport);

    // Set button viewport
    glViewport(m_x, m_y, m_width, m_height);

    // Save and setup matrices
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, m_width, 0.0, m_height);

    // Render button components
    renderBackground();
    renderFrame();
    renderLabel();

    // Restore matrices and viewport
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
}

bool Button::isClicked(GLint x, GLint y) const
{
    return m_enabled &&
           x >= m_x && x <= (m_x + m_width) &&
           y >= m_y && y <= (m_y + m_height);
}

Button& Button::setPosition(GLint x, GLint y)
{
    m_x = x;
    m_y = y;
    return *this;
}

Button& Button::setSize(GLint width, GLint height)
{
    m_width = std::max(0, width);
    m_height = std::max(0, height);
    return *this;
}

Button& Button::setLabel(const std::string& label)
{
    m_label = label;
    return *this;
}

Button& Button::setEnabled(bool enabled)
{
    m_enabled = enabled;
    return *this;
}

Button& Button::setClickHandler(ClickHandler handler)
{
    m_clickHandler = std::move(handler);
    return *this;
}

void Button::handleClick() const {
    if (m_enabled && m_clickHandler)
    {
        m_clickHandler();
    }
}

void Button::renderBackground() const
{
    // Apply transparency if disabled
    if (!m_enabled)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(RGB_COLOR_WHITE, DISABLED_ALPHA);
    }
    else
    {
        glColor3f(RGB_COLOR_WHITE);
    }

    glRectf(0.0f, 0.0f, static_cast<GLfloat>(m_width), static_cast<GLfloat>(m_height));

    if (!m_enabled)
    {
        glDisable(GL_BLEND);
    }
}

void Button::renderFrame() const
{
    glColor3f(m_enabled ? 0.0f : 0.5f, m_enabled ? 0.0f : 0.5f, m_enabled ? 0.0f : 0.5f);
    glLineWidth(FRAME_WIDTH);

    glBegin(GL_LINE_LOOP);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(static_cast<GLfloat>(m_width), 1.0f);
    glVertex2f(static_cast<GLfloat>(m_width), static_cast<GLfloat>(m_height));
    glVertex2f(1.0f, static_cast<GLfloat>(m_height));
    glEnd();
}

void Button::renderLabel() const
{
    if (m_label.empty()) return;

    glColor3f(m_enabled ? 0.0f : 0.5f, m_enabled ? 0.0f : 0.5f, m_enabled ? 0.0f : 0.5f);
    glRasterPos2f(LABEL_MARGIN_X, LABEL_MARGIN_Y);

    for (char c : m_label)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
