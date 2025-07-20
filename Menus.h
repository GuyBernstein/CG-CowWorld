#pragma once
/*****************************************************************//**
 * \file   Menus.h
 * \brief  A collection of functions for rendering the menus
 *         of CowGL.
 * 
 * \author aaron
 * \date   June 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

/******************************
*      EXTERNAL VARIABLES     *
*******************************/
extern const GLint TOP_MENU_HEIGHT;

/******************************
*     FUNCTION PROTOTYPES     *
*******************************/
/* Menu rendering */
void renderTopMenu(void);
void renderHelpMenu(void);
void renderAdjustLightingMenu(void);

/* Event handling */
void handleMouseEventTopMenu(int button, int state, int x, int y);
void handleKeyboardEventHelpMenu(unsigned char key, int x, int y);
void handleKeyboardEventAdjustLightingMenu(unsigned char key, int x, int y);
void handleMouseEventAdjustLightingMenu(int button, int state, int x, int y);

/* Various */
void resetProjectionAndModelviewMatrices(void);
