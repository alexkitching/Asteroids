////////////////////////////////////////////////////////////////////
// File: <Spaceship.cpp>
// Author: <Alex Kitching>
// Date Created: <30/11/16>
// Brief: <Source file for the Spaceship Class.>
////////////////////////////////////////////////////////////////////

#include "Spaceship.h"
#include "UGFW.h"
#define _USE_MATH_DEFINES
#include <math.h>

extern float g_fDeltaTime;
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oSpaceship::Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName)
{
	a_Spaceship.fTotalVelocity = 0.f;
	a_Spaceship.fCurrentTurnRate = 0.f;
	a_Spaceship.fPosX = 0.f;
	a_Spaceship.fPosY = 0.f;
	a_Spaceship.fVNewX = 0.f;
	a_Spaceship.fVNewY = 0.f;
	a_Spaceship.fFireDelay = 0.f;
	a_Spaceship.bIsActive = false;
	a_Spaceship.bCollision = false;
	a_Spaceship.fSpawnTime = 3.f;
	a_Spaceship.vNew = (0.f, 0.f);
	a_Spaceship.iSpriteID = UG::CreateSprite(a_SpaceshipImageFileName, (float)a_Spaceship.c_iWidth, (float)a_Spaceship.c_iHeight);

}

void oSpaceship::Draw(oSpaceship& a_Spaceship, float a_fXPos, float a_fYPos)
{
	a_Spaceship.bIsActive = true;
	a_Spaceship.pos.Set(a_fXPos, a_fYPos);
	UG::DrawSprite(a_Spaceship.iSpriteID);
	UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
	a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
}

void oSpaceship::Destroy(oSpaceship& a_Spaceship, oLivescontroller& a_Livescontroller)
{
	a_Livescontroller.UpdateLives(-1);
	a_Spaceship.ResetVars(a_Spaceship);
	UG::StopDrawingSprite(a_Spaceship.iSpriteID);
	UG::DestroySprite(a_Spaceship.iSpriteID);
	a_Spaceship.iSpriteID = -1;
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_fireKey, short a_exitKey)
{
	a_Spaceship.upKey = a_upKey;
	a_Spaceship.downKey = a_downKey;
	a_Spaceship.leftKey = a_leftKey;
	a_Spaceship.rightKey = a_rightKey;
	a_Spaceship.fireKey = a_fireKey;
	a_Spaceship.exitKey = a_exitKey;
}
void oSpaceship::CheckCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oLivescontroller& a_Livescontroller, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount, int& a_UFOEasydeathcount, int& a_UFOHarddeathcount)
{
	//Check for Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_aAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{

				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
					a_aAsteroidLargeArray[i].Destroy(a_aAsteroidLargeArray[i]);
					++a_asteroidlargedeathcount;
				}
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
	//Check for Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_aAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{
				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
					a_aAsteroidMediumArray[i].Destroy(a_aAsteroidMediumArray[i]);
					++a_asteroidmediumdeathcount;
				}
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
	//Check for Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_aAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{
				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
					a_aAsteroidSmallArray[i].Destroy(a_aAsteroidSmallArray[i]);
					++a_asteroidsmalldeathcount;
				}
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
	//Check for UFOEasy Collision
	if (a_UFOEasy.IsActive())
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_UFOEasy.GetPos(fUFOPosX, fUFOPosY);
		a_UFOEasy.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((fPosX - c_fRadius < fUFOPosX + iHalfUFOWidth && fPosX + c_fRadius > fUFOPosX - iHalfUFOWidth) && (fPosY - c_fRadius < fUFOPosY + iHalfUFOHeight && fPosY + c_fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (bIsActive == true)
			{
				a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
				a_Livescontroller.UpdateLives(-1);
				a_UFOEasy.Destroy(a_UFOEasy);
				++a_UFOEasydeathcount;
			}
		}
		else
		{
			a_Spaceship.bCollision = false;
		}
	}
	//Check for UFOHard Collision
	if (a_UFOHard.IsActive())
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_UFOHard.GetPos(fUFOPosX, fUFOPosY);
		a_UFOHard.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((fPosX - c_fRadius < fUFOPosX + iHalfUFOWidth && fPosX + c_fRadius > fUFOPosX - iHalfUFOWidth) && (fPosY - c_fRadius < fUFOPosY + iHalfUFOHeight && fPosY + c_fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (bIsActive == true)
			{
				a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
				a_Livescontroller.UpdateLives(-1);
				a_UFOHard.Destroy(a_UFOHard);
				++a_UFOHarddeathcount;
			}
		}
		else
		{
			a_Spaceship.bCollision = false;
		}
	}
}

void oSpaceship::CheckSpawnCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray)
{
	for (int i = 0; i < 5; ++i)
	{
		if (a_aAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
	for (int i = 0; i < 15; ++i)
	{
		if (a_aAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
	for (int i = 0; i < 45; ++i)
	{
		if (a_aAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				a_Spaceship.bCollision = true;
			}
			else
			{
				a_Spaceship.bCollision = false;
			}
		}
	}
}

void oSpaceship::ResetVars(oSpaceship& a_Spaceship)
{
	a_Spaceship.fTotalVelocity = 0.f;
	a_Spaceship.fCurrentTurnRate = 0.f;
	a_Spaceship.fPosX = 0.f;
	a_Spaceship.fPosY = 0.f;
	a_Spaceship.fVNewX = 0.f;
	a_Spaceship.fVNewY = 0.f;
	a_Spaceship.fFacingAngleDeg = 90.0;
	a_Spaceship.fMovementAngleDeg = 90.0;
	a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.c_degtorad;
	a_Spaceship.fFireDelay = 0.f;
	a_Spaceship.bIsActive = false;
	a_Spaceship.bCollision = false;
	a_Spaceship.fSpawnTime = 3.f;
	a_Spaceship.vNew = Vector(0.f, 0.f);
}

void oSpaceship::Respawn(oSpaceship & a_Spaceship)
{
	bool bHasSpawned = false;
	while (bHasSpawned == false)
	{
		if (!a_Spaceship.bCollision)
		{
			a_Spaceship.iSpriteID = UG::CreateSprite(a_Spaceship.c_cSpaceshipFileName, (float)a_Spaceship.c_iWidth, (float)a_Spaceship.c_iHeight);
			a_Spaceship.Draw(a_Spaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
			bHasSpawned = true;
		}
		else if (a_Spaceship.bCollision)
		{
			//Do nothing
		}
	}
}

void oSpaceship::GetPos(float& a_fPosX, float& a_fPosY)
{
	a_fPosX = fPosX;
	a_fPosY = fPosY;
}

void oSpaceship::GetRadius(float& a_fRadius)
{
	a_fRadius = c_fRadius;
}

void oSpaceship::SetCollision(bool a_collision)
{
	bCollision = a_collision;
}

bool oSpaceship::IsActive()
{
	return bIsActive;
}

float oSpaceship::AngleWrap(float x)
{
	float y;
	y = fmodf(x, 360);
	if (y < 0)
	{
		y += 360;
		return y;
	}
	else if (y > 1)
	{
		y -= 360;
		return y;
	}
	return x;
}
