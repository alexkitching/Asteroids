////////////////////////////////////////////////////////////////////////////
// File: <ufo.cpp>
// Author: <Alex Kitching>
// Date Created: <13/12/16>
// Brief: <Source file for the all UFO Classes, functions and variables.>
///////////////////////////////////////////////////////////////////////////

#include "UGFW.h"
#include "Spaceship.h"
#include "ufo.h"
#include <stdlib.h>
#include <math.h>

extern int g_iScreenWidth;

oUFOEasy::oUFOEasy()
{
	//General Variables
	iSpriteID = -1;
	iScore = 200;
	//Dimension Variables
	iWidth = 55;
	iHeight = 28;
	//Speed Variables
	fSpeed = 1.f;
	iDirection;
	fThinkingTime = 0.f;
	fMaxThinkingTime = 0.5f;
	//Firing Varibles 
	fShootingDelay = 0.f;
	fMaxShootingDelay = 3.0f;
	fBulletSpeed = 2.0;
	//Status Variables
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
	//Position Variables
	vNew = Vector(0.0f, 0.0f);
	vLeftUp = Vector(-fSpeed, fSpeed);
	vLeftDown = Vector(-fSpeed, -fSpeed);
	vRightDown = Vector(fSpeed, -fSpeed);
	vRightUp = Vector(fSpeed, fSpeed);
	posLeftTop = Vector((float)(0 - iWidth), 500);
	posLeftBottom = Vector((float)(0 - iWidth), 100);
	posRightTop = Vector((float)(g_iScreenWidth + iWidth), 500.f);
	posRightBottom = Vector((float)(g_iScreenWidth + iWidth), 100.f);
}

void oUFOEasy::Initialise(const char * a_UFOImageFileName)
{
	iSpriteID = UG::CreateSprite(a_UFOImageFileName, (float)iWidth, (float)iHeight); //Create UFO Sprite
	iDirection = rand() % 2; //Randomise Direction
	int iUpDown;
	if (!iDirection) // Move Left
	{
		iUpDown = rand() % 2;
		if (!iUpDown) // Move Down
		{
			vNew = vLeftDown;
		}
		else if (iUpDown) // Move Up
		{
			vNew = vLeftUp;
		}
	}
	else if (iDirection) // Move Right
	{
		iUpDown = rand() % 2; //Randomise Direction
		if (!iUpDown) // Move Down
		{
			vNew = vRightDown;
		}
		else if (iUpDown) // Move Up
		{
			vNew = vRightUp;
		}
	}
}

void oUFOEasy::Draw()
{
	bHasCollided = false; 
	bIsActive = true; //Set Active
	int iSpawnUpDown;
	if (!iDirection) // Is Moving Left
	{
		iSpawnUpDown = rand() % 2;
		if (!iSpawnUpDown) //Spawn Down
		{
			pos = posRightBottom;
		}
		else if (iSpawnUpDown) // Spawn Up
		{
			pos = posRightTop;
		}
	}
	else if (iDirection) // Is Moving Right
	{
		iSpawnUpDown = rand() % 2;
		if (!iSpawnUpDown) //Spawn Down
		{
			pos = posLeftBottom;
		}
		else if (iSpawnUpDown) // Spawn Up
		{
			pos = posLeftTop;
		}
	}
	UG::DrawSprite(iSpriteID); //Draw UFO Sprite

	UG::MoveSprite(iSpriteID, pos.fX, pos.fY); //Move UFO Sprite
}

Vector oUFOEasy::NewFireDirection() // Generate Random New Fire Direction
{
	Vector vFireDirection;
	int FireArcDeg;
	FireArcDeg = rand() % 361; // 360 Degree Firing Arc
	vFireDirection.fX = cosf((float)FireArcDeg);
	vFireDirection.fY = sinf((float)FireArcDeg);
	vFireDirection *= fBulletSpeed; // Increase Speed
	return vFireDirection;
}

void oUFOEasy::Destroy(oUFOEasy& a_rUFOEasy) //Destroy UFO
{
	a_rUFOEasy.bHasCollided = true;
	UG::StopDrawingSprite(a_rUFOEasy.iSpriteID); //Stop Drawing UFO Sprite
	UG::DestroySprite(a_rUFOEasy.iSpriteID); //Destroy UFO Sprite
	a_rUFOEasy.iSpriteID = -1; // Reset ISpriteID
}

void oUFOEasy::ResetVars(oUFOEasy& a_rUFOEasy)
{
	a_rUFOEasy.pos.fX = 0.f; //Reset Variables
	a_rUFOEasy.pos.fY = 0.f;
	a_rUFOEasy.vNew.fX = 0.f;
	a_rUFOEasy.vNew.fY = 0.f;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
}

