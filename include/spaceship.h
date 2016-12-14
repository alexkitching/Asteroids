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

	oSpaceship() {}; //Constructor
	~oSpaceship() {}; //Destructor

	//Functions
	void Initialise(oSpaceship& a_rSpaceship, const char* a_rSpaceshipImageFileName);
	void Draw(oSpaceship& a_rSpaceship, float a_fXPos, float a_fYPos);
	void Destroy(oSpaceship& a_rSpaceship, oLivescontroller& a_rLivescontroller);
	void SetSpaceshipMovementKeys(oSpaceship& a_rSpaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_fireKey, short a_exitKey);
	void CheckCollision(oSpaceship & a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller, int& a_rAsteroidLargedeathcount, int& a_rAsteroidMediumdeathcount, int& a_rAsteroidSmalldeathcount, int& a_rUFOEasydeathcount, int& a_rUFOHarddeathcount);
	void CheckSpawnCollision(oSpaceship & a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray);
	void ResetVars(oSpaceship& a_rSpaceship);
	void Respawn(oSpaceship& a_rSpaceship);
	void GetPos(float& a_rfPosX, float& a_rfPosY);
	void GetRadius(float& a_rfRadius);
	void SetCollision(bool a_collision);
	bool IsActive();
	float AngleWrap(float x);
	int iSpriteID = -1;

	//File Name
	char const c_cSpaceshipFileName[18] = "./images/Ship.png";

	//Position Variables
	Position pos;

	//Friend Classes
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
