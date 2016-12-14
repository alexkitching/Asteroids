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
	oBullet() {};
	~oBullet() {};
	void SetIsActive(bool a_IsActive);
	void SetIsDrawn(bool a_IsDrawn);
	void SetHasExpired(bool a_HasExpired);
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetPos(float& a_PosX, float& a_PosY);
	void GetRadius(float &a_fRadius);
	int iSpriteID = -1;
	friend class oObjectUpdateController;
protected:
	int iHeight = 3;
	int iWidth = 3;
	float fRadius = 1.5f;
	bool bIsActive = false;
	bool bHasExpired = true;
	bool bIsDrawn = false;
	Vector vNew;
	Vector pos;
};

class oSpaceshipBullet : public oBullet
{
public:
	oSpaceshipBullet() {};
	~oSpaceshipBullet() {};
	void Draw(oSpaceshipBullet& a_SpaceshipBullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY);
	void CheckCollision(oSpaceshipBullet& a_SpaceshipBullet, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount, int& a_UFOEasydeathcount, int& a_UFOHarddeathcount, oScorecontroller & a_Scorecontroller);
	bool IsActive(oSpaceshipBullet& a_SpaceshipBullet);
	bool IsDrawn(oSpaceshipBullet& a_SpaceshipBullet);
	bool HasExpired(oSpaceshipBullet& a_SpaceshipBullet);
	void Destroy(oSpaceshipBullet& a_SpaceshipBullet);
	const float c_fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	const int c_fMaxDistance = 400.f;
};

class oUFOBullet : public oBullet
{
public:
	oUFOBullet() {};
	~oUFOBullet() {};
	void Draw(oUFOBullet& a_UFOBullet, float fUFOPosX, float fUFOPosY, Vector& a_velocity);
	void CheckCollision(oUFOBullet& a_SpaceshipBullet,oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oLivescontroller a_Livescontroller, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount);
	Vector NewFireDirection(oUFOHard& a_UFOHard, oSpaceship& a_Spaceship);
	bool IsActive(oUFOBullet& a_SpaceshipBullet);
	bool IsDrawn(oUFOBullet& a_SpaceshipBullet);
	bool HasExpired(oUFOBullet& a_SpaceshipBullet);
	void Destroy(oUFOBullet& a_SpaceshipBullet);
	float c_fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	int c_fMaxDistance = 300.f;
};
#endif // !_BULLET_H_
