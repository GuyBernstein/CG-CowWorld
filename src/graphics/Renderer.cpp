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

#include "ui/UIManager.h"

namespace CowGL {
    Renderer::Renderer() {
        // Renderer will be initialized after OpenGL context is created
    }

    Renderer::~Renderer() = default;

    void Renderer::initialize() {
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
        // Get lighting values from UIManager
        auto app = Application::getInstance();
        auto uiManager = app->getUIManager();

        float globalAmbientValue = uiManager ? uiManager->getGlobalAmbient() : 0.3f;
        float sunIntensityValue = uiManager ? uiManager->getSunIntensity() : 1.0f;
        float sunAngleValue = uiManager ? uiManager->getSunAngle() : 45.0f;

        // Setup global ambient light
        GLfloat globalAmbient[] = {globalAmbientValue, globalAmbientValue, globalAmbientValue, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        // Setup sun light (directional light)
        float angleRad = glm::radians(sunAngleValue);
        GLfloat lightPosition[] = {50.0f * std::cos(angleRad), 50.0f * std::sin(angleRad), 100.0f, 0.0f};
        GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat lightDiffuse[] = {sunIntensityValue, sunIntensityValue, sunIntensityValue, 1.0f};
        GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    }

    void Renderer::renderSkybox() {
        // Get current lighting values
        auto app = Application::getInstance();
        auto uiManager = app->getUIManager();
        float globalAmbientValue = uiManager ? uiManager->getGlobalAmbient() : 0.3f;
        float sunIntensityValue = uiManager ? uiManager->getSunIntensity() : 1.0f;
        float sunAngleValue = uiManager ? uiManager->getSunAngle() : 45.0f;

        // Save current state
        glPushMatrix();
        glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT);

        // Disable depth writes and testing for sky rendering
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

        // Disable lighting for sky rendering
        glDisable(GL_LIGHTING);

        // Enable backface culling to render inside of sphere
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT); // Cull front faces since we're inside the sphere

        // Move sky sphere to camera position to ensure it always surrounds the viewer
        Camera *camera = app->getScene()->getActiveCamera();
        if (camera) {
            glm::vec3 camPos = camera->getPosition();
            glTranslatef(camPos.x, camPos.y, camPos.z);
        }

        // Use bright blue sky color without dimming
        float baseR = 0.529f, baseG = 0.808f, baseB = 0.922f;

        // Optional: slightly modulate based on sun position for atmosphere effect
        float sunHeight = std::sin(glm::radians(sunAngleValue));
        float atmosphereEffect = 0.9f + 0.1f * std::max(0.0f, sunHeight);

        // Set bright sky color
        glColor3f(
            baseR * atmosphereEffect,
            baseG * atmosphereEffect,
            baseB * atmosphereEffect
        );

        // Render sky sphere
        glutSolidSphere(150.0, 50, 50); // Slightly smaller radius to ensure we're well inside

        // Reset culling for sun
        glCullFace(GL_BACK);

        // Render sun
        glPushMatrix();

        // Position sun relative to world origin (not camera)
        // First, undo the camera translation
        if (camera) {
            glm::vec3 camPos = camera->getPosition();
            glTranslatef(-camPos.x, -camPos.y, -camPos.z);
        }

        float angleRad = glm::radians(sunAngleValue);
        float sunDistance = 140.0f; // Place sun inside the sky sphere
        glTranslatef(
            sunDistance * std::cos(angleRad),
            sunDistance * std::sin(angleRad),
            50.0f // Raise sun position for better visibility
        );

        // Sun color: warm yellow-orange that varies with intensity
        glColor3f(
            1.0f * sunIntensityValue,
            0.95f * sunIntensityValue,
            0.4f * sunIntensityValue
        );

        // Render sun as a sphere
        glutSolidSphere(8.0, 20, 20);

        glPopMatrix();

        // Restore state
        glDisable(GL_CULL_FACE);
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        glPopAttrib();
        glPopMatrix();

        // Re-enable lighting for subsequent rendering
        glEnable(GL_LIGHTING);
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
        float windowAspect = (float) windowWidth / (float) windowHeight;

        int viewportWidth, viewportHeight;
        int viewportX = 0, viewportY = 0;

        if (windowAspect > targetAspect) {
            // Window is wider - add black bars on sides
            viewportHeight = windowHeight;
            viewportWidth = (int) (windowHeight * targetAspect);
            viewportX = (windowWidth - viewportWidth) / 2;
        } else {
            // Window is taller - add black bars on top/bottom
            viewportWidth = windowWidth;
            viewportHeight = (int) (windowWidth / targetAspect);
            viewportY = (windowHeight - viewportHeight) / 2;
        }

        glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    }
} // namespace CowGL
