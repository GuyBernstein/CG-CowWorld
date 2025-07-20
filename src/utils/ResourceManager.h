//==============================================================================
// File: utils/ResourceManager.h
// Purpose: Resource management for textures, models, etc.
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include <string>
#include <unordered_map>
#include <memory>

namespace CowGL {
    class Texture;
    class Mesh;
    class Shader;

    class ResourceManager {
    public:
        static ResourceManager &getInstance() {
            static ResourceManager instance;
            return instance;
        }

        // Prevent copying
        ResourceManager(const ResourceManager &) = delete;

        ResourceManager &operator=(const ResourceManager &) = delete;

        // Resource loading functions would go here
        // For now, just placeholders

    private:
        ResourceManager() = default;

        ~ResourceManager() = default;
    };
} // namespace CowGL


#endif //RESOURCEMANAGER_H
