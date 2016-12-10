#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_
#include "position.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "asteroids.h"
#include "bullet.h"
#include <vector>

extern float g_DeltaTime;

class oSpaceship
{
public:
	oSpaceship();
	void Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos);
	void SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short  a_breakKey, short a_fireKey);
	void Update(oSpaceship& a_Spaceship, oAsteroidLarge* a_asteroidlargearray);
	float AngleWrap(float x);
	int iSpriteID = -1;
	Position pos;
private:
	//Dimension Variables

	int const iWidth = 18, iHeight = 25;
	//Speed Variables
	float const fAcceleration = 0.03f;
	float const fDrag = 0.99f;
	float fTotalVelocity = 0.0f;
	float const fMaxVelocity = 4.f;
	float const fVelocityZero = 0.f;

	//Rotation Variables
	const float degtorad = (float) M_PI / 180.f; // Converts degrees to radians
	const float degtoafix = 256.f / 360.f;
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
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	//Firing Varibles 
	float fFireDelay = 0.f;
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1, fireKey = -1;


	Vector vNew = Vector(0.0f, 0.0f);
};
#endif