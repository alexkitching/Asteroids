#include "spaceship.h"
#include "UGFW.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern float g_DeltaTime;
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
	a_Spaceship.vNew = Vector(0.f, 0.f);
	a_Spaceship.iSpriteID = UG::CreateSprite(a_SpaceshipImageFileName, (float)a_Spaceship.iWidth, (float)a_Spaceship.iHeight);
	
}

void oSpaceship::Draw(oSpaceship& a_Spaceship, float a_fXPos, float a_fYPos)
{
	a_Spaceship.bIsActive = true;
	a_Spaceship.pos.Set(a_fXPos, a_fYPos);
	UG::DrawSprite(a_Spaceship.iSpriteID);
	UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
	a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
}

void oSpaceship::Destroy(oSpaceship& a_Spaceship)
{
	a_Spaceship.ResetVars(a_Spaceship);
	UG::StopDrawingSprite(a_Spaceship.iSpriteID);
	UG::DestroySprite(a_Spaceship.iSpriteID);
	a_Spaceship.iSpriteID = -1;
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship& a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short  a_breakKey, short a_fireKey, short a_exitKey)
{
	a_Spaceship.upKey = a_upKey;
	a_Spaceship.downKey = a_downKey;
	a_Spaceship.leftKey = a_leftKey;
	a_Spaceship.rightKey = a_rightKey;
	a_Spaceship.breakKey = a_breakKey;
	a_Spaceship.fireKey = a_fireKey;
	a_Spaceship.exitKey = a_exitKey;
}
void oSpaceship::CheckAsteroidCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oLivesController& a_livescontroller, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount)
{
	//Check for Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_asteroidlargearray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidlargearray[i].GetRadius(iAsteroidRadius);
			a_asteroidlargearray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				
				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship);
					a_livescontroller.UpdateLives(-1);
					a_asteroidlargearray[i].Destroy(a_asteroidlargearray[i]);
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
		if (a_asteroidmediumarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidmediumarray[i].GetRadius(iAsteroidRadius);
			a_asteroidmediumarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship);
					a_livescontroller.UpdateLives(-1);
					a_asteroidmediumarray[i].Destroy(a_asteroidmediumarray[i]);
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
		if (a_asteroidsmallarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidsmallarray[i].GetRadius(iAsteroidRadius);
			a_asteroidsmallarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				if (bIsActive == true)
				{
					a_Spaceship.Destroy(a_Spaceship);
					a_livescontroller.UpdateLives(-1);
					a_asteroidsmallarray[i].Destroy(a_asteroidsmallarray[i]);
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
}

void oSpaceship::CheckSpawnCollision(oSpaceship & a_Spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray)
{
	for (int i = 0; i < 5; ++i)
	{
		if (a_asteroidlargearray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidlargearray[i].GetRadius(iAsteroidRadius);
			a_asteroidlargearray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
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
		if (a_asteroidmediumarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidmediumarray[i].GetRadius(iAsteroidRadius);
			a_asteroidmediumarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
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
		if (a_asteroidsmallarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_asteroidsmallarray[i].GetRadius(iAsteroidRadius);
			a_asteroidsmallarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
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
	a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.degtorad;
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
			a_Spaceship.iSpriteID = UG::CreateSprite(a_Spaceship.cSpaceshipFileName, (float)a_Spaceship.iWidth, (float)a_Spaceship.iHeight);
			a_Spaceship.Draw(a_Spaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
			bHasSpawned = true;
		}
		else if (a_Spaceship.bCollision)
		{
			//Do nothing
		}
	}
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
