//////////////////////////////////////////////////////////////////////////
// File: <bullet.h>
// Author: <Alex Kitching>
// Date Created: <8/12/16>
// Brief: <Header file for all Bullet classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////
#ifndef _BULLET_H_
#define _BULLET_H_

#include "asteroids.h"
#include "vector.h"
#include "Spaceship.h"
#include "ufo.h"

class oBullet
{
public:

	oBullet() {}; //Constructor
	~oBullet() {}; // Destructor

	//Functions
	void SetIsActive(bool a_bIsActive);
	void SetIsDrawn(bool a_bIsDrawn);
	void SetHasExpired(bool a_bHasExpired);
	void GetDimensions(int& a_riWidth, int& a_riHeight);
	void GetPos(float& a_rfPosX, float& a_rfPosY);
	void GetRadius(float &a_rfRadius);

	//General Variables
	int iSpriteID = -1;

	//Friend Classes
	friend class oObjectUpdateController;
protected:

	//Dimension Variables
	int iHeight = 3;
	int iWidth = 3;
	float fRadius = 1.5f;

	//Status Variables
	bool bIsActive = false;
	bool bHasExpired = true;
	bool bIsDrawn = false;

	//Movement Variables
	Vector vNew;
	Vector pos;
};

class oSpaceshipBullet : public oBullet
{
public:

	oSpaceshipBullet() {}; //Constructor
	~oSpaceshipBullet() {};//Destructor

	//Functions
	void Draw(oSpaceshipBullet& a_rSpaceshipBullet, float a_fSpaceshipFacingAngle, float a_fSpaceshipPosX, float a_fSpaceshipPosY);
	void CheckCollision(oSpaceshipBullet& a_rSpaceshipBullet, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		                oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, int& a_rAsteroidLargedeathcount,
		                int& a_rAsteroidMediumdeathcount, int& a_rAsteroidSmalldeathcount, int& a_rUFOEasydeathcount, int& a_rUFOHarddeathcount,
		                oScorecontroller & a_rScorecontroller);
	bool IsActive(oSpaceshipBullet& a_rSpaceshipBullet);
	bool IsDrawn(oSpaceshipBullet& a_rSpaceshipBullet);
	bool HasExpired(oSpaceshipBullet& a_rSpaceshipBullet);
	void Destroy(oSpaceshipBullet& a_rSpaceshipBullet);

	//Speed Variables
	const float c_fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	const float c_fMaxDistance = 400.f;
};

class oUFOBullet : public oBullet
{
public:

	oUFOBullet() {}; //Constructor
	~oUFOBullet() {}; //Destructor

	//Functions
	void Draw(oUFOBullet& a_rUFOBullet, float fUFOPosX, float fUFOPosY, Vector a_velocity);
	void CheckCollision(oUFOBullet& a_rSpaceshipBullet,oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray,
		                oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray,
		                oLivescontroller a_rLivescontroller, int& a_rAsteroidLargedeathcount, int& a_rAsteroidMediumdeathcount,
		                int& a_rAsteroidSmalldeathcount);
	Vector NewFireDirection(oUFOHard& a_rUFOHard, oSpaceship& a_rSpaceship);
	bool IsActive(oUFOBullet& a_rSpaceshipBullet);
	bool IsDrawn(oUFOBullet& a_rSpaceshipBullet);
	bool HasExpired(oUFOBullet& a_rSpaceshipBullet);
	void Destroy(oUFOBullet& a_rSpaceshipBullet);

	//Speed Variables
	float c_fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	float const c_fMaxDistance = 300.f;
};
#endif // !_BULLET_H_
