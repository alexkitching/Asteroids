////////////////////////////////////////////////////////////////////////////
// File: <ufo.h>
// Author: <Alex Kitching>
// Date Created: <13/12/16>
// Brief: <Header file for the all UFO Classes, functions and variables.>
///////////////////////////////////////////////////////////////////////////
#ifndef _UFO_H_
#define _UFO_H_

#include "vector.h"

class oUFO
{
public:

	oUFO() {}; //Constructor
	~oUFO() {}; //Destructor

	//General Variables
	int iSpriteID;

	//Functions
	void GetDimensions(int& a_riWidth, int& a_riHeight);
	void GetPos(float& a_rfPosX, float& a_rfPosY);
	void SetIsActive(bool a_bIsActive);
	void SetCanSpawn(bool a_CanSpawn);
	void SetHasCollied(bool a_bHasCollided);
	void SetScoreUpdated(bool a_bScoreUpdated);
	bool ScoreUpdated();
	bool HasCollided();
	bool IsActive();
	bool CanSpawn();
	float BulletSpeed();

	//Friend Classes
	friend class oObjectUpdateController;
	friend class oUFOBullet;

	//File Name
	char const cUFOFileName[2][23] = { "./images/UFO.png", "./images/UFOsmall.png" };

protected:

	//Score Variables
	int iScore;

	//Dimension Variables
	int iWidth;
	int iHeight;

	//Speed Variables
	float fSpeed;
	int iDirection;
	float fMaxThinkingTime;
	float fThinkingTime;
	float fMaxShootingDelay;
	float fShootingDelay;
	float fBulletSpeed;

	//Death Variables
	bool bHasCollided;
	bool bIsActive;
	bool bCanSpawn;
	bool bScoreUpdated;

	//Vector Variables
	Vector pos;
	Vector posLeftTop;
	Vector posLeftBottom;
	Vector posRightTop;
	Vector posRightBottom;
	Vector vNew;
	Vector vLeftUp;
	Vector vLeftDown;
	Vector vRightUp;
	Vector vRightDown;
	Vector vLeft;
	Vector vRight;
};

class oUFOEasy : public oUFO
{
public:

	oUFOEasy(); //Constructor
	~oUFOEasy() {}; //Destructor

	//Functions
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	Vector NewFireDirection();
	void Destroy(oUFOEasy& a_rUFOEasy);
	void ResetVars(oUFOEasy& a_rUFOEasy);
	int Score(oUFOEasy& a_rUFOEasy);

private:

};

class oUFOHard : public oUFO
{
public:

	oUFOHard(); //Constructor
	~oUFOHard() {}; //Destructor

	//Functions
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	void Destroy(oUFOHard& a_rUFOHard);
	void ResetVars(oUFOHard& a_rUFOHard);
	int Score(oUFOHard& a_rUFOHard);

private:
};
#endif // !_UFO_H_
