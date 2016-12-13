#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_
#include "position.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "asteroids.h"
#include "bullet.h"
#include "livescontroller.h"

extern float g_DeltaTime;

class oSpaceship
{
public:
	oSpaceship() {};
	void Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName);
	void Draw(oSpaceship& a_Spaceship, float a_fXPos, float a_fYPos);
	void Destroy(oSpaceship& a_Spaceship);
	void SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short  a_breakKey, short a_fireKey, short a_exitKey);
	void CheckAsteroidCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_asteroidarray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oLivesController& a_livescontroller, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount);
	void CheckSpawnCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray);
	void ResetVars(oSpaceship& a_Spaceship);
	void Respawn(oSpaceship& a_Spaceship);
	float AngleWrap(float x);
	int iSpriteID = -1;
	char const cSpaceshipFileName[18] = "./images/Ship.png";
	Position pos;
	friend class oObjectUpdateController;
private:
	//Dimension Variables
	int const iWidth = 18, iHeight = 25;
	float const fRadius = 10.5f;
	float const fSpawnRadius = fRadius * 2;
	//Speed Variables
	float const fAcceleration = 0.03f;
	float const fDrag = 0.99f;
	float fTotalVelocity;
	float const fMaxVelocity = 4.f;
	float const fVelocityZero = 0.f;
	//Rotation Variables
	const float degtorad = (float) M_PI / 180.f; // Converts degrees to radians
	float fFacingAngleDeg = 90.0;
	float fFacingAngleRad = fFacingAngleDeg * degtorad;
	float fMovementAngleDeg = 90.0;
	float fMovementAngleRad = fMovementAngleDeg * degtorad;
	float const fTurnRate = 2.0;
	float fCurrentTurnRate;
	//Position Variables
	float fPosX = 0.f;
	float fPosY = 0.f;
	//Vector Variables
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	//Firing Varibles 
	float fFireDelay;
	bool bIsActive = false;
	bool bCollision = false;
	float fSpawnTime = 0.f;
	float fMaxSpawnTime = 5.f;
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1, fireKey = -1, exitKey = -1;
	Vector vNew;
};
#endif