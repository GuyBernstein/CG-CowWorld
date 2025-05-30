//
// Created by Guy Bernstein on 29/05/2025.
//

#include "SceneManager.h"

void SceneManager::render() const {
    for (const auto& obj : m_objects)
    {
        if (obj)
        {
            obj->render();
        }
    }
}
