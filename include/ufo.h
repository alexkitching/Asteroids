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

	oUFO() {};
	~oUFO() {};
	int iSpriteID;
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetPos(float& a_PosX, float& a_PosY);
	void SetIsActive(bool a_IsActive);
	void SetCanSpawn(bool a_CanSpawn);
	void SetHasCollied(bool a_HasCollided);
	void SetScoreUpdated(bool a_ScoreUpdated);
	bool ScoreUpdated();
	bool HasCollided();
	bool IsActive();
	bool CanSpawn();
	int BulletSpeed();
	friend class oObjectUpdateController;
	friend class oUFOBullet;
	char const cUFOFileName[2][23] = { "./images/UFO.png", "./images/UFOsmall.png" };

protected:
	int iScore;
	//Dimension Variables
	int iWidth;
	int iHeight;
	//Speed Variables
	float fSpeed;
	bool bDirection;
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
	oUFOEasy();
	~oUFOEasy() {};
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	Vector NewFireDirection();
	void Destroy(oUFOEasy& a_UFOEasy);
	void ResetVars(oUFOEasy& a_UFOEasy);
	int Score(oUFOEasy& a_UFOEasy);
private:

};

class oUFOHard : public oUFO
{
public:
	oUFOHard();
	~oUFOHard() {};
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	void Destroy(oUFOHard& a_UFOHard);
	void ResetVars(oUFOHard& a_UFOHard);
	int Score(oUFOHard& a_UFOHard);
private:
};
#endif // !_UFO_H_
