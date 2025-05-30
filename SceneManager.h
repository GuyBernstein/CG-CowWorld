#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneObject.h"
#include <vector>
#include <memory>

class SceneManager
{
    std::vector<std::unique_ptr<SceneObject>> m_objects;
public:
    void addObject(const std::string& name, std::unique_ptr<SceneObject> obj)
    {
        m_objects.push_back(std::move(obj));
    }
    
    void render() const;
};
#endif //SCENEMANAGER_H