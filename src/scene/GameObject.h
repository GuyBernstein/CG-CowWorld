//==============================================================================
// File: scene/GameObject.h
// Purpose: Base game object class
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <string>
#include <memory>
#include "scene/Transform.h"

namespace CowGL {
    class GameObject {
    public:
        GameObject(const std::string &name = "GameObject");

        virtual ~GameObject() = default;

        virtual void update(float deltaTime) {
        }

        virtual void render();

        // Active state
        bool isActive() const { return m_active; }
        void setActive(bool active) { m_active = active; }

        // Name
        const std::string &getName() const { return m_name; }
        void setName(const std::string &name) { m_name = name; }

        // Transform
        Transform &getTransform() { return m_transform; }
        const Transform &getTransform() const { return m_transform; }

    protected:
        virtual void onRender() {
        }

        std::string m_name;
        bool m_active;
        Transform m_transform;
    };
} // namespace CowGL


#endif //GAMEOBJECT_H
