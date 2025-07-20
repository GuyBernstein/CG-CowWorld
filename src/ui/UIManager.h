//==============================================================================
// File: ui/UIManager.h
// Purpose: UI management system
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef UIMANAGER_H
#define UIMANAGER_H


#include <vector>
#include <memory>
#include <functional>

namespace CowGL {
    class Button;
    class Renderer;

    class UIManager {
    public:
        UIManager();

        ~UIManager();

        void initialize();

        void update(float deltaTime);

        void render(Renderer *renderer);

        void showHelpMenu();

        void hideHelpMenu();

        void toggleHelpMenu();

        void showLightingMenu();

        void hideLightingMenu();

        void toggleLightingMenu();

    private:
        void createTopMenu();

        void renderTopMenu();

        void renderHelpMenu();

        void renderLightingMenu();

        void updateLighting();

        std::vector<std::shared_ptr<Button> > m_topMenuButtons;

        bool m_showHelpMenu;
        bool m_showLightingMenu;

        float m_globalAmbient;
        float m_sunIntensity;
        float m_sunAngle;
    };
} // namespace CowGL


#endif //UIMANAGER_H
