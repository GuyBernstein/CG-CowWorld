/*****************************************************************//**
 * \file   SceneObjects.cpp
 * \brief  Function definitions for SceneObjects.h
 * 
 * \author aaron
 * \date   June 2023
 *********************************************************************/

/******************************
*          DEFINES            *
*******************************/
#define _USE_MATH_DEFINES

/******************************
*          INCLUDES           *
*******************************/
#include <cmath>

#include "SceneObjects.h"
#include "WcPt3D.h"
#include "RGBColor.h"
#include "WcVector3D.h"

/******************************
*       GLOBAL VARIABLES      *
*******************************/
/* Background */
const GLfloat WORLD_MIN_COORD = -100.0;
const GLfloat WORLD_MAX_COORD = 100.0;
const GLfloat SKY_SPHERE_RADIUS = 141.4;

/* Sun */
GLfloat sunHorizontalAngle = 0.0;
GLfloat sunVerticalAngle = 45.0;
GLfloat sunConstAttenuation = 0.7;

/******************************
*     FUNCTION DEFINITIONS    *
*******************************/
void renderBackground(void)
{
    /* Sky */
    static const GLint SKY_SPHERE_NUM_SLICES = 50;
    static const GLint SKY_SPHERE_NUM_STACKS = 50;

    /* Lighting */
    static const GLfloat grassGreenColor[] = { RGB_COLOR_GRASS_GREEN, 1.0 };
    static const GLfloat skyBlueColor[] = { RGB_COLOR_SKY_BLUE, 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    /* Render plane */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grassGreenColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(WORLD_MIN_COORD, WORLD_MIN_COORD, 0.0);
    glVertex3f(WORLD_MAX_COORD, WORLD_MIN_COORD, 0.0);
    glVertex3f(WORLD_MAX_COORD, WORLD_MAX_COORD, 0.0);
    glVertex3f(WORLD_MIN_COORD, WORLD_MAX_COORD, 0.0);
    glEnd();

    /* Render sky */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, skyBlueColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glutSolidSphere(SKY_SPHERE_RADIUS, SKY_SPHERE_NUM_SLICES, SKY_SPHERE_NUM_STACKS);

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


void renderHouseObject(const WcPt3D& position, const GLfloat rotationAngle)
{
    /* Dimensions */
    static const GLfloat HOUSE_WIDTH = 5.0;
    static const GLfloat HOUSE_LENGTH = 7.0;
    static const GLfloat HOUSE_WALL_HEIGHT = 3.25;
    static const GLfloat HOUSE_ROOF_HEIGHT = 2.0;
    static const GLfloat HOUSE_DOOR_WIDTH = 1.5;
    static const GLfloat HOUSE_DOOR_HEIGHT = 2.25;
    static const GLfloat HOUSE_WINDOW_WIDTH = 0.75;
    static const GLfloat HOUSE_WINDOW_HEIGHT = 1.5;
    static const GLfloat HOUSE_WINDOW_HEIGHT_FROM_GROUND = 1.0;
    static const GLfloat HOUSE_LINE_WIDTH = 1.0;

    /* Lighting */
    static const GLfloat creamColor[] = { RGB_COLOR_CREAM, 1.0 };
    static const GLfloat clayColor[] = { RGB_COLOR_CLAY, 1.0 };
    static const GLfloat brownColor[] = { RGB_COLOR_BROWN, 1.0 };
    static const GLfloat lightBlueColor[] = { RGB_COLOR_LIGHT_BLUE, 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };
    static const GLfloat DOOR_SHININESS = 10.0;
    static const GLfloat WINDOW_SHININESS = 5.0;

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(position.getX(), position.getY(), position.getZ());
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);

    /* Walls */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, creamColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glEnd();

    /* Roof */
    static WcVector3D roofNormal1;
    static WcVector3D roofNormal2;
    static bool calculateRoofNormals = true;
    if (calculateRoofNormals)
    {
        WcPt3D v1(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
        WcPt3D v2(0.0, (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
        WcPt3D v3(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
        roofNormal1 = getNormalVector(v1, v2, v3);

        WcPt3D v4((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
        WcPt3D v5((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
        WcPt3D v6(0.0, -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
        roofNormal2 = getNormalVector(v4, v5, v6);

        calculateRoofNormals = false;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, clayColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(0.0, -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(0.0, (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(roofNormal1.getX(), roofNormal1.getY(), roofNormal1.getZ());
    glVertex3f(-(HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(0.0, (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glVertex3f(0.0, -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(roofNormal2.getX(), roofNormal2.getY(), roofNormal2.getZ());
    glVertex3f((HOUSE_WIDTH / 2.0), -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0), (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT);
    glVertex3f(0.0, (HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glVertex3f(0.0, -(HOUSE_LENGTH / 2.0), HOUSE_WALL_HEIGHT + HOUSE_ROOF_HEIGHT);
    glEnd();

    /* Door */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brownColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, DOOR_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_DOOR_WIDTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_DOOR_WIDTH / 2.0), 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_DOOR_WIDTH / 2.0), HOUSE_DOOR_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_DOOR_WIDTH / 2.0), HOUSE_DOOR_HEIGHT);
    glEnd();

    /* Windows */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightBlueColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, WINDOW_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_LENGTH / 4.0) + HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_LENGTH / 4.0) + HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, (HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_LENGTH / 4.0) - HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_LENGTH / 4.0) - HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glVertex3f((HOUSE_WIDTH / 2.0) + 0.01, -(HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, (HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, (HOUSE_LENGTH / 4.0) + HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, (HOUSE_LENGTH / 4.0) + HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, (HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, -(HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, -(HOUSE_LENGTH / 4.0) - HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, -(HOUSE_LENGTH / 4.0) - HOUSE_WINDOW_WIDTH, HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glVertex3f(-(HOUSE_WIDTH / 2.0) - 0.01, -(HOUSE_LENGTH / 4.0), HOUSE_WINDOW_HEIGHT_FROM_GROUND + HOUSE_WINDOW_HEIGHT);
    glEnd();

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


void renderShedObject(const WcPt3D& position, const GLfloat rotationAngle)
{
    static const GLfloat SHED_WIDTH = 3.0;
    static const GLfloat SHED_LENGTH = 4.0;
    static const GLfloat SHED_WALL_HEIGHT = 2.5;
    static const GLfloat SHED_ROOF_HEIGHT = 1.0;
    static const GLfloat SHED_DOOR_WIDTH = 1.5;
    static const GLfloat SHED_DOOR_HEIGHT = 2.5;
    static const GLfloat SHED_EPSILON = 0.025;
    static const GLfloat SHED_LINE_WIDTH = 1.0;

    /* Lighting */
    static const GLfloat mediumGrayColor[] = { RGB_COLOR_MEDIUM_GRAY, 1.0 };
    static const GLfloat lightGrayColor[] = { RGB_COLOR_LIGHT_GRAY, 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };
    static const GLfloat SHED_SHININESS = 25.0;

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(position.getX(), position.getY(), position.getZ());
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);

    /* Walls */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mediumGrayColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, SHED_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glEnd();

    /* Roof */
    static WcVector3D roofNormal1;
    static WcVector3D roofNormal2;
    static bool calculateRoofNormals = true;
    if (calculateRoofNormals)
    {
        WcPt3D v1(0.0, (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
        WcPt3D v2(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
        WcPt3D v3(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
        roofNormal1 = getNormalVector(v1, v2, v3);

        WcPt3D v4((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
        WcPt3D v5((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
        WcPt3D v6(0.0, (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
        roofNormal2 = getNormalVector(v4, v5, v6);

        calculateRoofNormals = false;
    }

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(roofNormal1.getX(), roofNormal1.getY(), roofNormal1.getZ());
    glVertex3f(-(SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(-(SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(roofNormal2.getX(), roofNormal2.getY(), roofNormal2.getZ());
    glVertex3f((SHED_WIDTH / 2.0), -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f((SHED_WIDTH / 2.0), (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, (SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glVertex3f(0.0, -(SHED_LENGTH / 2.0), SHED_WALL_HEIGHT + SHED_ROOF_HEIGHT + SHED_EPSILON);
    glEnd();

    /* Door */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightGrayColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, SHED_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-(SHED_DOOR_WIDTH / 2.0), (SHED_LENGTH / 2.0) + SHED_EPSILON, SHED_EPSILON);
    glVertex3f((SHED_DOOR_WIDTH / 2.0), (SHED_LENGTH / 2.0) + SHED_EPSILON, SHED_EPSILON);
    glVertex3f((SHED_DOOR_WIDTH / 2.0), (SHED_LENGTH / 2.0) + SHED_EPSILON, SHED_DOOR_HEIGHT);
    glVertex3f(-(SHED_DOOR_WIDTH / 2.0), (SHED_LENGTH / 2.0) + SHED_EPSILON, SHED_DOOR_HEIGHT);
    glEnd();

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


void renderSunObject(void)
{
    /* Dimensions */
    static const GLfloat SUN_SPHERE_RADIUS = 2.0;
    static const GLint SUN_SPHERE_NUM_SLICES = 20;
    static const GLint SUN_SPHERE_NUM_STACKS = 20;

    /* Lighting */
    static const GLfloat sunYellowColor[] = { RGB_COLOR_SUN_YELLOW , 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };
    static const GLfloat SUN_LINEAR_ATTENUATION = 0.005;
    static const GLfloat SUN_QUADRATIC_ATTENUATION = 0.0;

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    const WcPt3D sunPosition(  // Spherical coordinates
        SKY_SPHERE_RADIUS * sin((90.0 - sunVerticalAngle) * M_PI / 180.0) * cos(sunHorizontalAngle * M_PI / 180.0),
        SKY_SPHERE_RADIUS * sin((90.0 - sunVerticalAngle) * M_PI / 180.0) * sin(sunHorizontalAngle * M_PI / 180.0),
        SKY_SPHERE_RADIUS * cos((90.0 - sunVerticalAngle) * M_PI / 180.0)
    );
    const GLfloat sunLightPosType[] = { sunPosition.getX(), sunPosition.getY(), sunPosition.getZ(), 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiteColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, sunYellowColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glTranslatef(sunPosition.getX(), sunPosition.getY(), sunPosition.getZ());
    glutSolidSphere(SUN_SPHERE_RADIUS, SUN_SPHERE_NUM_SLICES, SUN_SPHERE_NUM_STACKS);

    glLightfv(GL_LIGHT0, GL_POSITION, sunLightPosType);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, sunConstAttenuation);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, SUN_LINEAR_ATTENUATION);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, SUN_QUADRATIC_ATTENUATION);
    glEnable(GL_LIGHT0);

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


void renderTreeObject(const WcPt3D& position)
{
    /* Tree stem parameters */
    static const GLfloat TREE_STEM_BASE_RADIUS = 0.5;
    static const GLfloat TREE_STEM_HEIGHT = 8.0;
    static const GLint TREE_STEM_NUM_SLICES = 10;
    static const GLint TREE_STEM_NUM_STACKS = 10;

    /* Leaf parameters */
    static const GLfloat LEAF_BASE_WIDTH1 = 1.5;
    static const GLfloat LEAF_BASE_WIDTH2 = 1.25;
    static const GLfloat LEAF_BASE_WIDTH3 = 1.0;
    static const GLfloat LEAF_HEIGHT = 2.5;
    static const GLfloat LEAF_HEIGHT_FROM_GROUND = 2.0;
    static const GLint LEAF_NUM_SLICES = 25;
    static const GLint LEAF_NUM_STACKS = 25;

    /* Lighting */
    static const GLfloat darkBrownColor[] = { RGB_COLOR_DARK_BROWN, 1.0 };
    static const GLfloat darkGreenColor[] = { RGB_COLOR_DARK_GREEN, 1.0 };
    static const GLfloat mediumGreenColor[] = { RGB_COLOR_MEDIUM_GREEN, 1.0 };
    static const GLfloat forestGreenColor[] = { RGB_COLOR_FOREST_GREEN, 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(position.getX(), position.getY(), position.getZ());

    /* Render tree stem */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkBrownColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glutSolidCone(TREE_STEM_BASE_RADIUS, TREE_STEM_HEIGHT, TREE_STEM_NUM_SLICES, TREE_STEM_NUM_STACKS);

    GLUquadric* disk = gluNewQuadric();

    /* Render leaf #1 */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGreenColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glTranslatef(0.0, 0.0, LEAF_HEIGHT_FROM_GROUND);
    glNormal3f(0.0, 0.0, -1.0);
    gluDisk(disk, 0.0, LEAF_BASE_WIDTH1, LEAF_NUM_SLICES, LEAF_NUM_STACKS);
    glutSolidCone(LEAF_BASE_WIDTH1, LEAF_HEIGHT, LEAF_NUM_SLICES, LEAF_NUM_STACKS);

    /* Render leaf #2 */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mediumGreenColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glTranslatef(0.0, 0.0, LEAF_HEIGHT_FROM_GROUND);
    glNormal3f(0.0, 0.0, -1.0);
    gluDisk(disk, 0.0, LEAF_BASE_WIDTH2, LEAF_NUM_SLICES, LEAF_NUM_STACKS);
    glutSolidCone(LEAF_BASE_WIDTH2, LEAF_HEIGHT, LEAF_NUM_SLICES, LEAF_NUM_STACKS);

    /* Render leaf #3 */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, forestGreenColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blackColor);

    glTranslatef(0.0, 0.0, LEAF_HEIGHT_FROM_GROUND);
    glNormal3f(0.0, 0.0, -1.0);
    gluDisk(disk, 0.0, LEAF_BASE_WIDTH3, LEAF_NUM_SLICES, LEAF_NUM_STACKS);
    glutSolidCone(LEAF_BASE_WIDTH3, LEAF_HEIGHT, LEAF_NUM_SLICES, LEAF_NUM_STACKS);

    gluDeleteQuadric(disk);

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


void renderWaterTank(const WcPt3D& position, const GLfloat rotationAngle)
{
    static const GLfloat WATER_TANK_WIDTH = 1.0;
    static const GLfloat WATER_TANK_LENGTH = 3.0;
    static const GLfloat WATER_TANK_HEIGHT = 0.5;
    static const GLfloat WATER_TANK_WATER_LEVEL = 0.35;
    static const GLfloat WATER_TANK_LINE_WIDTH = 1.0;

    /* Lighting */
    static const GLfloat darkGrayColor[] = { RGB_COLOR_DARK_GRAY, 1.0 };
    static const GLfloat waterBlueColor[] = { RGB_COLOR_WATER_BLUE, 1.0 };
    static const GLfloat blackColor[] = { RGB_COLOR_BLACK, 1.0 };
    static const GLfloat whiteColor[] = { RGB_COLOR_WHITE, 1.0 };
    static const GLfloat WALL_SHININESS = 15;
    static const GLfloat WATER_SHININESS = 20;

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(rotationAngle, 0.0, 0.0, 1.0);
    glTranslatef(position.getX(), position.getY(), position.getZ());

    /* Water tank walls */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGrayColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, WALL_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glVertex3f((WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glVertex3f((WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), 0.0);
    glVertex3f((WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_HEIGHT);
    glEnd();

    /* Water */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, waterBlueColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, blackColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor);
    glMaterialf(GL_FRONT, GL_SHININESS, WATER_SHININESS);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_WATER_LEVEL);
    glVertex3f((WATER_TANK_WIDTH / 2.0), -(WATER_TANK_LENGTH / 2.0), WATER_TANK_WATER_LEVEL);
    glVertex3f((WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_WATER_LEVEL);
    glVertex3f(-(WATER_TANK_WIDTH / 2.0), (WATER_TANK_LENGTH / 2.0), WATER_TANK_WATER_LEVEL);
    glEnd();

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


WcVector3D crossProduct(const WcVector3D& v1, const WcVector3D& v2)
{
    WcVector3D result;

    result.setX(v1.getY() * v2.getZ() - v1.getZ() * v2.getY());
    result.setY(-(v1.getX() * v2.getZ() - v1.getZ() * v2.getX()));
    result.setZ(v1.getX() * v2.getY() - v1.getY() * v2.getX());

    return result;
}


WcVector3D getNormalVector(const WcPt3D& v1, const WcPt3D& v2, const WcPt3D& v3)
{
    WcVector3D a, b, result;

    a.setX(v1.getX() - v2.getX());
    a.setY(v1.getY() - v2.getY());
    a.setZ(v1.getZ() - v2.getZ());

    b.setX(v1.getX() - v3.getX());
    b.setY(v1.getY() - v3.getY());
    b.setZ(v1.getZ() - v3.getZ());

    result = crossProduct(a, b);
    result.normalize();
    return result;
}