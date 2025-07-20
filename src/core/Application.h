//==============================================================================
// File: core/Application.h
// Purpose: Main application class that manages the game loop and systems
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef APPLICATION_H
#define APPLICATION_H


#include <memory>
#include <chrono>

namespace CowGL {
    class Window;
    class Renderer;
    class Scene;
    class UIManager;
    class Input;

    class Application {
    public:
        Application(int argc, char **argv);

        ~Application();

        // Prevent copying
        Application(const Application &) = delete;

        Application &operator=(const Application &) = delete;

        int run();

        void shutdown();

        static Application *getInstance() { return s_instance; }
        Window *getWindow() const { return m_window.get(); }
        Renderer *getRenderer() const { return m_renderer.get(); }
        Scene *getScene() const { return m_scene.get(); }
        Input *getInput() const { return m_input.get(); }

    private:
        void initialize(int argc, char **argv);

        void update(float deltaTime);

        void render();

        void handleEvents();

        static Application *s_instance;

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Scene> m_scene;
        std::unique_ptr<UIManager> m_uiManager;
        std::unique_ptr<Input> m_input;

        std::chrono::steady_clock::time_point m_lastFrameTime;
        bool m_running = true;
        static void timerCallback(int value);
    };
} // namespace CowGL


#endif //APPLICATION_H
