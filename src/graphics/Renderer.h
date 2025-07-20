//==============================================================================
// File: graphics/Renderer.h
// Purpose: Main rendering system
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef RENDERER_H
#define RENDERER_H


#include <memory>
#include "utils/Math.h"

namespace CowGL {
    class Scene;
    class Shader;
    class Camera;

    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void initialize();

        void beginFrame();

        void endFrame();

        void renderScene(Scene *scene);

        void renderUI();

        void setViewport(int x, int y, int width, int height);

        void clear(const glm::vec4 &color = glm::vec4(0.529f, 0.808f, 0.922f, 1.0f));

        Shader *getDefaultShader() const { return m_defaultShader.get(); }
        Shader *getUIShader() const { return m_uiShader.get(); }

    private:
        void setupLighting(Scene *scene);

        void renderSkybox();

        std::unique_ptr<Shader> m_defaultShader;
        std::unique_ptr<Shader> m_uiShader;

        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;
    };
} // namespace CowGL


#endif //RENDERER_H
