//
// Created by Guy Bernstein on 29/05/2025.
// Button class

#ifndef BUTTON_H
#define BUTTON_H

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <string>
#include <functional>


class Button
{
public:
    // Type aliases for clarity
    using ClickHandler = std::function<void()>;

    // Constructors
    Button() = default;
    Button(GLint x, GLint y, GLint width, GLint height, std::string  label);

    // Core functionality
    void render() const;
    bool isClicked(GLint x, GLint y) const;

    // Property setters with chaining support
    Button& setPosition(GLint x, GLint y);
    Button& setSize(GLint width, GLint height);
    Button& setLabel(const std::string& label);
    Button& setEnabled(bool enabled);
    Button& setClickHandler(ClickHandler handler);

    // Property getters
    GLint getX() const { return m_x; }
    GLint getY() const { return m_y; }
    GLint getWidth() const { return m_width; }
    GLint getHeight() const { return m_height; }
    const std::string& getLabel() const { return m_label; }
    bool isEnabled() const { return m_enabled; }

    // Event handling
    void handleClick() const;

private:
    // Rendering constants
    static constexpr GLfloat FRAME_WIDTH = 3.0f;
    static constexpr GLfloat LABEL_MARGIN_X = 6.0f;
    static constexpr GLfloat LABEL_MARGIN_Y = 9.0f;
    static constexpr GLfloat DISABLED_ALPHA = 0.5f;

    // Member variables with modern naming convention
    GLint m_x{0};
    GLint m_y{0};
    GLint m_width{0};
    GLint m_height{0};
    std::string m_label;
    bool m_enabled{true};
    ClickHandler m_clickHandler;

    // Helper methods
    void renderBackground() const;
    void renderFrame() const;
    void renderLabel() const;
};

#endif //BUTTON_H
