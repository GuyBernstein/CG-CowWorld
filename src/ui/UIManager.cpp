//==============================================================================
// File: ui/UIManager.cpp
// Purpose: UI management implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "ui/UIManager.h"
#include "ui/Button.h"
#include "graphics/Renderer.h"
#include "core/Application.h"
#include "core/Window.h"
#include "core/Input.h"

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

namespace CowGL {
    UIManager::UIManager()
        : m_showHelpMenu(false)
          , m_showLightingMenu(false)
          , m_globalAmbient(0.75f)
          , m_sunIntensity(1.0f)
          , m_sunAngle(45.0f) {
    }

    UIManager::~UIManager() = default;

    void UIManager::initialize() {
        createTopMenu();
    }

    void UIManager::update(float deltaTime) {
        // Handle input for menus
        Input *input = Application::getInstance()->getInput();

        if (input->isKeyJustPressed('\r')) {
            // Enter key
            if (m_showHelpMenu) hideHelpMenu();
            if (m_showLightingMenu) hideLightingMenu();
        }

        if (input->isKeyJustPressed('h')) {
            toggleHelpMenu();
        }

        // Update buttons
        for (auto &button: m_topMenuButtons) {
            button->update();
        }
    }

    void UIManager::render(Renderer *renderer) {
        renderTopMenu();

        if (m_showHelpMenu) {
            renderHelpMenu();
        }

        if (m_showLightingMenu) {
            renderLightingMenu();
        }
    }

    void UIManager::createTopMenu() {
        auto exitButton = std::make_shared<Button>("Exit", 0, 0, 45, 30);
        exitButton->setCallback([]() { exit(0); });
        m_topMenuButtons.push_back(exitButton);

        auto helpButton = std::make_shared<Button>("Help", 45, 0, 50, 30);
        helpButton->setCallback([this]() { toggleHelpMenu(); });
        m_topMenuButtons.push_back(helpButton);

        auto lightingButton = std::make_shared<Button>("Adjust Lighting", 95, 0, 135, 30);
        lightingButton->setCallback([this]() { toggleLightingMenu(); });
        m_topMenuButtons.push_back(lightingButton);
    }

    void UIManager::renderTopMenu() {
        auto window = Application::getInstance()->getWindow();
        int width = window->getWidth();
        int height = window->getHeight();

        // Setup viewport for UI
        glViewport(0, height - 40, width, 40);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, 40);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw background
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, 40);
        glVertex2f(0, 40);
        glEnd();

        // Draw frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(1, 1);
        glVertex2f(width - 1, 1);
        glVertex2f(width - 1, 39);
        glVertex2f(1, 39);
        glEnd();

        // Render buttons
        for (auto &button: m_topMenuButtons) {
            button->render();
        }
    }

    void UIManager::renderHelpMenu() {
        auto window = Application::getInstance()->getWindow();
        int width = window->getWidth();
        int height = window->getHeight();

        int menuWidth = 400;
        int menuHeight = 350;
        int x = (width - menuWidth) / 2;
        int y = (height - menuHeight) / 2;

        glViewport(x, y, menuWidth, menuHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, menuWidth, 0, menuHeight);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Background
        glColor3f(0.8f, 0.8f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(menuWidth, 0);
        glVertex2f(menuWidth, menuHeight);
        glVertex2f(0, menuHeight);
        glEnd();

        // Frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(7.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(1, 1);
        glVertex2f(menuWidth - 1, 1);
        glVertex2f(menuWidth - 1, menuHeight - 1);
        glVertex2f(1, menuHeight - 1);
        glEnd();

        // Title
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(90, menuHeight - 40);
        const char *title = "Help Menu - CowGL";
        for (const char *c = title; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        // Help text
        const char *helpText[] = {
            "*** MAKE SURE KEYBOARD LANGUAGE IS ENGLISH ***",
            "Cow Movement: W,A,S,D keys",
            "Head/Tail Movement: I,J,K,L keys",
            "Toggle tail control: T key",
            "Toggle head control: H key",
            "Switch camera view: V key",
            "Third-person camera: Numpad 2,4,6,8",
            "Zoom: Numpad 1 (in), 7 (out)",
            "Reset camera/head/tail: Numpad 5",
            "Exit: Q key",
            "",
            "Press ENTER to close this window"
        };

        int yPos = menuHeight - 70;
        for (const char *line: helpText) {
            glRasterPos2f(10, yPos);
            for (const char *c = line; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
            }
            yPos -= 20;
        }
    }

    void UIManager::renderLightingMenu() {
        auto window = Application::getInstance()->getWindow();
        int width = window->getWidth();
        int height = window->getHeight();

        int menuWidth = 400;
        int menuHeight = 350;
        int x = (width - menuWidth) / 2;
        int y = (height - menuHeight) / 2;

        glViewport(x, y, menuWidth, menuHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, menuWidth, 0, menuHeight);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Background
        glColor3f(0.8f, 0.8f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(menuWidth, 0);
        glVertex2f(menuWidth, menuHeight);
        glVertex2f(0, menuHeight);
        glEnd();

        // Frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(7.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(1, 1);
        glVertex2f(menuWidth - 1, 1);
        glVertex2f(menuWidth - 1, menuHeight - 1);
        glVertex2f(1, menuHeight - 1);
        glEnd();

        // Title
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(50, menuHeight - 40);
        const char *title = "Adjust Lighting Menu - CowGL";
        for (const char *c = title; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        // Lighting controls text
        glRasterPos2f(50, 250);
        const char *ambientText = "Ambient Light: Use +/- keys";
        for (const char *c = ambientText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(50, 200);
        const char *sunText = "Sun Intensity: Use [/] keys";
        for (const char *c = sunText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(50, 150);
        const char *angleText = "Sun Angle: Use <,> keys";
        for (const char *c = angleText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(40, 50);
        const char *footer = "Press ENTER to close this window";
        for (const char *c = footer; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    void UIManager::showHelpMenu() {
        m_showHelpMenu = true;
        m_showLightingMenu = false;
    }

    void UIManager::hideHelpMenu() {
        m_showHelpMenu = false;
    }

    void UIManager::toggleHelpMenu() {
        m_showHelpMenu = !m_showHelpMenu;
        if (m_showHelpMenu) {
            m_showLightingMenu = false;
        }
    }

    void UIManager::showLightingMenu() {
        m_showLightingMenu = true;
        m_showHelpMenu = false;
    }

    void UIManager::hideLightingMenu() {
        m_showLightingMenu = false;
    }

    void UIManager::toggleLightingMenu() {
        m_showLightingMenu = !m_showLightingMenu;
        if (m_showLightingMenu) {
            m_showHelpMenu = false;
        }
    }
} // namespace CowGL
