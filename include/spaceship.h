#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_
#include "position.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern float g_DeltaTime;

class oSpaceship
{
public:
	oSpaceship();
	void Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos);
	void SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short  a_breakKey);
	void MoveSpaceship(oSpaceship& a_Spaceship);
	float AngleWrap(float x);

	int iSpriteID = -1;


private:

	const int iWidth = 18, iHeight = 25;
	//Speed Variables
	float const fAcceleration = 0.03;
	float const fDrag = 0.01f;
	float fTotalVelocity = 0.0f;
	float const fMaxVelocity = 4.0f;
	float const fVelocityZero = 0.f;

	//Rotation Variables
	const float degtorad = M_PI / 180.0; // Converts degrees to radians
	const float degtoafix = 256.0 / 360.0;
	float fFacingAngleDeg = 90.0;
	float fFacingAngleRad = fFacingAngleDeg * degtorad;
	float fMovementAngleDeg = 90.0;
	float fMovementAngleRad = fMovementAngleDeg * degtorad;
	float const fTurnRate = 2.0;
	float fCurrentTurnRate = 0.f;
	//Position Variables
	float fPosX = 0.f;
	float fPosY = 0.f;
	//Vector Variables
	float fNewVecX = 0.f;
	float fNewVecY = 0.f;
	float fCurrentVecX = 0.f;
	float fCurrentVecY = 0.f;
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1;


	Vector VecNew = Vector(0.0f, 0.0f);
	Position pos;
};

#endif