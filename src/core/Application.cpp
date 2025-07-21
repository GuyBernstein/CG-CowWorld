//==============================================================================
// File: core/Application.cpp
// Purpose: Implementation of the main application class
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "core/Application.h"
#include "core/Window.h"
#include "core/Input.h"
#include "graphics/Renderer.h"
#include "scene/Scene.h"
#include "ui/UIManager.h"
#include "entities/Cow.h"
#include "entities/Environment.h"

#include <GLUT/glut.h>
#include <iostream>

namespace CowGL {
    Application *Application::s_instance = nullptr;

    Application::Application(int argc, char **argv) {
        if (s_instance) {
            throw std::runtime_error("Application already exists");
        }
        s_instance = this;
        initialize(argc, argv);
    }

    Application::~Application() {
        s_instance = nullptr;
    }

    void Application::initialize(int argc, char **argv) {
        // Initialize GLUT
        glutInit(&argc, argv);

        // Create systems
        m_window = std::make_unique<Window>("CowGL", 1024, 768);
        m_input = std::make_unique<Input>();
        m_renderer = std::make_unique<Renderer>();
        m_scene = std::make_unique<Scene>();
        m_uiManager = std::make_unique<UIManager>();

        // Initialize systems
        m_renderer->initialize();
        m_scene->initialize();
        m_uiManager->initialize();

        // Setup callbacks
        m_window->setDisplayCallback([]() {
            if (s_instance) s_instance->render();
        });

        m_window->setKeyboardCallback([](unsigned char key, int x, int y) {
            if (s_instance) s_instance->m_input->onKeyPress(key, x, y);
        });

        m_window->setKeyboardUpCallback([](unsigned char key, int x, int y) {
            if (s_instance) s_instance->m_input->onKeyRelease(key, x, y);
        });

        m_window->setMouseCallback([](int button, int state, int x, int y) {
            if (s_instance) s_instance->m_input->onMouseButton(button, state, x, y);
        });

        m_window->setMouseMoveCallback([](int x, int y) {
            if (s_instance) s_instance->m_input->onMouseMove(x, y);
        });

        m_window->setReshapeCallback([](int width, int height) {
            if (s_instance) {
                s_instance->m_window->setWidth(width);
                s_instance->m_window->setHeight(height);
                // Update button positions
                s_instance->m_uiManager->updateButtonPositions();
            }
        });

        m_lastFrameTime = std::chrono::steady_clock::now();
    }

    void Application::timerCallback(int value) {
        if (s_instance) {
            s_instance->handleEvents();
            glutPostRedisplay();
            glutTimerFunc(16, timerCallback, 0);
        }
    }

    int Application::run() {
        // Start timer with static callback
        glutTimerFunc(0, Application::timerCallback, 0);


        // Enter main loop
        glutMainLoop();

        return EXIT_SUCCESS;
    }

    void Application::shutdown() {
        m_running = false;
    }

    void Application::update(float deltaTime) {
        m_input->update();
        m_scene->update(deltaTime);
        m_uiManager->update(deltaTime);
    }

    void Application::render() {
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
        m_lastFrameTime = currentTime;

        update(deltaTime);

        m_renderer->beginFrame();
        m_renderer->renderScene(m_scene.get());
        m_uiManager->render(m_renderer.get());
        m_renderer->endFrame();

        // Swap buffers after all rendering is complete
        glutSwapBuffers();
    }

    void Application::handleEvents() {
        // Process any pending events
        if (m_input->isKeyPressed('q') || m_input->isKeyPressed('Q')) {
            exit(0);
        }
    }
} // namespace CowGL
