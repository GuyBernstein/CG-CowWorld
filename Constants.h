//
// Created by Guy Bernstein on 29/05/2025.
// Centralized constants for the CowGL application.
// This file consolidates all magic numbers and constants
// to improve maintainability and readability


#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

/******************************
*      WINDOW CONSTANTS       *
*******************************/
namespace Window {
    constexpr GLint INIT_X = 100;
    constexpr GLint INIT_Y = 100;
    constexpr GLint INIT_WIDTH = 720;
    constexpr GLint INIT_HEIGHT = 480;
    constexpr GLfloat REFRESH_RATE_MS = 16.6666666666666666667f;
}

/******************************
*      WORLD CONSTANTS        *
*******************************/
namespace World {
    constexpr GLfloat MIN_COORD = -100.0f;
    constexpr GLfloat MAX_COORD = 100.0f;
    constexpr GLfloat SKY_SPHERE_RADIUS = 141.4f;
    constexpr GLint SKY_SPHERE_SLICES = 50;
    constexpr GLint SKY_SPHERE_STACKS = 50;
}

/******************************
*      CAMERA CONSTANTS       *
*******************************/
namespace Camera {
    constexpr GLint NEAR_PLANE = 1;
    constexpr GLint FAR_PLANE = 175;
    constexpr GLfloat VIEW_MIN_X = -1.0f;
    constexpr GLfloat VIEW_MAX_X = 1.0f;
    constexpr GLfloat VIEW_MIN_Y = -1.0f;
    constexpr GLfloat VIEW_MAX_Y = 1.0f;

    // Third Person Camera
    constexpr GLfloat TP_INIT_RADIUS = 4.0f;
    constexpr GLfloat TP_INIT_HORIZONTAL_ANGLE = 180.0f;
    constexpr GLfloat TP_INIT_VERTICAL_ANGLE = 35.0f;
    constexpr GLfloat TP_MIN_VERTICAL_ANGLE = 15.0f;
    constexpr GLfloat TP_MAX_VERTICAL_ANGLE = 89.0f;
    constexpr GLfloat TP_MIN_RADIUS = 2.75f;
    constexpr GLfloat TP_MAX_RADIUS = 10.0f;
    constexpr GLfloat TP_MOVEMENT_DIFF = 2.0f;
    constexpr GLfloat TP_RADIUS_DIFF = 0.1f;
}

/******************************
*       COW CONSTANTS         *
*******************************/
namespace Cow {
    // Movement
    constexpr GLfloat MOVEMENT_SPEED = 0.25f;
    constexpr GLfloat ROTATION_SPEED = 2.0f;

    // Head movement
    constexpr GLfloat HEAD_MOVEMENT_SPEED = 2.0f;
    constexpr GLfloat HEAD_MAX_HORIZONTAL_ANGLE = 80.0f;
    constexpr GLfloat HEAD_MAX_VERTICAL_ANGLE = 60.0f;

    // Tail movement
    constexpr GLfloat TAIL_MOVEMENT_SPEED = 2.0f;
    constexpr GLfloat TAIL_INIT_VERTICAL_ANGLE = -70.0f;
    constexpr GLfloat TAIL_MAX_HORIZONTAL_ANGLE = 80.0f;
    constexpr GLfloat TAIL_MAX_VERTICAL_ANGLE = 90.0f;

    // Body dimensions
    constexpr GLfloat BODY_RADIUS = 0.5f;
    constexpr GLfloat BODY_LENGTH = 1.4f;
    constexpr GLfloat HEAD_RADIUS = 0.4f;
    constexpr GLfloat LEG_RADIUS = 0.1f;
    constexpr GLfloat LEG_HEIGHT = 1.0f;
    constexpr GLfloat HOOF_HEIGHT = 0.15f;
    constexpr GLfloat UDDER_RADIUS = 0.35f;
}

/******************************
*       MENU CONSTANTS        *
*******************************/
namespace Menu {
    constexpr GLint TOP_HEIGHT = 30;
    constexpr GLint HELP_WIDTH = 375;
    constexpr GLint HELP_HEIGHT = 350;
    constexpr GLint LIGHTING_WIDTH = 375;
    constexpr GLint LIGHTING_HEIGHT = 350;
    constexpr GLfloat FRAME_WIDTH = 3.0f;
    constexpr GLfloat HELP_FRAME_WIDTH = 7.0f;

    // Button dimensions
    constexpr GLint EXIT_BTN_WIDTH = 45;
    constexpr GLint HELP_BTN_WIDTH = 50;
    constexpr GLint LIGHTING_BTN_WIDTH = 135;
    constexpr GLint ADJUST_BTN_WIDTH = 30;
    constexpr GLint ADJUST_BTN_HEIGHT = 30;
}

/******************************
*    LIGHTING CONSTANTS       *
*******************************/
namespace Lighting {
    constexpr GLfloat AMBIENT_ADJUSTMENT_STEP = 0.05f;
    constexpr GLfloat SUN_ANGLE_STEP = 5.0f;
    constexpr GLfloat SUN_ATTENUATION_STEP = 0.2f;
    constexpr GLfloat SUN_LINEAR_ATTENUATION = 0.005f;
    constexpr GLfloat SUN_QUADRATIC_ATTENUATION = 0.0f;
}

/******************************
*     OBJECT CONSTANTS        *
*******************************/
namespace Objects {
    // House
    constexpr GLfloat HOUSE_WIDTH = 5.0f;
    constexpr GLfloat HOUSE_LENGTH = 7.0f;
    constexpr GLfloat HOUSE_WALL_HEIGHT = 3.25f;
    constexpr GLfloat HOUSE_ROOF_HEIGHT = 2.0f;
    constexpr GLfloat HOUSE_DOOR_WIDTH = 1.5f;
    constexpr GLfloat HOUSE_DOOR_HEIGHT = 2.25f;
    constexpr GLfloat HOUSE_WINDOW_WIDTH = 0.75f;
    constexpr GLfloat HOUSE_WINDOW_HEIGHT = 1.5f;

    // Shed
    constexpr GLfloat SHED_WIDTH = 3.0f;
    constexpr GLfloat SHED_LENGTH = 4.0f;
    constexpr GLfloat SHED_WALL_HEIGHT = 2.5f;
    constexpr GLfloat SHED_ROOF_HEIGHT = 1.0f;

    // Tree
    constexpr GLfloat TREE_STEM_RADIUS = 0.5f;
    constexpr GLfloat TREE_STEM_HEIGHT = 8.0f;
    constexpr GLfloat TREE_LEAF_HEIGHT = 2.5f;

    // Water Tank
    constexpr GLfloat WATER_TANK_WIDTH = 1.0f;
    constexpr GLfloat WATER_TANK_LENGTH = 3.0f;
    constexpr GLfloat WATER_TANK_HEIGHT = 0.5f;
    constexpr GLfloat WATER_TANK_WATER_LEVEL = 0.35f;
}

/******************************
*      INPUT CONSTANTS        *
*******************************/
namespace Input {
    constexpr int ENTER_KEY = 13;
}
#endif //CONSTANTS_H
