/*****************************************************************//**
 * \file   MainScene.cpp
 * \brief  Function definitions for MainScene.h
 * 
 * \author aaron
 * \date   May 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <vector>
#include <cctype>

#include "MainScene.h"
#include "Menus.h"
#include "SceneObjects.h"
#include "Cow.h"

#include "RGBColor.h"
#include "WcPt3D.h"

/******************************
*            ENUMS            *
*******************************/
enum CameraMode
{
    FIRST_PERSON = 0,
    THIRD_PERSON,
    LAST_OF_CAMERA_MODE
};

enum OrganMode
{
    HEAD = 0,
    TAIL,
    LAST_OF_ORGAN_MODE
};

/******************************
*       GLOBAL VARIABLES      *
*******************************/
GLfloat globalAmbient[] = { 0.75, 0.75, 0.75, 1.0 };
CameraMode cameraMode = THIRD_PERSON;
OrganMode organMode = HEAD;

Cow cow;

/******************************
*     FUNCTION DEFINITIONS    *
*******************************/
void renderMainScene(void)
{
    static const GLint XW_MIN = -1;
    static const GLint XW_MAX = 1;
    static const GLint YW_MIN = -1;
    static const GLint YW_MAX = 1;
    static const GLint Z_NEAR = 1;
    static const GLint Z_FAR = 175;
    static const WcPt3D houseLocation(-10, 0, 0);
    static const WcPt3D shedLocation(0, 8, 0);
    static const WcPt3D waterTankLocation(2.5, 8, 0);
    static const std::vector<WcPt3D> treeLocations(
        {
            WcPt3D(15, 15, 0),
            WcPt3D(-84, 47, 0),
            WcPt3D(25, 4, 0),
            WcPt3D(19, -9, 0),
            WcPt3D(-38, -7, 0),
            WcPt3D(7, 2, 0),
            WcPt3D(3, -52, 0),
            WcPt3D(10, -30, 0),
            WcPt3D(-17, -17, 0),
            WcPt3D(-66, -55, 0),
            WcPt3D(-5, 5, 0),
            WcPt3D(-19, 2, 0),
            WcPt3D(-14, 9, 0),
            WcPt3D(20, -5, 0),
            WcPt3D(32, 9, 0),
            WcPt3D(1, 22, 0),
            WcPt3D(6, 15, 0),
            WcPt3D(-3, 29, 0),
            WcPt3D(33, -33, 0),
            WcPt3D(60, -77, 0),
            WcPt3D(1, -10, 0),
            WcPt3D(3, -44, 0),
            WcPt3D(0, 90, 0),
            WcPt3D(-8, -49, 0),
            WcPt3D(-19, -40, 0),
            WcPt3D(-80, -90, 0)
        }
    );

    const GLint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    const GLint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, windowWidth, windowHeight - TOP_MENU_HEIGHT);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    resetProjectionAndModelviewMatrices();

    glMatrixMode(GL_PROJECTION);
    glFrustum(XW_MIN, XW_MAX, YW_MIN, YW_MAX, Z_NEAR, Z_FAR);

    renderCamera();

    renderBackground();
    renderSunObject();
    renderHouseObject(houseLocation, 0.0);
    renderShedObject(shedLocation, 180.0);
    renderWaterTank(waterTankLocation, 0.0);

    for (const auto& p : treeLocations)
    {
        renderTreeObject(p);
    }

    cow.render();

    glDisable(GL_DEPTH_TEST);
}


void renderCamera(void)
{
    static const WcVector3D upVector(0.0, 0.0, 1.0);
    static WcPt3D viewOrigin;
    static WcPt3D lookAtPoint;

    if (cameraMode == FIRST_PERSON)
    {
        viewOrigin = WcPt3D(cow.getFpCamViewOrigin());
        lookAtPoint = WcPt3D(cow.getFpCamLookAtPoint());
    }
    else
    {
        viewOrigin = WcPt3D(cow.getTpCamViewOrigin());
        lookAtPoint = WcPt3D(cow.getTpCamLookAtPoint());
    }

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(viewOrigin.getX(), viewOrigin.getY(), viewOrigin.getZ(), lookAtPoint.getX(), lookAtPoint.getY(), lookAtPoint.getZ(), upVector.getX(), upVector.getY(), upVector.getZ());
}


void handleKeyboardEventMainScene(unsigned char key, int x, int y)
{
    key = static_cast<unsigned char>(tolower(key));

    switch (key)
    {
        /* Organ mode toggle (head / tail) */
    case 't':
        organMode = TAIL;
        break;

    case 'h':
        organMode = HEAD;
        break;

        /* Camera mode toggle */
    case 'v':
        if (cameraMode == THIRD_PERSON)
        {
            cameraMode = FIRST_PERSON;
            organMode = HEAD;
        }
        else
            cameraMode = THIRD_PERSON;
        break;

        /* TP Camera controls */
    case '1':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamDecreaseRadius();
        break;

    case '2':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamRotateDown();
        break;

    case '4':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamRotateCW();
        break;

    case '5':
        if (cameraMode == THIRD_PERSON)
        {
            cow.TPCamReset();
            cow.resetTail();
            cow.resetHead();
        }
        else
            cow.resetHead();
        break;

    case '6':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamRotateCCW();
        break;

    case '7':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamIncreaseRadius();
        break;

    case '8':
        if (cameraMode == THIRD_PERSON)
            cow.TPCamRotateUp();
        break;

        /* FP Camera and head controls / Tail controls */
    case 'i':
        if (organMode == HEAD)
            cow.moveHeadUp();
        else
            cow.moveTailUp();
        break;
        
    case 'k':
        if (organMode == HEAD)
            cow.moveHeadDown();
        else
            cow.moveTailDown();
        break;

    case 'j':
        if (organMode == HEAD)
            cow.turnHeadLeft();
        else
            cow.turnTailLeft();
        break;

    case 'l':
        if (organMode == HEAD)
            cow.turnHeadRight();
        else
            cow.turnTailRight();
        break;

        /* Movement controls */
    case 'w':
        cow.moveForward();
        break;

    case 's':
        cow.moveBackward();
        break;

    case 'a':
        cow.turnLeft();
        break;

    case 'd':
        cow.turnRight();
        break;
    }
}
