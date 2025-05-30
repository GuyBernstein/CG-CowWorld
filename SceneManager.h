//
// Created by Guy Bernstein on 29/05/2025.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneObject.h"

class SceneManager
{
    std::vector<std::unique_ptr<SceneObject>> m_objects;
public:
    void addObject(const std::string& name, std::unique_ptr<SceneObject> obj)
    {
        m_objects.push_back(std::move(obj));
    }
};
#endif //SCENEMANAGER_H
