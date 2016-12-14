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
	oAsteroid() {}; //Constructor
	~oAsteroid() {}; //Destructor

	//General Variables
	int iSpriteID;

	//Declare Get Functions
	void GetDimensions(int& a_riWidth, int& a_riHeight);
	void GetRadius(int& a_rRadius);
	void GetPos(float& a_rfPosX, float& a_rfPosY);

	//Declare Set Functions
	void SetRotation(float& a_rfCurrentRotation);
	void SetIsActive(bool a_bIsActive);
	void SetHasCollied(bool a_bHasCollided);
	void SetScoreUpdated(bool a_bScoreUpdated);

	//Declare Bool Functions
	bool ScoreUpdated();
	bool HasCollided();
	bool IsActive();

	//Friend Classes
	friend class oObjectUpdateController;

	//SpriteFileArray
	char const c_acLargeAsteroidFileName[5][35] = { { "./images/LargeAsteroid1.png" },{ "./images/LargeAsteroid2.png" },{ "./images/LargeAsteroid3.png" },{ "./images/LargeAsteroid4.png" },{ "./images/LargeAsteroid1.png" } };
	char const c_acMediumAsteroidFileName[3][35] = { { "./images/MediumAsteroid1.png" },{ "./images/MediumAsteroid2.png" },{ "./images/MediumAsteroid3.png" } };
	char const c_acSmallAsteroidFileName[3][35] = { { "./images/SmallAsteroid1.png" },{ "./images/SmallAsteroid2.png" },{ "./images/SmallAsteroid3.png" } };
	float afLargeAsteroidRespawnPosArray[5][2] = { {872.f, 300.f}, {400.f, -72.f}, {-72.f, 300.f}, {200.f, 672.f}, {600.f, 672.f} };

protected:

	//Score Variables
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
	Position pos;

	//Vector Variables
	float fVNewX;
	float fVNewY;
	Vector vNew;

	//Death Variables
	bool bHasCollided;
	bool bShattered;
	bool bIsActive;
	bool bScoreUpdated;

	
};
class oAsteroidLarge : public oAsteroid
{
public:

	oAsteroidLarge(); //Constructor
	~oAsteroidLarge() {}; //Destructor

	//Declare Functions
	void Initialise(const char* a_rAsteroidLargeImageFileName);
	void Draw(oSpawncontroller& a_rSpawncontroller, int a_currentAsteroid);
	void Destroy(oAsteroidLarge& a_rAsteroidLarge);
	void ResetVars(oAsteroidLarge& a_rAsteroidLarge);
	void Respawn(oAsteroidLarge& a_rAsteroidLarge, int a_currentAsteroid);
	int Score(oAsteroidLarge& a_rAsteroidLarge);
};

class oAsteroidMedium : public oAsteroid
{
public:
	
	oAsteroidMedium(); //Constructor
	~oAsteroidMedium() {}; //Destructor

	//Declare Functions
	void Initialise(const char* c_pcAsteroidMediumImageFileName);
	void Draw(float a_rAsteroidLargePosX, float a_rAsteroidLargePosY);
	void Destroy(oAsteroidMedium& a_rAsteroidMedium);
	void ResetVars(oAsteroidMedium& a_rAsteroidMedium);
	int Score(oAsteroidMedium& a_rAsteroidMedium);
};

class oAsteroidSmall : public oAsteroid
{
public:
	
	oAsteroidSmall(); //Constructor
	~oAsteroidSmall() {}; //Destructor

	//Declare Functions
	void Initialise(const char* c_pcAsteroidSmallImageFileName);
	void Draw(float a_rAsteroidMediumPosX, float a_rAsteroidMediumPosY);
	void Destroy(oAsteroidSmall& a_rAsteroidSmall);
	void ResetVars(oAsteroidSmall& a_rAsteroidSmall);
	int Score(oAsteroidSmall& a_rAsteroidSmall);
};
#endif // !_ASTEROIDS_H_