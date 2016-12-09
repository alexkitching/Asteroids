#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_
#include "position.h"
#include "spawncontroller.h"
#include "vector.h"
#include "bullet.h"
class oAsteroid
{
public:
	int iSpriteID = -1;
	int iQty;
	oAsteroid();
protected:
	int iScore = 0;
	//Dimension Variables
	int iWidth = 0;
	int iHeight = 0;
	int iRadius = 0;
	//Speed Variables
	float fSpeedMax = 0.f;
	float fSpeedMin = 0.f;
	//Rotation Variables
	float fSpriteTurnRate = 0.f;
	//Position Variables
	float fPosX = 0.f;
	float fPosY = 0.f;
	//Vector Variables
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	//Death Variables
	bool bIsDead = false;
	Position pos;
	Vector vNew = Vector(0.0f, 0.0f);
private:
	
};
class oAsteroidLarge : public oAsteroid
{
public:
	oAsteroidLarge();
	void Initialise(oSpawnController& a_spawncontroller, int a_AsteroidNumber, const char* a_AsteroidLargeImageFileName);
	void Update(oAsteroidLarge& a_asteroidlarge);
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetPos(float& a_PosX, float& a_PosY);
	void GetRadius(int &a_Radius);
	void SetRotation(float &a_CurrentRotation);
	void SetIsDead(bool a_IsDead);
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