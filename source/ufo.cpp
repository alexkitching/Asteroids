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
	iSpriteID = -1;
	iScore = 200;
	iWidth = 55;
	iHeight = 28;
	fSpeed = 1.f;
	bDirection;
	fThinkingTime = 0.f;
	fMaxThinkingTime = 0.5f;
	fShootingDelay = 0.f;
	fMaxShootingDelay = 3.0f;
	fBulletSpeed = 2.0;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
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
	iSpriteID = UG::CreateSprite(a_UFOImageFileName, (float)iWidth, (float)iHeight);
	bDirection = rand() % 2;
	bool bUpDown;
	if (!bDirection) // Move Left
	{
		bUpDown = rand() % 2;
		if (!bUpDown) // Move Down
		{
			vNew = vLeftDown;
		}
		else if (bUpDown) // Move Up
		{
			vNew = vLeftUp;
		}
	}
	else if (bDirection) // Move Right
	{
		bUpDown = rand() % 2;
		if (!bUpDown) // Move Down
		{
			vNew = vRightDown;
		}
		else if (bUpDown) // Move Up
		{
			vNew = vRightUp;
		}
	}
}

void oUFOEasy::Draw()
{
	bHasCollided = false;
	bIsActive = true;
	bool bSpawnUpDown;
	if (!bDirection) // Is Moving Left
	{
		bSpawnUpDown = rand() % 2;
		if (!bSpawnUpDown) //Spawn Down
		{
			pos = posRightBottom;
		}
		else if (bSpawnUpDown) // Spawn Up
		{
			pos = posRightTop;
		}
	}
	else if (bDirection) // Is Moving Right
	{
		bSpawnUpDown = rand() % 2;
		if (!bSpawnUpDown) //Spawn Down
		{
			pos = posLeftBottom;
		}
		else if (bSpawnUpDown) // Spawn Up
		{
			pos = posLeftTop;
		}
	}
	UG::DrawSprite(iSpriteID);

	UG::MoveSprite(iSpriteID, pos.fX, pos.fY);
}

Vector oUFOEasy::NewFireDirection()
{
	Vector vFireDirection;
	int FireArcDeg;
	FireArcDeg = rand() % 361;
	vFireDirection.fX = cosf(FireArcDeg);
	vFireDirection.fY = sinf(FireArcDeg);
	vFireDirection *= fBulletSpeed; // Increase Speed
	return vFireDirection;
}

void oUFOEasy::Destroy(oUFOEasy & a_UFOEasy)
{
	a_UFOEasy.bHasCollided = true;
	UG::StopDrawingSprite(a_UFOEasy.iSpriteID);
	UG::DestroySprite(a_UFOEasy.iSpriteID);
	a_UFOEasy.iSpriteID = -1;
}

void oUFOEasy::ResetVars(oUFOEasy & a_UFOEasy)
{
	a_UFOEasy.pos.fX = 0.f;
	a_UFOEasy.pos.fY = 0.f;
	a_UFOEasy.vNew.fX = 0.f;
	a_UFOEasy.vNew.fY = 0.f;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
}

int oUFOEasy::Score(oUFOEasy & a_UFOEasy)
{
	return a_UFOEasy.iScore;
}

void oUFO::GetDimensions(int & a_iWidth, int & a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oUFO::GetPos(float & a_PosX, float & a_PosY)
{
	a_PosX = pos.fX;
	a_PosY = pos.fY;
}

void oUFO::SetIsActive(bool a_IsActive)
{
	bIsActive = a_IsActive;
}

void oUFO::SetCanSpawn(bool a_CanSpawn)
{
	bCanSpawn = a_CanSpawn;
}

void oUFO::SetHasCollied(bool a_HasCollided)
{
	bHasCollided = a_HasCollided;
}

void oUFO::SetScoreUpdated(bool a_ScoreUpdated)
{
	bScoreUpdated = a_ScoreUpdated;
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

int oUFO::BulletSpeed()
{
	return fBulletSpeed;
}

oUFOHard::oUFOHard()
{
	iSpriteID = -1;
	iScore = 1000;
	iWidth = 28;
	iHeight = 14;
	fSpeed = 2.f;
	bDirection;
	fThinkingTime = 0.f;
	fMaxThinkingTime = 1.5f;
	fShootingDelay = 0.f;
	fMaxShootingDelay = 1.0f;
	fBulletSpeed = 4.0;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
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
	iSpriteID = UG::CreateSprite(a_UFOImageFileName, (float)iWidth, (float)iHeight);
	bDirection = rand() % 2;
	bool bUpDown;
	if (!bDirection) // Move Left
	{
		vNew = vLeft;
	}
	else if (bDirection) // Move Right
	{
		vNew = vRight;
	}
}

void oUFOHard::Draw()
{
	bHasCollided = false;
	bIsActive = true;
	bool bSpawnUpDown;
	if (!bDirection) // Is Moving Left
	{
		bSpawnUpDown = rand() % 2;
		if (!bSpawnUpDown) //Spawn Down
		{
			pos = posRightBottom;
		}
		else if (bSpawnUpDown) // Spawn Up
		{
			pos = posRightTop;
		}
	}
	else if (bDirection) // Is Moving Right
	{
		bSpawnUpDown = rand() % 2;
		if (!bSpawnUpDown) //Spawn Down
		{
			pos = posLeftBottom;
		}
		else if (bSpawnUpDown) // Spawn Up
		{
			pos = posLeftTop;
		}
	}
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, pos.fX, pos.fY);
}

void oUFOHard::Destroy(oUFOHard & a_UFOHard)
{
	a_UFOHard.bHasCollided = true;
	UG::StopDrawingSprite(a_UFOHard.iSpriteID);
	UG::DestroySprite(a_UFOHard.iSpriteID);
	a_UFOHard.iSpriteID = -1;
}

void oUFOHard::ResetVars(oUFOHard & a_UFOHard)
{
	a_UFOHard.pos.fX = 0.f;
	a_UFOHard.pos.fY = 0.f;
	a_UFOHard.vNew.fX = 0.f;
	a_UFOHard.vNew.fY = 0.f;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false;
	bCanSpawn = true;
}

int oUFOHard::Score(oUFOHard & a_UFOHard)
{
	return a_UFOHard.iScore;
}
