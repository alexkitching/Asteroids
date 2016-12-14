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

void oSpaceship::Initialise(oSpaceship& a_rSpaceship, const char* a_rSpaceshipImageFileName)
{
	a_rSpaceship.fTotalVelocity = 0.f;	//Initialise Variables
	a_rSpaceship.fCurrentTurnRate = 0.f;
	a_rSpaceship.fPosX = 0.f;
	a_rSpaceship.fPosY = 0.f;
	a_rSpaceship.fVNewX = 0.f;
	a_rSpaceship.fVNewY = 0.f;
	a_rSpaceship.fFireDelay = 0.f;
	a_rSpaceship.bIsActive = false;
	a_rSpaceship.bCollision = false;
	a_rSpaceship.fSpawnTime = 3.f;
	a_rSpaceship.vNew = (0.f, 0.f);
	a_rSpaceship.iSpriteID = UG::CreateSprite(a_rSpaceshipImageFileName, (float)a_rSpaceship.c_iWidth, (float)a_rSpaceship.c_iHeight); //Create Sprite

}

void oSpaceship::Draw(oSpaceship& a_rSpaceship, float a_fXPos, float a_fYPos) 
{
	a_rSpaceship.bIsActive = true; //Set Active
	a_rSpaceship.pos.Set(a_fXPos, a_fYPos);
	UG::DrawSprite(a_rSpaceship.iSpriteID); //Draw Spaceship
	UG::MoveSprite(a_rSpaceship.iSpriteID, a_rSpaceship.fPosX, a_rSpaceship.fPosY); //Move Spaceship
	a_rSpaceship.pos.Get(a_rSpaceship.fPosX, a_rSpaceship.fPosY);
}

void oSpaceship::Destroy(oSpaceship& a_rSpaceship, oLivescontroller& a_rLivescontroller)
{
	a_rLivescontroller.UpdateLives(-1); //Updates Lives
	a_rSpaceship.ResetVars(a_rSpaceship); //Reset Variables
	UG::StopDrawingSprite(a_rSpaceship.iSpriteID); //Stop Drawing Sprite
	UG::DestroySprite(a_rSpaceship.iSpriteID); //Destroy Sprite
	a_rSpaceship.iSpriteID = -1; //Reset ISpriteID
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship& a_rSpaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey,
	short a_fireKey, short a_exitKey)
{
	a_rSpaceship.upKey = a_upKey; //Set Movement Keys
	a_rSpaceship.downKey = a_downKey;
	a_rSpaceship.leftKey = a_leftKey;
	a_rSpaceship.rightKey = a_rightKey;
	a_rSpaceship.fireKey = a_fireKey;
	a_rSpaceship.exitKey = a_exitKey;
}
void oSpaceship::CheckCollision(oSpaceship & a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
								oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller,
								int& a_rAsteroidLargedeathcount, int& a_rAsteroidMediumdeathcount, int& a_rAsteroidSmalldeathcount, int& a_rUFOEasydeathcount,
								int& a_rUFOHarddeathcount)
{
	//Check for Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_paAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (bIsActive == true)
				{
					a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
					a_paAsteroidLargeArray[i].Destroy(a_paAsteroidLargeArray[i]); //Destroy Asteroid
					++a_rAsteroidLargedeathcount; //Increase Asteroid Death Count
				}
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false; 
			}
		}
	}
	//Check for Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_paAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (bIsActive == true)
				{
					a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
					a_paAsteroidMediumArray[i].Destroy(a_paAsteroidMediumArray[i]); //Destroy Asteroid
					++a_rAsteroidMediumdeathcount; //Increase Asteroid Death Count
				}
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false;
			}
		}
	}
	//Check for Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_paAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (bIsActive == true)
				{
					a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
					a_paAsteroidSmallArray[i].Destroy(a_paAsteroidSmallArray[i]); //Destroy Asteroid
					++a_rAsteroidSmalldeathcount; //Increase Asteroid Death Count
				}
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false;
			}
		}
	}
	//Check for UFOEasy Collision
	if (a_rUFOEasy.IsActive())
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_rUFOEasy.GetPos(fUFOPosX, fUFOPosY);
		a_rUFOEasy.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((fPosX - c_fRadius < fUFOPosX + iHalfUFOWidth && fPosX + c_fRadius > fUFOPosX - iHalfUFOWidth) && (fPosY - c_fRadius < fUFOPosY + iHalfUFOHeight &&
			fPosY + c_fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (bIsActive == true)
			{
				a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
				a_rUFOEasy.Destroy(a_rUFOEasy); //Destroy UFO
				++a_rUFOEasydeathcount; //Increase UFO Death Count
			}
		}
		else
		{
			a_rSpaceship.bCollision = false;
		}
	}
	//Check for UFOHard Collision
	if (a_rUFOHard.IsActive())
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_rUFOHard.GetPos(fUFOPosX, fUFOPosY);
		a_rUFOHard.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((fPosX - c_fRadius < fUFOPosX + iHalfUFOWidth && fPosX + c_fRadius > fUFOPosX - iHalfUFOWidth) && (fPosY - c_fRadius < fUFOPosY + iHalfUFOHeight &&
			fPosY + c_fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (bIsActive == true)
			{
				a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
				a_rUFOHard.Destroy(a_rUFOHard); //Destroy UFO
				++a_rUFOHarddeathcount; //Increase UFO Death Count
			}
		}
		else
		{
			a_rSpaceship.bCollision = false;
		}
	}
}

