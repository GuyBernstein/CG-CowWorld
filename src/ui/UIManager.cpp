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
#include "scene/Scene.h"
#include "graphics/Light.h"

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "entities/Cow.h"

namespace CowGL {
    UIManager::UIManager()
        : m_showHelpMenu(false)
          , m_showLightingMenu(false)
          , m_globalAmbient(0.3f)
          , m_sunIntensity(1.0f)
          , m_sunAngle(45.0f) {
    }

    UIManager::~UIManager() = default;

    void UIManager::initialize() {
        createTopMenu();
    }

    void UIManager::update(float deltaTime) {
        Input *input = Application::getInstance()->getInput();

        // Check for help menu toggle ONLY if not in head control mode
        if (!m_showHelpMenu && !m_showLightingMenu) {
            // Only process H key for help if cow is not in head control mode
            auto scene = Application::getInstance()->getScene();
            auto cowObj = scene->findGameObject("MainCow");
            if (cowObj) {
                auto cow = std::dynamic_pointer_cast<Cow>(cowObj);
                if (!cow || cow->getControlMode() != Cow::ControlMode::Head) {
                    if (input->isKeyJustPressed('h') || input->isKeyJustPressed('H')) {
                        toggleHelpMenu();
                    }
                }
            }
        }

        if (input->isKeyJustPressed('\r')) {
            if (m_showHelpMenu) hideHelpMenu();
            if (m_showLightingMenu) hideLightingMenu();
        }

        if (input->isKeyJustPressed('h') || input->isKeyJustPressed('H')) {
            toggleHelpMenu();
        }

        // Handle lighting adjustments when menu is open
        if (m_showLightingMenu) {
            if (input->isKeyPressed('+') || input->isKeyPressed('=')) {
                m_globalAmbient = std::min(1.0f, m_globalAmbient + 0.01f);
                updateLighting();
            }
            if (input->isKeyPressed('-') || input->isKeyPressed('_')) {
                m_globalAmbient = std::max(0.0f, m_globalAmbient - 0.01f);
                updateLighting();
            }
            if (input->isKeyPressed('[')) {
                m_sunIntensity = std::max(0.0f, m_sunIntensity - 0.01f);
                updateLighting();
            }
            if (input->isKeyPressed(']')) {
                m_sunIntensity = std::min(2.0f, m_sunIntensity + 0.01f);
                updateLighting();
            }
            if (input->isKeyPressed('<') || input->isKeyPressed(',')) {
                m_sunAngle = std::max(-90.0f, m_sunAngle - 1.0f);
                updateLighting();
            }
            if (input->isKeyPressed('>') || input->isKeyPressed('.')) {
                m_sunAngle = std::min(90.0f, m_sunAngle + 1.0f);
                updateLighting();
            }
        }

        // Update buttons
        for (auto &button: m_topMenuButtons) {
            button->update();
        }
    }

    void UIManager::render(Renderer *renderer) {
        // Save current OpenGL state
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // Disable depth test and lighting for UI
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        renderTopMenu();

        if (m_showHelpMenu) {
            renderHelpMenu();
        }

        if (m_showLightingMenu) {
            renderLightingMenu();
        }

        // Restore OpenGL state
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
    }

    void UIManager::createTopMenu() {
        auto window = Application::getInstance()->getWindow();
        int width = window->getWidth();
        int height = window->getHeight();

        // Position buttons on the right side of screen, near the top
        int buttonX = width - 150; // 150 pixels from right edge

        auto exitButton = std::make_shared<Button>("Exit", buttonX, height - 50, 120, 35);
        exitButton->setCallback([]() { exit(0); });
        m_topMenuButtons.push_back(exitButton);

        auto helpButton = std::make_shared<Button>("Help", buttonX, height - 95, 120, 35);
        helpButton->setCallback([this]() { toggleHelpMenu(); });
        m_topMenuButtons.push_back(helpButton);

        auto lightingButton = std::make_shared<Button>("Lighting", buttonX, height - 140, 120, 35);
        lightingButton->setCallback([this]() { toggleLightingMenu(); });
        m_topMenuButtons.push_back(lightingButton);
    }

