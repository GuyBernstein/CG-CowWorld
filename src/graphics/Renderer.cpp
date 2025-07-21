//==============================================================================
// File: graphics/Renderer.cpp
// Purpose: Renderer implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "scene/Scene.h"
#include "scene/GameObject.h"
#include "core/Application.h"
#include "core/Window.h"

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

namespace CowGL {
    Renderer::Renderer() {
        // Renderer will be initialized after OpenGL context is created
    }

    Renderer::~Renderer() = default;

    void Renderer::initialize() {
        // For this example, we'll continue using the fixed-function pipeline
        // In a real refactor, we'd implement proper shader support

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Enable lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Set up default material properties
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess[] = {50.0};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }

    void Renderer::beginFrame() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::endFrame() {
        // Don't swap buffers here - let Application handle it after UI rendering
    }

    void Renderer::renderScene(Scene *scene) {
        if (!scene) return;

        // Setup camera
        Camera *camera = scene->getActiveCamera();
        if (camera) {
            auto window = Application::getInstance()->getWindow();
            int width = window->getWidth();
            int height = window->getHeight();

            // Set viewport for main scene (accounting for UI)
            glViewport(0, 0, width, height);

            // Setup projection matrix
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(camera->getFOV(),
                           (float) width / (float) height,
                           camera->getNearPlane(),
                           camera->getFarPlane());

            // Setup view matrix
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glm::vec3 pos = camera->getPosition();
            glm::vec3 target = camera->getTarget();
            glm::vec3 up = camera->getUp();

            gluLookAt(pos.x, pos.y, pos.z,
                      target.x, target.y, target.z,
                      up.x, up.y, up.z);
        }

        // Setup lighting
        setupLighting(scene);

        // Render skybox/background
        renderSkybox();

        // Render all game objects
        const auto &objects = scene->getGameObjects();
        for (const auto &obj: objects) {
            if (obj->isActive()) {
                obj->render();
            }
        }
    }

    void Renderer::renderUI() {
        // Save current state
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // Disable depth test and lighting for UI
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        // Restore state
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
    }

    void Renderer::setupLighting(Scene *scene) {
        // Setup global ambient light
        GLfloat globalAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        // Setup sun light (directional light)
        GLfloat lightPosition[] = {50.0f, 50.0f, 100.0f, 0.0f};
        GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    }

    void Renderer::renderSkybox() {
        // Simple sky sphere
        glPushMatrix();

        GLfloat skyColor[] = {0.529f, 0.808f, 0.922f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, skyColor);
        glMaterialfv(GL_FRONT, GL_EMISSION, skyColor);

        glutSolidSphere(200.0, 50, 50);

        GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, black);

        glPopMatrix();
    }

    void Renderer::setViewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    void Renderer::clear(const glm::vec4 &color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::setupViewport(int windowWidth, int windowHeight) {
        // Calculate viewport to maintain 4:3 aspect ratio
        float targetAspect = 4.0f / 3.0f;
        float windowAspect = (float)windowWidth / (float)windowHeight;

        int viewportWidth, viewportHeight;
        int viewportX = 0, viewportY = 0;

        if (windowAspect > targetAspect) {
            // Window is wider - add black bars on sides
            viewportHeight = windowHeight;
            viewportWidth = (int)(windowHeight * targetAspect);
            viewportX = (windowWidth - viewportWidth) / 2;
        } else {
            // Window is taller - add black bars on top/bottom
            viewportWidth = windowWidth;
            viewportHeight = (int)(windowWidth / targetAspect);
            viewportY = (windowHeight - viewportHeight) / 2;
        }

        glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    }
} // namespace CowGL
