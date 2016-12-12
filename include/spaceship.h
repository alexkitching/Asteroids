#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_
#include "position.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "asteroids.h"
#include "bullet.h"
#include "livescontroller.h"
#include <vector>

extern float g_DeltaTime;

class oSpaceship
{
public:
	oSpaceship();
	void Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos);
	void SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short  a_breakKey, short a_fireKey);
	void CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidLarge>& a_asteroidarray, oLivesController& a_livescontroller);
	void CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidMedium>& a_asteroidarray, oLivesController& a_livescontroller);
	void CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidSmall>& a_asteroidarray, oLivesController& a_livescontroller);
	void ResetVars(oSpaceship & a_spaceship);
	void Respawn(oSpaceship& a_Spaceship);
	float AngleWrap(float x);
	int iSpriteID = -1;
	Position pos;
	friend class oObjectUpdateController;
private:
	//Dimension Variables

	int const iWidth = 18, iHeight = 25;
	float const fRadius = 10.5f;
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
	bool bIsDead = false;
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1, fireKey = -1;

	std::vector<oBullet> bullets;
	Vector vNew = Vector(0.0f, 0.0f);
};
#endif