////////////////////////////////////////////////////////////////////
// File: <Spaceship.h>
// Author: <Alex Kitching>
// Date Created: <30/11/16>
// Brief: <Header file for the Spaceship Class.>
////////////////////////////////////////////////////////////////////
#ifndef _Spaceship_H_
#define _Spaceship_H_

#include "position.h"
#include "vector.h"
#include "asteroids.h"
#include "Livescontroller.h"
#define _USE_MATH_DEFINES
#include <math.h>

extern float g_fDeltaTime;

class oSpaceship
{
public:
	oSpaceship() {};
	~oSpaceship() {};
	void Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName);
	void Draw(oSpaceship& a_Spaceship, float a_fXPos, float a_fYPos);
	void Destroy(oSpaceship& a_Spaceship, oLivescontroller& a_Livescontroller);
	void SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_fireKey, short a_exitKey);
	void CheckCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oLivescontroller& a_Livescontroller, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount, int& a_UFOEasydeathcount, int& a_UFOHarddeathcount);
	void CheckSpawnCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray);
	void ResetVars(oSpaceship& a_Spaceship);
	void Respawn(oSpaceship& a_Spaceship);
	void GetPos(float& a_fPosX, float& a_fPosY);
	void GetRadius(float& a_fRadius);
	void SetCollision(bool a_collision);
	bool IsActive();
	float AngleWrap(float x);
	int iSpriteID = -1;
	char const c_cSpaceshipFileName[18] = "./images/Ship.png";
	Position pos;
	friend class oObjectUpdateController;
private:
	//Dimension Variables
	int const c_iWidth = 18, c_iHeight = 25;
	float const c_fRadius = 10.5f;
	float const c_fSpawnRadius = c_fRadius * 3.5f;
	//Speed Variables
	float const c_fAcceleration = 0.03f;
	float const c_fDrag = 0.99f;
	float fTotalVelocity;
	float const c_fMaxVelocity = 4.f;
	float const c_fVelocityZero = 0.f;
	//Rotation Variables
	float const c_degtorad = (float) M_PI / 180.f; // Converts degrees to radians
	float fFacingAngleDeg = 90.0;
	float fFacingAngleRad = fFacingAngleDeg * c_degtorad;
	float fMovementAngleDeg = 90.0;
	float fMovementAngleRad = fMovementAngleDeg * c_degtorad;
	float const c_fTurnRate = 2.0;
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
	float const c_fMaxSpawnTime = 5.f;
	//Movement Keys
	short upKey = -1, downKey = -1, leftKey = -1, rightKey = -1, breakKey = -1, fireKey = -1, exitKey = -1;
	Vector vNew;
};
#endif // !_Spaceship_H_
