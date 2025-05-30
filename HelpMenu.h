//
// Created by Guy Bernstein on 29/05/2025.
// Help menu implementation using MenuBase

#ifndef HELPMENU_H
#define HELPMENU_H

#include "MenuBase.h"
#include <vector>
#include <string>

class HelpMenu : public MenuBase
{
public:
    HelpMenu();

    void handleKeyboard(unsigned char key, int x, int y) override;

protected:
    void renderContent() override;

private:
    std::vector<std::string> m_helpLines;
    static constexpr GLfloat LINE_SPACING = 20.0f;
    static constexpr GLfloat TEXT_START_Y = 275.0f;
    static constexpr GLfloat TEXT_START_X = 10.0f;
};


#endif //HELPMENU_H
