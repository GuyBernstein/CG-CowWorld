/*****************************************************************//**
 * \file   Main.cpp
 * \brief  CowGL is my solution for the final project in
 *         Computer Graphics (20562) course. It is an interactive
 *         rendering of a cow. The cow is located in a world which
 *         has a few objects in it (trees, house, etc.) and a lighting
 *         model. The user can control the movement of the cow, camera
 *         positioning and the lighting of the scene.
 * 
 * *** BUILD INSTRUCTIONS (VS2019/VS2022 Windows 10/11) ***
 * 1. Setup OpenGL: https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/.
 * 2. Select x86 Debug configuration.
 * 3. Build the solution (ctrl + shift + B).
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "MainScene.h"
#include "Menus.h"

/******************************
*          DEFINES            *
*******************************/
#define WINDOW_INIT_POS  100, 100
#define WINDOW_INIT_SIZE 720, 480
#define WINDOW_TITLE     "CG GowGL"
#define WORLD_COORD      0.0, 100.0, 0.0, 100.0  // left right bottom top
#define REFRESH_PERIOD_MS  16.6666666666666666667

/******************************
*     FUNCTION PROTOTYPES     *
*******************************/
void createWindow(int argc, char** argv);
void registerCallbacks(void);
void displayCallback(void);
void mouseCallback(int button, int state, int x, int y);
void keyboardCallback(unsigned char key, int x, int y);
void timerCallback(int value);
void resetProjectionAndModelviewMatrices(void);
int main(int argc, char** argv);

/******************************
*     FUNCTION DEFINITIONS    *
*******************************/
void createWindow(int argc, char** argv)
{
    /* Create the window */
    glutInit(&argc, argv);                        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowPosition(WINDOW_INIT_POS);      // Set top-left window position
    glutInitWindowSize(WINDOW_INIT_SIZE);         // Set window width and height
    glutCreateWindow(WINDOW_TITLE);               // Create window

    /* Initialize the window */
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Set window color to white
}


void registerCallbacks(void)
{
    glutDisplayFunc(displayCallback);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);
    glutTimerFunc(0.0, timerCallback, 0);
}


void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    renderTopMenu();
    renderMainScene();
    renderHelpMenu();
    renderAdjustLightingMenu();
    
    glFlush();
}


void mouseCallback(int button, int state, int x, int y)
{
    handleMouseEventTopMenu(button, state, x, y);
    handleMouseEventAdjustLightingMenu(button, state, x, y);
    glutPostRedisplay();
}


void keyboardCallback(unsigned char key, int x, int y)
{
    handleKeyboardEventHelpMenu(key, x, y);
    handleKeyboardEventAdjustLightingMenu(key, x, y);
    handleKeyboardEventMainScene(key, x, y);
    glutPostRedisplay();
}


void timerCallback(int value)
{
    glutPostRedisplay();
    glutTimerFunc(static_cast<unsigned int>(REFRESH_PERIOD_MS), timerCallback, 0);
}


void resetProjectionAndModelviewMatrices(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}


int main(int argc, char** argv)
{
    /* Initialize OpenGL */
    createWindow(argc, argv);  // Create the display-window
    registerCallbacks();       // Assign callback functions for events
    glutMainLoop();            // Display everything and wait
    return 0;
}
