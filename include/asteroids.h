#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_
#include "position.h"
#include "spawncontroller.h"
#include "vector.h"
class oAsteroid
{
public:
	int iSpriteID = -1;
	int iQty;
	oAsteroid();
protected:
	int iScore = 0;
	int iWidth = 0;
	int iHeight = 0;

	//Speed Variables
	float const iSpeedMax = 3.0f;
	float const iSpeedMin = 0.5f;
	//Rotation Variables
	int iSpriteTurnRate = 0;
	//Position Variables
	float fPosX = 0.f;
	float fPosY = 0.f;
	//Vector Variables
	float fNewVecX = 0.f;
	float fNewVecY = 0.f;
	float fCurrentVecX = 0.f;
	float fCurrentVecY = 0.f;
	//Death Variables
	bool bIsDead = false;
	Position pos;
	Vector NewVec = Vector(0.0f, 0.0f);
private:
	
};
class oAsteroidLarge : public oAsteroid
{
public:
	oAsteroidLarge();
	void Initialise(oSpawnController& a_spawncontroller, int a_AsteroidNumber, const char* a_AsteroidLargeImageFileName);
	void Update(oAsteroidLarge& a_asteroidlarge);
	void GetDimensions(int &a_iWidth, int &a_iHeight);
	void CollisionCheck(oAsteroidLarge* a_asteroidlarge);
	void SetRotation(int &a_CurrentRotation);
private:	
	
};

class oAsteroidSmall : public oAsteroid
{
public:
	oAsteroidSmall();
	void Initialise(oAsteroidSmall& a_asteroidsmall, const char* a_AsteroidSmallImageFileName);
	void Update(oAsteroidSmall& a_asteroidsmall);
	void GetDimensions(int a_iWidth, int a_iHeight);

private:
};
#endif