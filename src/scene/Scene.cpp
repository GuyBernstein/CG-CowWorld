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

#include <algorithm>

namespace CowGL {

Scene::Scene() : m_activeCamera(nullptr) {
}

Scene::~Scene() = default;

void Scene::initialize() {
    createDefaultScene();
}

void Scene::update(float deltaTime) {
    // Update all game objects
    for (auto& obj : m_gameObjects) {
        if (obj->isActive()) {
            obj->update(deltaTime);
        }
    }

    // Update camera
    if (m_activeCamera) {
        m_activeCamera->update(deltaTime);
    }
}

void Scene::addGameObject(std::shared_ptr<GameObject> object) {
    m_gameObjects.push_back(object);
}

void Scene::removeGameObject(const std::string& name) {
    m_gameObjects.erase(
        std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
            [&name](const auto& obj) { return obj->getName() == name; }),
        m_gameObjects.end()
    );
}

std::shared_ptr<GameObject> Scene::findGameObject(const std::string& name) const {
    auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });

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
    auto cow = std::make_shared<Cow>("MainCow");
    cow->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    addGameObject(cow);

    // Create environment objects
    auto house = std::make_shared<Environment::House>();
    house->getTransform().setPosition(glm::vec3(-10.0f, 0.0f, 0.0f));
    addGameObject(house);

    auto shed = std::make_shared<Environment::Shed>();
    shed->getTransform().setPosition(glm::vec3(0.0f, 8.0f, 0.0f));
    shed->getTransform().setRotation(glm::vec3(0.0f, 0.0f, 180.0f));
    addGameObject(shed);

    auto waterTank = std::make_shared<Environment::WaterTank>();
    waterTank->getTransform().setPosition(glm::vec3(2.5f, 8.0f, 0.0f));
    addGameObject(waterTank);

    // Create trees
    std::vector<glm::vec3> treePositions = {
        {15.0f, 15.0f, 0.0f}, {-84.0f, 47.0f, 0.0f}, {25.0f, 4.0f, 0.0f},
        {19.0f, -9.0f, 0.0f}, {-38.0f, -7.0f, 0.0f}, {7.0f, 2.0f, 0.0f}
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
    camera->setFollowTarget(&cow->getTransform().getPositionRef());
    setActiveCamera(camera.release());
}

} // namespace CowGL