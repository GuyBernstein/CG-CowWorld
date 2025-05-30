//
// Created by Guy Bernstein on 29/05/2025.
//

#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager()
{
    // Initialize quadric
    m_quadric = gluNewQuadric();
    if (m_quadric)
    {
        gluQuadricNormals(m_quadric, GLU_SMOOTH);
        gluQuadricTexture(m_quadric, GL_FALSE);
    }
}

ResourceManager::~ResourceManager()
{
    cleanup();
}

GLUquadric* ResourceManager::getQuadric()
{
    if (!m_quadric)
    {
        m_quadric = gluNewQuadric();
        if (m_quadric)
        {
            gluQuadricNormals(m_quadric, GLU_SMOOTH);
            gluQuadricTexture(m_quadric, GL_FALSE);
        }
    }
    return m_quadric;
}

GLuint ResourceManager::createDisplayList(const std::string& name)
{
    if (hasDisplayList(name))
    {
        return m_displayLists[name];
    }

    GLuint id = generateDisplayListId();
    m_displayLists[name] = id;
    return id;
}

GLuint ResourceManager::getDisplayList(const std::string& name) const
{
    const auto it = m_displayLists.find(name);
    return (it != m_displayLists.end()) ? it->second : 0;
}

bool ResourceManager::hasDisplayList(const std::string& name) const
{
    return m_displayLists.find(name) != m_displayLists.end();
}

void ResourceManager::deleteDisplayList(const std::string& name)
{
    auto it = m_displayLists.find(name);
    if (it != m_displayLists.end())
    {
        glDeleteLists(it->second, 1);
        m_displayLists.erase(it);
    }
}

void ResourceManager::cleanup()
{
    // Clean up quadric
    if (m_quadric)
    {
        gluDeleteQuadric(m_quadric);
        m_quadric = nullptr;
    }

    // Clean up display lists
    for (const auto& pair : m_displayLists)
    {
        glDeleteLists(pair.second, 1);
    }
    m_displayLists.clear();
}

GLuint ResourceManager::generateDisplayListId()
{
    return glGenLists(1);
}

// Example usage in refactored rendering code:
/*
void CowBody::renderLeg(GLfloat x, GLfloat y)
{
    QuadricRenderer quad;

    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Render leg
    setMaterial(COW_BROWN);
    quad.cylinder(Cow::LEG_RADIUS, Cow::LEG_RADIUS, Cow::LEG_HEIGHT);

    // Render hoof
    setMaterial(DARK_GRAY);
    quad.cylinder(Cow::LEG_RADIUS + 0.00002f, Cow::LEG_RADIUS + 0.00002f, Cow::HOOF_HEIGHT);

    glPopMatrix();
}

// Using display lists for static geometry:
void TreeRenderer::render(const WcPt3D& position)
{
    static const std::string TREE_LIST = "tree_geometry";

    glPushMatrix();
    glTranslatef(position.getX(), position.getY(), position.getZ());

    DisplayListBuilder::execute(TREE_LIST);

    glPopMatrix();
}

void TreeRenderer::initialize()
{
    DisplayListBuilder::build("tree_geometry", []() {
        QuadricRenderer quad;

        // Tree stem
        setMaterial(DARK_BROWN);
        glutSolidCone(TREE_STEM_RADIUS, TREE_STEM_HEIGHT, 10, 10);

        // Leaves...
    });
}
*/