void oSpaceship::CheckSpawnCollision(oSpaceship & a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
	oAsteroidSmall* a_paAsteroidSmallArray)
{
	for (int i = 0; i < 5; ++i) //Checks to See if Spawn Area Is Occupied With Asteroids
	{
		if (a_paAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				//Collision
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false;
			}
		}
	} 
	for (int i = 0; i < 15; ++i) //Checks to See if Spawn Area Is Occupied With Asteroids
	{
		if (a_paAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				//Collision
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false;
			}
		}
	}
	for (int i = 0; i < 45; ++i) //Checks to See if Spawn Area Is Occupied With Asteroids
	{
		if (a_paAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < c_fSpawnRadius + (float)iAsteroidRadius)
			{
				//Collision
				a_rSpaceship.bCollision = true;
			}
			else
			{
				a_rSpaceship.bCollision = false;
			}
		}
	}
}

void oSpaceship::ResetVars(oSpaceship& a_rSpaceship) // Reset Variables
{
	a_rSpaceship.fTotalVelocity = 0.f;
	a_rSpaceship.fCurrentTurnRate = 0.f;
	a_rSpaceship.fPosX = 0.f;
	a_rSpaceship.fPosY = 0.f;
	a_rSpaceship.fVNewX = 0.f;
	a_rSpaceship.fVNewY = 0.f;
	a_rSpaceship.fFacingAngleDeg = 90.0;
	a_rSpaceship.fMovementAngleDeg = 90.0;
	a_rSpaceship.fFacingAngleRad = a_rSpaceship.fFacingAngleDeg * a_rSpaceship.c_degtorad;
	a_rSpaceship.fFireDelay = 0.f;
	a_rSpaceship.bIsActive = false;
	a_rSpaceship.bCollision = false;
	a_rSpaceship.fSpawnTime = 3.f;
	a_rSpaceship.vNew = Vector(0.f, 0.f);
}

void oSpaceship::Respawn(oSpaceship & a_rSpaceship)
{
	bool bHasSpawned = false;
	while (bHasSpawned == false)
	{
		if (!a_rSpaceship.bCollision) // Check Spawn Collision
		{
			a_rSpaceship.iSpriteID = UG::CreateSprite(a_rSpaceship.c_cSpaceshipFileName, (float)a_rSpaceship.c_iWidth, (float)a_rSpaceship.c_iHeight); //Create Sprite
			a_rSpaceship.Draw(a_rSpaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f); // Draw Sprite
			bHasSpawned = true;
		}
		else if (a_rSpaceship.bCollision)
		{
			//Do nothing
		}
	}
}

void oSpaceship::GetPos(float& a_rfPosX, float& a_rfPosY)
{
	a_rfPosX = fPosX;
	a_rfPosY = fPosY;
}

void oSpaceship::GetRadius(float& a_rfRadius)
{
	a_rfRadius = c_fRadius;
}

void oSpaceship::SetCollision(bool a_collision)
{
	bCollision = a_collision;
}

bool oSpaceship::IsActive()
{
	return bIsActive;
}

float oSpaceship::AngleWrap(float x) // Wraps Angle Around if Greater Than 360 or Less Than 1
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
