#pragma once
/*****************************************************************//**
 * \file   Cow.h
 * \brief  Cow class declaration.
 * 
 * \author aaron
 * \date   June 2023
 *********************************************************************/

/******************************
*          INCLUDES           *
*******************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "WcPt3D.h"

class Cow
{
public:
	Cow();
	Cow(WcPt3D pos);
	void render(void);

	/* Cow movement */
	void moveForward(void);
	void moveBackward(void);
	void turnLeft(void);
	void turnRight(void);

	/* Head movement */
	void moveHeadUp(void);
	void moveHeadDown(void);
	void turnHeadLeft(void);
	void turnHeadRight(void);
	void resetHead(void);

	/* Tail movement */
	void moveTailUp(void);
	void moveTailDown(void);
	void turnTailLeft(void);
	void turnTailRight(void);
	void resetTail(void);

	/* Camera controls */
	void TPCamRotateCW(void);
	void TPCamRotateCCW(void);
	void TPCamRotateUp(void);
	void TPCamRotateDown(void);
	void TPCamIncreaseRadius(void);
	void TPCamDecreaseRadius(void);
	void TPCamReset(void);

	/* Getters */
	WcPt3D getPosition(void);
	WcPt3D getTpCamViewOrigin(void);
	WcPt3D getTpCamLookAtPoint(void);
	WcPt3D getFpCamViewOrigin(void);
	WcPt3D getFpCamLookAtPoint(void);

private:
	void _renderBody(void);
	void _renderHead(void);
	void _renderTail(void);

	WcPt3D _pos;
	GLfloat _directionAngle;
	GLfloat _headAngleHorizontal, _headAngleVertical;
	GLfloat _tailAngleHorizontal, _tailAngleVertical;
	GLfloat _tpCamRadius, _tpCamVerticalAngle, _tpCamHorizontalAngle;
};
