#ifndef _UFO_H_
#define _UFO_H_

#include "Position.h"
#include "vector.h"

class oUFO
{
public:
	oUFO() {};
	int iSpriteID;

	friend class oObjectUpdateController;

	char const cUFOFileName[17] = { "./images/UFO.png" };

protected:
	int iScore;
	//Dimension Variables
	int iWidith;
	int iHeight;
	//Speed Variables
	float fSpeed;
	//Position Variables
	float fPosX;
	float fPosY;
	//Vector Variables
	float fVNewX;
	float fVNewY;
	//Death Variables
	bool bHasCollided;
	bool bIsActive;
	bool bScoreUpdated;

	Position pos;
	Vector vNew;
};

class oUFOEasy : public oUFO
{
public:
	oUFOEasy();
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	void Destroy(oUFOEasy& a_ufoeasy);
private:

};

class oUFOHard : public oUFO
{
public:
	oUFOHard();
	void Initialise(const char* a_UFOImageFileName);
	void Draw();
	void Destroy(oUFOHard& a_ufohard);
private:

};
#endif
