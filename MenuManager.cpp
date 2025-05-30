//
// Created by Guy Bernstein on 29/05/2025.
//

#include "MenuManager.h"

MenuManager& MenuManager::getInstance()
{
    static MenuManager instance;
    return instance;
}

void MenuManager::registerMenu(const std::string& name, std::unique_ptr<MenuBase> menu)
{
    m_menus[name] = std::move(menu);
}

MenuBase* MenuManager::getMenu(const std::string& name)
{
    auto it = m_menus.find(name);
    return (it != m_menus.end()) ? it->second.get() : nullptr;
}

void MenuManager::renderAll() const {
    for (const auto& pair : m_menus)
    {
        if (pair.second->isVisible())
        {
            pair.second->render();
        }
    }
}

void MenuManager::handleMouse(int button, const int state, const int x, const int y) const {
    for (const auto& pair : m_menus)
    {
        if (pair.second->isVisible())
        {
            pair.second->handleMouse(button, state, x, y);
        }
    }
}

void MenuManager::handleKeyboard(const unsigned char key, const int x, const int y) const {
    for (const auto& pair : m_menus)
    {
        if (pair.second->isVisible())
        {
            pair.second->handleKeyboard(key, x, y);
        }
    }
}

void MenuManager::hideAll() const {
    for (const auto& pair : m_menus)
    {
        pair.second->hide();
    }
}

void MenuManager::showOnly(const std::string& name)
{
    hideAll();
    if (auto* menu = getMenu(name))
    {
        menu->show();
    }
}