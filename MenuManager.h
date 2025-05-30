//
// Created by Guy Bernstein on 29/05/2025.
// Centralized menu management system.

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "MenuBase.h"

class MenuManager
{
public:
    static MenuManager& getInstance();

    // Menu registration and access
    void registerMenu(const std::string& name, std::unique_ptr<MenuBase> menu);
    MenuBase* getMenu(const std::string& name);

    // Render all visible menus
    void renderAll() const;

    // Event forwarding
    void handleMouse(int button, int state, int x, int y) const;
    void handleKeyboard(unsigned char key, int x, int y) const;

    // Utility methods
    void hideAll() const;
    void showOnly(const std::string& name);

private:
    MenuManager() = default;
    std::unordered_map<std::string, std::unique_ptr<MenuBase>> m_menus;
};
#endif //MENUMANAGER_H
