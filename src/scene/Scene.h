//==============================================================================
// File: scene/Scene.h
// Purpose: Scene management class:
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include <memory>
#include <string>

namespace CowGL {
    class GameObject;
    class Camera;
    class Light;
    class Cow;

    class Scene {
    public:
        Scene();

        ~Scene();

        void initialize();

        void update(float deltaTime);

        void addGameObject(std::shared_ptr<GameObject> object);

        void removeGameObject(const std::string &name);

        std::shared_ptr<GameObject> findGameObject(const std::string &name) const;

        const std::vector<std::shared_ptr<GameObject> > &getGameObjects() const { return m_gameObjects; }

        void setActiveCamera(Camera *camera) { m_activeCamera = camera; }
        Camera *getActiveCamera() const { return m_activeCamera; }

        void addLight(std::shared_ptr<Light> light);

        const std::vector<std::shared_ptr<Light> > &getLights() const { return m_lights; }

    private:
        void createDefaultScene();

        void handleCameraControls(float deltaTime);

        std::vector<std::shared_ptr<GameObject> > m_gameObjects;
        std::vector<std::shared_ptr<Light> > m_lights;
        Camera *m_activeCamera;
        std::shared_ptr<Cow> m_cow;
    };
} // namespace CowGL


#endif //SCENE_H
