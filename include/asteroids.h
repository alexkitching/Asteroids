#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_
#include "position.h"

class oAsteroidLarge
{
public:
	oAsteroidLarge();
	void Initialise(const char* a_AsteroidLargeImageFileName);
	void SetSpriteID(int a_id);
	void Update(oAsteroidLarge& a_asteroidlarge);
	void CheckSpawnCollision(oAsteroidLarge& a_asteroidlarge);


	int iSpriteID = -1;

	//Speed Variables
	float ixSpeedMax = 2.0f, iySpeedMax = 2.0f;
	float ixSpeed = 0.0f, iySpeed = 0.0f;

	//Rotation Variables
	int iSpriteTurnRate = 0;

	//Score Variables
	const int Score = 20;
	//Death Variables
	bool bIsDead = false;

private:
	const int iWidth = 72, iHeight = 72;

	Position pos;
};

class oAsteroidSmall
{
public:
	oAsteroidSmall();
	void Initialise(oAsteroidSmall& a_asteroidsmall, const char* a_AsteroidSmallImageFileName);
	void Update(oAsteroidSmall& a_asteroidsmall);

	int iSpriteID = -1;

	//Speed Variables
	float ixSpeedMax = 5.0f, iySpeedMax = 5.0f;
	float ixSpeed = 0, iySpeed = 0;

	//Rotation Variables
	int iSpriteTurnRate = 0;

	//Score Variables
	const int Score = 50;
	//Death Variables
	bool bIsDead = false;

private:
	const int iWidth = 36, iHeight = 36;
	Position pos;
};
#endif