    void UIManager::renderTopMenu() {
        // Remove the redundant button creation - just render existing buttons
        for (auto &button: m_topMenuButtons) {
            button->render();
        }
    }

    void UIManager::updateButtonPositions() {
        auto window = Application::getInstance()->getWindow();
        int width = window->getWidth();
        int height = window->getHeight();
        int buttonX = width - 150;

        if (m_topMenuButtons.size() >= 3) {
            m_topMenuButtons[0]->setPosition(buttonX, height - 50); // Exit
            m_topMenuButtons[1]->setPosition(buttonX, height - 95); // Help
            m_topMenuButtons[2]->setPosition(buttonX, height - 140); // Lighting
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

        // Setup viewport and projection for centered menu
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Background with transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
        glEnd();

        // Menu background
        glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + menuWidth, y);
        glVertex2f(x + menuWidth, y + menuHeight);
        glVertex2f(x, y + menuHeight);
        glEnd();

        // Frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + 1, y + 1);
        glVertex2f(x + menuWidth - 1, y + 1);
        glVertex2f(x + menuWidth - 1, y + menuHeight - 1);
        glVertex2f(x + 1, y + menuHeight - 1);
        glEnd();

        glDisable(GL_BLEND);

        // Title
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(x + 90, y + menuHeight - 40);
        const char *title = "Help Menu - CowGL";
        for (const char *c = title; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        const char *helpText[] = {
            "*** MAKE SURE KEYBOARD LANGUAGE IS ENGLISH ***",
            "Cow Movement: W,A,S,D keys",
            "Control Modes:",
            "  M - Movement mode (default)",
            "  H - Head control mode",
            "  T - Tail control mode",
            "Head/Tail Movement: I,J,K,L keys (after pressing H or T)",
            "Toggle Camera View: V key",
            "Reset Head/Tail: R key",
            "Quit: Q key",
            "",
            "Camera controls (third person):",
            "  Numpad 8,2,4,6 - Rotate camera",
            "  Numpad 1,7 - Zoom in/out",
            "  Numpad 5 - Reset camera",
            "",
            "Press ENTER to close this window"
        };

        int yPos = y + menuHeight - 70;
        for (const char *line: helpText) {
            glRasterPos2f(x + 10, yPos);
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

        // Setup viewport and projection for centered menu
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Background with transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
        glEnd();

        // Menu background
        glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + menuWidth, y);
        glVertex2f(x + menuWidth, y + menuHeight);
        glVertex2f(x, y + menuHeight);
        glEnd();

        // Frame
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + 1, y + 1);
        glVertex2f(x + menuWidth - 1, y + 1);
        glVertex2f(x + menuWidth - 1, y + menuHeight - 1);
        glVertex2f(x + 1, y + menuHeight - 1);
        glEnd();

        glDisable(GL_BLEND);

        // Title
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(x + 50, y + menuHeight - 40);
        const char *title = "Adjust Lighting Menu - CowGL";
        for (const char *c = title; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        // Lighting controls text with current values
        char buffer[100];

        glRasterPos2f(x + 50, y + 250);
        sprintf(buffer, "Ambient Light (%.2f): Use +/- keys", m_globalAmbient);
        for (const char *c = buffer; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(x + 50, y + 200);
        sprintf(buffer, "Sun Intensity (%.2f): Use [/] keys", m_sunIntensity);
        for (const char *c = buffer; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(x + 50, y + 150);
        sprintf(buffer, "Sun Angle (%.1f deg): Use <,> keys", m_sunAngle);
        for (const char *c = buffer; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glRasterPos2f(x + 40, y + 50);
        const char *footer = "Press ENTER to close this window";
        for (const char *c = footer; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    void UIManager::updateLighting() {
        // Update global ambient
        GLfloat globalAmbient[] = {m_globalAmbient, m_globalAmbient, m_globalAmbient, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        // Update sun light
        float angleRad = glm::radians(m_sunAngle);
        GLfloat lightPosition[] = {50.0f * std::cos(angleRad), 50.0f * std::sin(angleRad), 100.0f, 0.0f};
        GLfloat lightDiffuse[] = {m_sunIntensity, m_sunIntensity, m_sunIntensity, 1.0f};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
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
