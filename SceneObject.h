//
// Created by Guy Bernstein on 29/05/2025.
// Base class for all scene objects providing common
// rendering functionality


#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <OpenGL/gl.h>
#include "WcPt3D.h"


class SceneObject
{
public:
    explicit SceneObject(const WcPt3D& position = WcPt3D(), GLfloat rotation = 0.0f);
    virtual ~SceneObject() = default;

    // Main rendering method
    void render();

    // Position and orientation
    void setPosition(const WcPt3D& position) { m_position = position; }
    void setRotation(GLfloat rotation) { m_rotation = rotation; }
    const WcPt3D& getPosition() const { return m_position; }
    GLfloat getRotation() const { return m_rotation; }

protected:
    // Override this in derived classes
    virtual void doRender() = 0;

    // Helper methods for common rendering tasks
    void beginLighting();
    void endLighting();

    static void setMaterial(const GLfloat* color, const GLfloat* specular = nullptr, GLfloat shininess = 0.0f);
    void pushTransform();
    void popTransform();

    // Common material presets
    struct Materials {
        static constexpr GLfloat BLACK_EMISSION[] = {0.0f, 0.0f, 0.0f, 1.0f};
        static constexpr GLfloat BLACK_SPECULAR[] = {0.0f, 0.0f, 0.0f, 1.0f};
        static constexpr GLfloat WHITE_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};
    };

    WcPt3D m_position;
    GLfloat m_rotation;

private:
    bool m_lightingEnabled{false};
    int m_matrixStackDepth{0};
};



#endif //SCENEOBJECT_H
