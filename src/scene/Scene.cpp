//==============================================================================
// File: scene/Scene.cpp
// Purpose: Scene management implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "scene/Scene.h"
#include "scene/GameObject.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "entities/Cow.h"
#include "entities/Environment.h"
#include "core/Application.h"
#include "core/Input.h"

#include <algorithm>

namespace CowGL {
    Scene::Scene() : m_activeCamera(nullptr), m_cow(nullptr) {
    }

    Scene::~Scene() = default;

    void Scene::initialize() {
        createDefaultScene();
    }

    void Scene::update(float deltaTime) {
        // Update all game objects
        for (auto &obj: m_gameObjects) {
            if (obj->isActive()) {
                obj->update(deltaTime);
            }
        }

        // Update camera
        if (m_activeCamera) {
            m_activeCamera->update(deltaTime);
        }

        // Handle camera controls
        handleCameraControls(deltaTime);
    }

    void Scene::handleCameraControls(float deltaTime) {
        if (!m_activeCamera || !m_cow) return;

        Input *input = Application::getInstance()->getInput();

        // Switch camera mode with 'V'
        if (input->isKeyJustPressed('v') || input->isKeyJustPressed('V')) {
            if (m_activeCamera->getMode() == Camera::Mode::ThirdPerson) {
                m_activeCamera->setMode(Camera::Mode::FirstPerson);
                // Set follow target to cow's position for now, will be updated in Camera::updateFirstPerson()
                m_activeCamera->setFollowTarget(&m_cow->getTransform().getPositionRef());
            } else {
                m_activeCamera->setMode(Camera::Mode::ThirdPerson);
                m_activeCamera->setFollowTarget(&m_cow->getTransform().getPositionRef());
            }
        }

        // Third person camera controls (arrow keys or numpad)
        if (m_activeCamera->getMode() == Camera::Mode::ThirdPerson) {
            float rotateSpeed = 90.0f * deltaTime;
            float zoomSpeed = 5.0f * deltaTime;

            // Rotation controls
            if (input->isKeyPressed('8')) {
                // Numpad 8 - rotate up
                m_activeCamera->rotate(0.0f, -rotateSpeed);
            }
            if (input->isKeyPressed('2')) {
                // Numpad 2 - rotate down
                m_activeCamera->rotate(0.0f, rotateSpeed);
            }
            if (input->isKeyPressed('4')) {
                // Numpad 4 - rotate left
                m_activeCamera->rotate(-rotateSpeed, 0.0f);
            }
            if (input->isKeyPressed('6')) {
                // Numpad 6 - rotate right
                m_activeCamera->rotate(rotateSpeed, 0.0f);
            }

            // Zoom controls
            if (input->isKeyPressed('1')) {
                // Numpad 1 - zoom in
                m_activeCamera->zoom(-zoomSpeed);
            }
            if (input->isKeyPressed('7')) {
                // Numpad 7 - zoom out
                m_activeCamera->zoom(zoomSpeed);
            }

            // Reset camera
            if (input->isKeyPressed('5')) {
                // Numpad 5 - reset
                m_activeCamera->setOrbitAngles(180.0f, 35.0f);
                m_activeCamera->setOrbitDistance(10.0f);
            }
        }
    }

    void Scene::addGameObject(std::shared_ptr<GameObject> object) {
        m_gameObjects.push_back(object);
    }

    void Scene::removeGameObject(const std::string &name) {
        m_gameObjects.erase(
            std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
                           [&name](const auto &obj) { return obj->getName() == name; }),
            m_gameObjects.end()
        );
    }

    std::shared_ptr<GameObject> Scene::findGameObject(const std::string &name) const {
        auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
                               [&name](const auto &obj) { return obj->getName() == name; });

        return (it != m_gameObjects.end()) ? *it : nullptr;
    }

    void Scene::addLight(std::shared_ptr<Light> light) {
        m_lights.push_back(light);
    }

    void Scene::createDefaultScene() {
        // Create ground
        auto ground = std::make_shared<Environment::Ground>();
        addGameObject(ground);

        // Create cow
        m_cow = std::make_shared<Cow>("MainCow");
        m_cow->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        addGameObject(m_cow);

        // Create environment objects
        auto house = std::make_shared<Environment::House>();
        house->getTransform().setPosition(glm::vec3(-10.0f, 0.0f, 0.0f));
        addGameObject(house);

        auto shed = std::make_shared<Environment::Shed>();
        shed->getTransform().setPosition(glm::vec3(10.0f, 10.0f, 0.0f));
        shed->getTransform().setRotation(glm::vec3(0.0f, 0.0f, 180.0f));
        addGameObject(shed);

        auto waterTank = std::make_shared<Environment::WaterTank>();
        waterTank->getTransform().setPosition(glm::vec3(15.0f, 8.0f, 0.0f));
        addGameObject(waterTank);

        // Create trees
        std::vector<glm::vec3> treePositions = {
            {15.0f, 15.0f, 0.0f}, {-20.0f, 10.0f, 0.0f}, {25.0f, 4.0f, 0.0f},
            {19.0f, -9.0f, 0.0f}, {-15.0f, -7.0f, 0.0f}, {7.0f, -12.0f, 0.0f}
        };

        for (size_t i = 0; i < treePositions.size(); ++i) {
            auto tree = std::make_shared<Environment::Tree>();
            tree->getTransform().setPosition(treePositions[i]);
            tree->setName("Tree_" + std::to_string(i));
            addGameObject(tree);
        }

        // Create camera
        auto camera = std::make_unique<Camera>();
        camera->setMode(Camera::Mode::ThirdPerson);
        camera->setFollowTarget(&m_cow->getTransform().getPositionRef());
        setActiveCamera(camera.release());
    }
} // namespace CowGL
