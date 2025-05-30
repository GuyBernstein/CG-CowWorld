//
// Created by Guy Bernstein on 29/05/2025.
// Singleton resource manager for efficient handling of
// OpenGL resources like quadrics, display lists, and textures


#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    // Singleton access
    static ResourceManager& getInstance();

    // Quadric management
    GLUquadric* getQuadric();

    // Display list management
    GLuint createDisplayList(const std::string& name);
    GLuint getDisplayList(const std::string& name) const;
    bool hasDisplayList(const std::string& name) const;
    void deleteDisplayList(const std::string& name);

    // Cleanup
    void cleanup();

    // Delete copy/move constructors and operators
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

private:
    ResourceManager();
    ~ResourceManager();

    // Quadric resource
    GLUquadric* m_quadric{nullptr};

    // Display lists
    std::unordered_map<std::string, GLuint> m_displayLists;

    // Helper to generate unique display list IDs
    static GLuint generateDisplayListId();
};
#endif //RESOURCEMANAGER_H
