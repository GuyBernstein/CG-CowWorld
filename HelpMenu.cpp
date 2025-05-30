//
// Created by Guy Bernstein on 29/05/2025.
//

#include "HelpMenu.h"
#include "Constants.h"

HelpMenu::HelpMenu()
    : MenuBase(Menu::HELP_WIDTH, Menu::HELP_HEIGHT, "Help Menu - CowGL")
{
    // Initialize help text
    m_helpLines = {
        "*** MAKE SURE KEYBOARD LANGUAGE IS ENGLISH ***",
        "Cow Movement: W,A,S,D keys.",
        "Head/Tail Movement: I,J,K,L keys.",
        "Toggle tail movement: T key.",
        "Toggle head movement : H key.",
        "Switch between first-person and third-person cameras: V key.",
        "Move third-person camera: 8, 4, 2, 6 keys",
        "Zoom in third-person camera: 1",
        "Zoom out third-person camera: 7",
        "Reset head, tail and third-person camera: 5 (NUMPAD)",
        "Use the left mouse button to click on menu buttons."
    };
}

void HelpMenu::handleKeyboard(unsigned char key, int x, int y)
{
    if (key == Input::ENTER_KEY)
    {
        hide();
    }
}

void HelpMenu::renderContent()
{
    GLfloat currentY = TEXT_START_Y;

    for (const auto& line : m_helpLines)
    {
        renderText(line, TEXT_START_X, currentY);
        currentY -= LINE_SPACING;
    }

    // Footer
    renderText("Press ENTER to close this window", 40.0f, 20.0f, GLUT_BITMAP_HELVETICA_18);
}
