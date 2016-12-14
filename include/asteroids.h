////////////////////////////////////////////////////////////////////////////
// File: <asteroids.h>
// Author: <Alex Kitching>
// Date Created: <01/12/16>
// Brief: <Header file for all Asteroid classes, functions and variables.>
///////////////////////////////////////////////////////////////////////////
#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_

#include "position.h"
#include "vector.h"
#include "Spawncontroller.h"

class oAsteroid
{
public:
	oAsteroid() {};
	~oAsteroid() {};
	int iSpriteID;
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetRadius(int &a_Radius);
	void GetPos(float &a_fPosX, float &a_fPosY);
	void SetRotation(float &a_CurrentRotation);
	void SetIsActive(bool a_IsActive);
	void SetHasCollied(bool a_HasCollided);
	void SetScoreUpdated(bool a_ScoreUpdated);
	bool ScoreUpdated();
	bool HasCollided();
	bool IsActive();
	friend class oObjectUpdateController;
	//SpriteFileArray
	char const c_cLargeAsteroidFileName[5][35] = { { "./images/LargeAsteroid1.png" },{ "./images/LargeAsteroid2.png" },{ "./images/LargeAsteroid3.png" },{ "./images/LargeAsteroid4.png" },{ "./images/LargeAsteroid1.png" } };
	char const c_cMediumAsteroidFileName[3][35] = { { "./images/MediumAsteroid1.png" },{ "./images/MediumAsteroid2.png" },{ "./images/MediumAsteroid3.png" } };
	char const c_cSmallAsteroidFileName[3][35] = { { "./images/SmallAsteroid1.png" },{ "./images/SmallAsteroid2.png" },{ "./images/SmallAsteroid3.png" } };
	float fLargeAsteroidRespawnPosArray[5][2] = { {872.f, 300.f}, {400.f, -72.f}, {-72, 300}, {200, 672}, {600, 672} };

protected:
	int iScore;
	//Dimension Variables
	int iWidth;
	int iHeight;
	int iRadius;
	//Speed Variables
	float c_fSpeedMax;
	float c_fSpeedMin;
	//Rotation Variables
	float fSpriteTurnRate;
	//Position Variables
	float fPosX;
	float fPosY;
	//Vector Variables
	float fVNewX;
	float fVNewY;
	//Death Variables
	bool bHasCollided;
	bool bShattered;
	bool bIsActive;
	bool bScoreUpdated;
	Position pos;
	Vector vNew;
};
class oAsteroidLarge : public oAsteroid
{
public:
	oAsteroidLarge();
	~oAsteroidLarge() {};
	void Initialise(const char* a_AsteroidLargeImageFileName);
	void Draw(oSpawncontroller& a_Spawncontroller, int a_currentAsteroid);
	void Destroy(oAsteroidLarge& a_asteroidlarge);
	void ResetVars(oAsteroidLarge& a_asteroidlarge);
	void Respawn(oAsteroidLarge& a_asteroidlarge, int a_currentAsteroid);
	int Score(oAsteroidLarge& a_asteroidlarge);
};

class oAsteroidMedium : public oAsteroid
{
public:
	oAsteroidMedium();
	~oAsteroidMedium() {};
	void Initialise(const char * oAsteroidMediumImageFileName);
	void Draw(float a_AsteroidLargePosX, float a_AsteroidLargePosY);
	void Destroy(oAsteroidMedium& a_asteroidmedium);
	void ResetVars(oAsteroidMedium& a_asteroidmedium);
	int Score(oAsteroidMedium& a_asteroidmedium);
};

class oAsteroidSmall : public oAsteroid
{
public:
	oAsteroidSmall();
	~oAsteroidSmall() {};
	void Initialise(const char * a_AsteroidSmallImageFileName);
	void Draw(float a_AsteroidMediumPosX, float a_AsteroidMediumPosY);
	void Destroy(oAsteroidSmall& a_asteroidsmall);
	void ResetVars(oAsteroidSmall& a_asteroidsmall);
	int Score(oAsteroidSmall& a_asteroidsmall);
};
#endif // !_ASTEROIDS_H_