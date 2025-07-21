//==============================================================================
// File: entities/Environment.cpp
// Purpose: Environment objects implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "entities/Environment.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "core/Application.h"
#include "ui/UIManager.h"

namespace CowGL {
    namespace Environment {
        namespace {
            // Colors
            const GLfloat GRASS_GREEN[] = {0.18f, 0.55f, 0.18f, 1.0f};
            const GLfloat CREAM[] = {1.0f, 0.99f, 0.89f, 1.0f};
            const GLfloat CLAY[] = {0.71f, 0.13f, 0.13f, 1.0f};
            const GLfloat BROWN[] = {0.55f, 0.27f, 0.07f, 1.0f};
            const GLfloat LIGHT_BLUE[] = {0.62f, 0.82f, 0.88f, 1.0f};
            const GLfloat MEDIUM_GRAY[] = {0.5f, 0.5f, 0.5f, 1.0f};
            const GLfloat LIGHT_GRAY[] = {0.8f, 0.8f, 0.8f, 1.0f};
            const GLfloat DARK_BROWN[] = {0.31f, 0.21f, 0.14f, 1.0f};
            const GLfloat DARK_GREEN[] = {0.1f, 0.29f, 0.11f, 1.0f};
            const GLfloat FOREST_GREEN[] = {0.13f, 0.55f, 0.13f, 1.0f};
            const GLfloat WATER_BLUE[] = {0.11f, 0.58f, 0.88f, 1.0f};
            const GLfloat BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};
            const GLfloat WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};
            const GLfloat METALLIC_GRAY[] = {0.7f, 0.7f, 0.75f, 1.0f};
        }

        // Ground
        Ground::Ground() : GameObject("Ground") {
        }

        void Ground::onRender() {
            glEnable(GL_LIGHTING);

            // Get lighting values for ground color variation
            auto app = Application::getInstance();
            auto uiManager = app->getUIManager();
            float globalAmbientValue = uiManager ? uiManager->getGlobalAmbient() : 0.3f;

            // Vary grass color slightly based on ambient light
            float grassIntensity = 0.7f + 0.3f * globalAmbientValue;
            GLfloat dynamicGrassGreen[] = {
                0.18f * grassIntensity,
                0.55f * grassIntensity,
                0.18f * grassIntensity,
                1.0f
            };

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dynamicGrassGreen);
            glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);

            // Add specular to make sun angle changes visible
            GLfloat groundSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f};
            glMaterialfv(GL_FRONT, GL_SPECULAR, groundSpecular);
            glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-100.0f, -100.0f, 0.0f);
            glVertex3f(100.0f, -100.0f, 0.0f);
            glVertex3f(100.0f, 100.0f, 0.0f);
            glVertex3f(-100.0f, 100.0f, 0.0f);
            glEnd();

            glDisable(GL_LIGHTING);
        }

        // House
        House::House() : GameObject("House") {
        }

        void House::onRender() {
            glEnable(GL_LIGHTING);

            // Walls
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, CREAM);
            glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
            glMaterialfv(GL_FRONT, GL_SPECULAR, BLACK);

            // Front wall
            glBegin(GL_QUADS);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(2.5f, -3.5f, 0.0f);
            glVertex3f(-2.5f, -3.5f, 0.0f);
            glVertex3f(-2.5f, -3.5f, 3.25f);
            glVertex3f(2.5f, -3.5f, 3.25f);
            glEnd();

            // Back wall
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-2.5f, 3.5f, 0.0f);
            glVertex3f(2.5f, 3.5f, 0.0f);
            glVertex3f(2.5f, 3.5f, 3.25f);
            glVertex3f(-2.5f, 3.5f, 3.25f);
            glEnd();

            // Right wall
            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.5f, -3.5f, 0.0f);
            glVertex3f(2.5f, 3.5f, 0.0f);
            glVertex3f(2.5f, 3.5f, 3.25f);
            glVertex3f(2.5f, -3.5f, 3.25f);
            glEnd();

            // Left wall
            glBegin(GL_QUADS);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-2.5f, -3.5f, 0.0f);
            glVertex3f(-2.5f, 3.5f, 0.0f);
            glVertex3f(-2.5f, 3.5f, 3.25f);
            glVertex3f(-2.5f, -3.5f, 3.25f);
            glEnd();

            // Roof
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, CLAY);

            glBegin(GL_TRIANGLES);
            // Front
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(-2.5f, -3.5f, 3.25f);
            glVertex3f(2.5f, -3.5f, 3.25f);
            glVertex3f(0.0f, -3.5f, 5.25f);

            // Back
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(2.5f, 3.5f, 3.25f);
            glVertex3f(-2.5f, 3.5f, 3.25f);
            glVertex3f(0.0f, 3.5f, 5.25f);
            glEnd();

            // Roof sides
            glBegin(GL_QUADS);
            // Left side
            glNormal3f(-0.894f, 0.0f, 0.447f);
            glVertex3f(-2.5f, -3.5f, 3.25f);
            glVertex3f(-2.5f, 3.5f, 3.25f);
            glVertex3f(0.0f, 3.5f, 5.25f);
            glVertex3f(0.0f, -3.5f, 5.25f);

            // Right side
            glNormal3f(0.894f, 0.0f, 0.447f);
            glVertex3f(2.5f, -3.5f, 3.25f);
            glVertex3f(2.5f, 3.5f, 3.25f);
            glVertex3f(0.0f, 3.5f, 5.25f);
            glVertex3f(0.0f, -3.5f, 5.25f);
            glEnd();

            // Door
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BROWN);
            glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
            glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.51f, 0.75f, 0.0f);
            glVertex3f(2.51f, -0.75f, 0.0f);
            glVertex3f(2.51f, -0.75f, 2.25f);
            glVertex3f(2.51f, 0.75f, 2.25f);
            glEnd();

            // Windows
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LIGHT_BLUE);
            glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
            glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

            // Front windows
            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.51f, 1.75f, 1.0f);
            glVertex3f(2.51f, 2.5f, 1.0f);
            glVertex3f(2.51f, 2.5f, 2.5f);
            glVertex3f(2.51f, 1.75f, 2.5f);
            glEnd();

            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.51f, -1.75f, 1.0f);
            glVertex3f(2.51f, -2.5f, 1.0f);
            glVertex3f(2.51f, -2.5f, 2.5f);
            glVertex3f(2.51f, -1.75f, 2.5f);
            glEnd();

            glDisable(GL_LIGHTING);
        }

        // Shed
        Shed::Shed() : GameObject("Shed") {
        }

        void Shed::onRender() {
            glEnable(GL_LIGHTING);

            // Get current sun intensity for dynamic metallic reflection
            auto app = Application::getInstance();
            auto uiManager = app->getUIManager();
            float sunIntensity = uiManager ? uiManager->getSunIntensity() : 1.0f;

            // Metallic walls with dynamic properties
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, METALLIC_GRAY);
            glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);

            // Strong specular reflection that varies with sun intensity
            GLfloat dynamicSpecular[] = {
                0.8f * sunIntensity,
                0.8f * sunIntensity,
                0.8f * sunIntensity,
                1.0f
            };
            glMaterialfv(GL_FRONT, GL_SPECULAR, dynamicSpecular);
            glMaterialf(GL_FRONT, GL_SHININESS, 90.0f); // Very shiny metal

            // Front wall
            glBegin(GL_QUADS);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(2.0f, -2.5f, 0.0f);
            glVertex3f(-2.0f, -2.5f, 0.0f);
            glVertex3f(-2.0f, -2.5f, 2.5f);
            glVertex3f(2.0f, -2.5f, 2.5f);
            glEnd();

            // Back wall
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-2.0f, 2.5f, 0.0f);
            glVertex3f(2.0f, 2.5f, 0.0f);
            glVertex3f(2.0f, 2.5f, 2.5f);
            glVertex3f(-2.0f, 2.5f, 2.5f);
            glEnd();

            // Right wall
            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.0f, -2.5f, 0.0f);
            glVertex3f(2.0f, 2.5f, 0.0f);
            glVertex3f(2.0f, 2.5f, 2.5f);
            glVertex3f(2.0f, -2.5f, 2.5f);
            glEnd();

            // Left wall
            glBegin(GL_QUADS);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-2.0f, -2.5f, 0.0f);
            glVertex3f(-2.0f, 2.5f, 0.0f);
            glVertex3f(-2.0f, 2.5f, 2.5f);
            glVertex3f(-2.0f, -2.5f, 2.5f);
            glEnd();

            // Flat metal roof
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MEDIUM_GRAY);
            GLfloat roofSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Maximum specular
            glMaterialfv(GL_FRONT, GL_SPECULAR, roofSpecular);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);  // Mirror-like

            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-2.2f, -2.7f, 2.5f);
            glVertex3f(2.2f, -2.7f, 2.5f);
            glVertex3f(2.2f, 2.7f, 2.5f);
            glVertex3f(-2.2f, 2.7f, 2.5f);
            glEnd();

            // Shed door (metallic sliding door)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LIGHT_GRAY);
            glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
            glMaterialf(GL_FRONT, GL_SHININESS, 60.0f);

            glBegin(GL_QUADS);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(2.01f, 1.0f, 0.0f);
            glVertex3f(2.01f, -1.0f, 0.0f);
            glVertex3f(2.01f, -1.0f, 2.0f);
            glVertex3f(2.01f, 1.0f, 2.0f);
            glEnd();

            glDisable(GL_LIGHTING);
        }

        // Tree
        Tree::Tree()
            : GameObject("Tree") {
        }

        void Tree::onRender() {
            glEnable(GL_LIGHTING);

            GLUquadric *quadric = gluNewQuadric();

            // Trunk
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, DARK_BROWN);
            glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
            glMaterialfv(GL_FRONT, GL_SPECULAR, BLACK);

            glutSolidCone(0.5f, 8.0f, 10, 10);

            // Leaves (3 layers)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, DARK_GREEN);

            glTranslatef(0.0f, 0.0f, 2.0f);
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            gluDisk(quadric, 0.0f, 1.5f, 25, 25);
            glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(1.5f, 2.5f, 25, 25);

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, FOREST_GREEN);

            glTranslatef(0.0f, 0.0f, 2.0f);
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            gluDisk(quadric, 0.0f, 1.25f, 25, 25);
            glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(1.25f, 2.5f, 25, 25);

            glTranslatef(0.0f, 0.0f, 2.0f);
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            gluDisk(quadric, 0.0f, 1.0f, 25, 25);
            glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(1.0f, 2.5f, 25, 25);

            gluDeleteQuadric(quadric);
            glDisable(GL_LIGHTING);
        }

        // WaterTank
        WaterTank::WaterTank()
            : GameObject("WaterTank") {
        }

        void WaterTank::onRender() {
            glEnable(GL_LIGHTING);

            // Tank walls
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MEDIUM_GRAY);
            glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
            glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
            glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);

            // Simple box for water tank
            glBegin(GL_QUADS);
            // Front
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.5f, -1.5f, 0.0f);
            glVertex3f(-0.5f, -1.5f, 0.0f);
            glVertex3f(-0.5f, -1.5f, 0.5f);
            glVertex3f(0.5f, -1.5f, 0.5f);

            // Back
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f, 1.5f, 0.0f);
            glVertex3f(0.5f, 1.5f, 0.0f);
            glVertex3f(0.5f, 1.5f, 0.5f);
            glVertex3f(-0.5f, 1.5f, 0.5f);

            // Left
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, -1.5f, 0.0f);
            glVertex3f(-0.5f, 1.5f, 0.0f);
            glVertex3f(-0.5f, 1.5f, 0.5f);
            glVertex3f(-0.5f, -1.5f, 0.5f);

            // Right
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, -1.5f, 0.0f);
            glVertex3f(0.5f, 1.5f, 0.0f);
            glVertex3f(0.5f, 1.5f, 0.5f);
            glVertex3f(0.5f, -1.5f, 0.5f);
            glEnd();

            // Water
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WATER_BLUE);
            glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
            glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, -1.5f, 0.35f);
            glVertex3f(0.5f, -1.5f, 0.35f);
            glVertex3f(0.5f, 1.5f, 0.35f);
            glVertex3f(-0.5f, 1.5f, 0.35f);
            glEnd();

            glDisable(GL_LIGHTING);
        }
    } // namespace Environment
} // namespace CowGL
