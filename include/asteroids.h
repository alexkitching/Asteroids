#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_
#include "position.h"
#include "spawncontroller.h"
#include "vector.h"
#include <vector>
class oAsteroid
{
public:
	int iSpriteID = -1;
	int iQty;
	oAsteroid();
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetPos(float& a_PosX, float& a_PosY);
	void GetRadius(int &a_Radius);
	void SetRotation(float &a_CurrentRotation);
	void SetIsDead(bool a_IsDead);
	bool IsDead();
	friend class oObjectUpdateController;
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
	//SpriteFileArray
	char const cMediumAsteroidFileName[3][35] = { { "./images/MediumAsteroid1.png" }, { "./images/MediumAsteroid2.png" }, { "./images/MediumAsteroid3.png" } };
	char const cSmallAsteroidFileName[3][35] = { { "./images/SmallAsteroid1.png" }, { "./images/SmallAsteroid2.png" }, { "./images/SmallAsteroid3.png" } };
	//Death Variables
	bool bShattered = false;
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
private:	
	
};

class oAsteroidMedium : public oAsteroid
{
public:
	oAsteroidMedium(float a_AsteroidLargePosX, float a_AsteroidlargePosY, int a_currentAsteroid);
	void Initialise(const char * oAsteroidMediumImageFileName, float a_AsteroidLargePosX, float a_AsteroidlargePosY);
private:
};

class oAsteroidSmall : public oAsteroid
{
public:
	oAsteroidSmall(float a_AsteroidMediumPosX, float a_AsteroidMediumPosY, int a_currentAsteroid);
	void Initialise(const char * a_AsteroidSmallImageFileName, float a_oAsteroidMediumPosX, float a_oAsteroidMediumPosY);
	void Update(oAsteroidSmall& a_asteroidsmall);

private:
};
#endif