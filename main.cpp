
#include "Constants.h"
#include "ResourceManager.h"
#include "MenuManager.h"
#include "SceneManager.h"
#include "CowController.h"
#include "HelpMenu.h"
#include "House.h"
#include <memory>

// Global objects (minimized)
std::unique_ptr<CowController> g_cow;
std::unique_ptr<SceneManager> g_scene;

void initializeApplication()
{
    // Initialize resource manager
    ResourceManager::getInstance();

    // Create cow at center
    g_cow = std::make_unique<CowController>(WcPt3D(0, 0, 0));

    // Initialize scene
    g_scene = std::make_unique<SceneManager>();
    g_scene->addObject("house", std::make_unique<House>(WcPt3D(-10, 0, 0)));
    // g_scene->addObject("shed", std::make_unique<Shed>(WcPt3D(0, 8, 0), 180.0f));

    // Setup menus
    auto& menuManager = MenuManager::getInstance();
    menuManager.registerMenu("help", std::make_unique<HelpMenu>());
    // menuManager.registerMenu("lighting", std::make_unique<LightingMenu>());

    // // Setup display lists for static geometry
    // initializeStaticGeometry();
}

void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render scene
    // g_scene->render();
    g_cow->render();

    // Render UI
    MenuManager::getInstance().renderAll();

    glFlush();
}

void keyboardCallback(unsigned char key, int x, int y)
{
    // Menu handling first
    MenuManager::getInstance().handleKeyboard(key, x, y);

    // Then game controls
    switch (std::tolower(key))
    {
        // Movement
        case 'w': g_cow->moveForward(); break;
        case 's': g_cow->moveBackward(); break;
        case 'a': g_cow->turnLeft(); break;
        case 'd': g_cow->turnRight(); break;

        // // Camera
        // case 'v': g_cow->getCamera().toggleMode(); break;

        // Menus
        case 'h': MenuManager::getInstance().showOnly("help"); break;
        case 'l': MenuManager::getInstance().showOnly("lighting"); break;
    }

    glutPostRedisplay();
}

void cleanup()
{
    // Cleanup is automatic through destructors
    g_cow.reset();
    g_scene.reset();
    ResourceManager::getInstance().cleanup();
}