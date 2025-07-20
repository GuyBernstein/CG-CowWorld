#pragma once
/*****************************************************************//**
 * \file   SceneObjects.h
 * \brief  A collection of functions for rendering various objects
 *         in the CowGL world.
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
*    FORWARD DECLARATIONS     *
*******************************/
class WcPt3D;
class WcVector3D;

/******************************
*      EXTERNAL VARIABLES     *
*******************************/
/* Background */
extern const GLfloat WORLD_MIN_COORD;
extern const GLfloat WORLD_MAX_COORD;

/* Sun */
extern GLfloat sunHorizontalAngle;
extern GLfloat sunVerticalAngle;
extern GLfloat sunConstAttenuation;

/******************************
*     FUNCTION PROTOTYPES     *
*******************************/
void renderBackground(void);
void renderHouseObject(const WcPt3D& position, const GLfloat rotationAngle);
void renderShedObject(const WcPt3D& position, const GLfloat rotationAngle);
void renderSunObject(void);
void renderTreeObject(const WcPt3D& position);
void renderWaterTank(const WcPt3D& position, const GLfloat rotationAngle);
WcVector3D crossProduct(const WcVector3D& v1, const WcVector3D& v2);
WcVector3D getNormalVector(const WcPt3D& v1, const WcPt3D& v2, const WcPt3D& v3);
