//
// Created by Guy Bernstein on 29/05/2025.
// Helper class for building OpenGL display lists.

#ifndef DISPLAYLISTBUILDER_H
#define DISPLAYLISTBUILDER_H


#include <string>
#include <functional>
#include "ResourceManager.h"

class DisplayListBuilder
{
public:
    using RenderFunction = std::function<void()>;

    // Build or get existing display list
    static GLuint build(const std::string& name, const RenderFunction& renderFunc)
    {
        auto& manager = ResourceManager::getInstance();

        if (manager.hasDisplayList(name))
        {
            return manager.getDisplayList(name);
        }

        const GLuint listId = manager.createDisplayList(name);

        glNewList(listId, GL_COMPILE);
        renderFunc();
        glEndList();

        return listId;
    }

    // Execute display list
    static void execute(const std::string& name)
    {
        const auto& manager = ResourceManager::getInstance();
        if (manager.hasDisplayList(name))
        {
            glCallList(manager.getDisplayList(name));
        }
    }
};

#endif //DISPLAYLISTBUILDER_H
