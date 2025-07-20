#pragma once
/*****************************************************************//**
 * \file   MainScene.h
 * \brief  A collection of functions for rendering the main scene
 *         of CowGL.
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include "WcPt3D.h"
#include "WcVector3D.h"

/******************************
*      EXTERNAL VARIABLES     *
*******************************/
extern GLfloat globalAmbient[];

/******************************
*     FUNCTION PROTOTYPES     *
*******************************/
void renderMainScene(void);
void renderCamera(void);
void handleKeyboardEventMainScene(unsigned char key, int x, int y);
void resetProjectionAndModelviewMatrices(void);
