
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
        default: ;
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

void mouseCallback(int button, int state, int x, int y)
{
    MenuManager::getInstance().handleMouse(button, state, x, y);
    glutPostRedisplay();
}

void reshapeCallback(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, Camera::NEAR_PLANE, Camera::FAR_PLANE);

    glMatrixMode(GL_MODELVIEW);
}

void timerCallback(int value)
{
    glutPostRedisplay();
    glutTimerFunc(static_cast<unsigned int>(Window::REFRESH_RATE_MS), timerCallback, 0);
}

void initializeOpenGL()
{
    // Set clear color to light blue (sky)
    glClearColor(RGB_COLOR_SKY_BLUE, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable smooth shading
    glShadeModel(GL_SMOOTH);

    // Setup lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    constexpr GLfloat lightPosition[] = {50.0f, 50.0f, 50.0f, 1.0f};
    constexpr GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    constexpr GLfloat lightDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    constexpr GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Set up initial camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, -10.0, 5.0,  // Eye position
              0.0, 0.0, 0.0,    // Look at
              0.0, 0.0, 1.0);   // Up vector
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Window::INIT_WIDTH, Window::INIT_HEIGHT);
    glutInitWindowPosition(Window::INIT_X, Window::INIT_Y);
    glutCreateWindow("CowGL - OpenGL Cow Simulator");

    // Initialize OpenGL
    initializeOpenGL();

    // Initialize application
    initializeApplication();

    // Register callbacks
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutTimerFunc(static_cast<unsigned int>(Window::REFRESH_RATE_MS), timerCallback, 0);

    // Start main loop
    glutMainLoop();

    // Cleanup (never reached in GLUT)
    cleanup();

    return 0;
}