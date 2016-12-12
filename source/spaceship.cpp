#include "spaceship.h"
#include "UGFW.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern float g_DeltaTime;
extern int g_iScreenHeight;
extern int g_iScreenWidth;

oSpaceship::oSpaceship()
{
}

void oSpaceship::Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos)
{
	a_Spaceship.pos.Set(a_fXPos, a_fYPos);
	a_Spaceship.iSpriteID = UG::CreateSprite(a_SpaceshipImageFileName, (float)a_Spaceship.iWidth, (float)a_Spaceship.iHeight);
	a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
	UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship & a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_breakKey, short a_fireKey)
{
	a_Spaceship.upKey = a_upKey;
	a_Spaceship.downKey = a_downKey;
	a_Spaceship.leftKey = a_leftKey;
	a_Spaceship.rightKey = a_rightKey;
	a_Spaceship.breakKey = a_breakKey;
	a_Spaceship.fireKey = a_fireKey;
}
bool oSpaceship::CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidLarge>& a_asteroidarray, oLivesController& a_livescontroller)
{
	bool Collision = false;
	for (std::vector<oAsteroidLarge>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				if (bIsDead == false)
				{
					bIsDead = true;
					a_livescontroller.UpdateLives(-1);
					i->SetIsDead(true);
				}
				return Collision;
			}
			else
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}
bool oSpaceship::CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidMedium>& a_asteroidarray, oLivesController& a_livescontroller)
{
	bool Collision = false;
	for (std::vector<oAsteroidMedium>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				if (bIsDead == false)
				{
					bIsDead = true;
					a_livescontroller.UpdateLives(-1);
					i->SetIsDead(true);
				}
				return Collision;
			}
			else 
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}
bool oSpaceship::CheckAsteroidCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidSmall>& a_asteroidarray, oLivesController& a_livescontroller)
{
	bool Collision = false;
	for (std::vector<oAsteroidSmall>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				if (bIsDead == false)
				{
					bIsDead = true;
					a_livescontroller.UpdateLives(-1);
					i->SetIsDead(true);
				}
				return Collision;
			}
			else
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}

bool oSpaceship::CheckSpawnCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidLarge>& a_asteroidarray)
{
	bool Collision = false;
	for (std::vector<oAsteroidLarge>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				return Collision;
			}
			else
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}

bool oSpaceship::CheckSpawnCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidMedium>& a_asteroidarray)
{
	bool Collision = false;
	for (std::vector<oAsteroidMedium>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				return Collision;
			}
			else
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}

bool oSpaceship::CheckSpawnCollision(oSpaceship & a_Spaceship, std::vector<oAsteroidSmall>& a_asteroidarray)
{
	bool Collision = false;
	for (std::vector<oAsteroidSmall>::iterator i = a_asteroidarray.begin(); i != a_asteroidarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fPosX - fAsteroidPosX;
			float fDistanceY = fPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fSpawnRadius + (float)iAsteroidRadius)
			{
				Collision = true;
				return Collision;
			}
			else
			{
				return Collision;
			}
		}
		i++;
	}
	return Collision;
}

void oSpaceship::ResetVars(oSpaceship & a_spaceship)
{
	a_spaceship.fTotalVelocity = 0.f;
	fFacingAngleDeg = 90.0;
	fMovementAngleDeg = 90.0;
	fPosX = g_iScreenHeight * 0.5;
	fPosY = g_iScreenHeight * 0.5;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bIsDead = false;
	bCollision = false;
}

void oSpaceship::Respawn(oSpaceship & a_Spaceship)
{
	bool bHasSpawned = false;
	while (bHasSpawned == false)
	{
		if (!a_Spaceship.bCollision)
		{
			a_Spaceship.bIsDead = false;
			UG::DrawSprite(a_Spaceship.iSpriteID);
			UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
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
