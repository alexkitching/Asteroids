#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_
#include "position.h"
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

	int iSpriteID = -1;

	//Speed Variables
	float iAcceleration = 0.01f;
	float iCurrentVelocity = 0.0f;
	float iMaxVelocity = 4.0f;
	float ixVelocity = 0, iyVelocity = 0;;
	
	//Rotation Variables
	const float degtorad = M_PI / 180.0; // Converts degrees to radians
	const float degtoafix = 256.0 / 360.0;
	float iFacingAngleDeg = 90.0;
	float iFacingAngleRad = iFacingAngleDeg * degtorad;
	float iFacingAngleAfix = iFacingAngleDeg * degtoafix;
	float iMovementAngleDeg = 90.0;
	float iMovementAngleRad = iMovementAngleDeg * degtorad;
	float iMovementAngleAfix = iMovementAngleDeg * degtoafix;
	int iSpriteTurnRate = 0;
	float iTurnRate = 1.0;
	
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1;
private:

	const int iWidth = 18, iHeight = 25;

	Position pos;
};

#endif