int oUFOEasy::Score(oUFOEasy& a_rUFOEasy)
{
	return a_rUFOEasy.iScore;
}

void oUFO::GetDimensions(int & a_riWidth, int & a_riHeight)
{
	a_riWidth = iWidth, a_riHeight = iHeight;
}

void oUFO::GetPos(float & a_rfPosX, float & a_rfPosY)
{
	a_rfPosX = pos.fX;
	a_rfPosY = pos.fY;
}

void oUFO::SetIsActive(bool a_bIsActive)
{
	bIsActive = a_bIsActive;
}

void oUFO::SetCanSpawn(bool a_CanSpawn)
{
	bCanSpawn = a_CanSpawn;
}

void oUFO::SetHasCollied(bool a_bHasCollided)
{
	bHasCollided = a_bHasCollided;
}

void oUFO::SetScoreUpdated(bool a_bScoreUpdated)
{
	bScoreUpdated = a_bScoreUpdated;
}

bool oUFO::ScoreUpdated()
{
	return bScoreUpdated;
}

bool oUFO::HasCollided()
{
	return bHasCollided;
}

bool oUFO::IsActive()
{
	return bIsActive;
}

bool oUFO::CanSpawn()
{
	return bCanSpawn;
}

float oUFO::BulletSpeed()
{
	return fBulletSpeed;
}

oUFOHard::oUFOHard()
{
	//General Variables
	iSpriteID = -1;
	iScore = 1000;
	//Dimension Variables
	iWidth = 28;
	iHeight = 14;
	//Speed Variables
	fSpeed = 2.f;
	iDirection;
	fThinkingTime = 0.f;
	fMaxThinkingTime = 1.5f;
	//Firing Variables
	fShootingDelay = 0.f;
	fMaxShootingDelay = 1.0f;
	fBulletSpeed = 4.0;
	//Status Variables
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
	//Movement Variables
	vNew = Vector(0.0f, 0.0f);
	vLeft = Vector(-fSpeed, 0.f);
	vRight = Vector(fSpeed, 0.f);
	posLeftTop = Vector((float)(0 - iWidth), 450);
	posLeftBottom = Vector((float)(0 - iWidth), 150);
	posRightTop = Vector((float)(g_iScreenWidth + iWidth), 450.f);
	posRightBottom = Vector((float)(g_iScreenWidth + iWidth), 150.f);
}

void oUFOHard::Initialise(const char * a_UFOImageFileName)
{
	iSpriteID = UG::CreateSprite(a_UFOImageFileName, (float)iWidth, (float)iHeight); //Create UFO Sprite
	iDirection = rand() % 2; //Randomise Direction
	if (!iDirection) // Move Left
	{
		vNew = vLeft;
	}
	else if (iDirection) // Move Right
	{
		vNew = vRight;
	}
}

void oUFOHard::Draw()
{
	bHasCollided = false;
	bIsActive = true; //Set Active
	int iSpawnUpDown;
	if (!iDirection) // Is Moving Left
	{
		iSpawnUpDown = rand() % 2; //Randomise Spawn
		if (!iSpawnUpDown) //Spawn Down
		{
			pos = posRightBottom;
		}
		else if (iSpawnUpDown) // Spawn Up
		{
			pos = posRightTop;
		}
	}
	else if (iDirection) // Is Moving Right
	{
		iSpawnUpDown = rand() % 2; //Randomise Spawn
		if (!iSpawnUpDown) //Spawn Down
		{
			pos = posLeftBottom;
		}
		else if (iSpawnUpDown) // Spawn Up
		{
			pos = posLeftTop;
		}
	}
	UG::DrawSprite(iSpriteID); //Draw UFO Sprite
	UG::MoveSprite(iSpriteID, pos.fX, pos.fY); //Move UFO
}

void oUFOHard::Destroy(oUFOHard& a_rUFOHard) //Destroy UFO
{
	a_rUFOHard.bHasCollided = true;
	UG::StopDrawingSprite(a_rUFOHard.iSpriteID);
	UG::DestroySprite(a_rUFOHard.iSpriteID);
	a_rUFOHard.iSpriteID = -1;
}

void oUFOHard::ResetVars(oUFOHard& a_rUFOHard)
{
	a_rUFOHard.pos.fX = 0.f; //Reset Variables
	a_rUFOHard.pos.fY = 0.f;
	a_rUFOHard.vNew.fX = 0.f;
	a_rUFOHard.vNew.fY = 0.f;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
}

int oUFOHard::Score(oUFOHard& a_rUFOHard)
{
	return a_rUFOHard.iScore; //Get Score
}
