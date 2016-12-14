///////////////////////////////////////////////////////////////
// File: <bullet.cpp>
// Author: <Alex Kitching>
// Date Created: <8/12/16>
// Brief: <Source file for all Bullet classes and functions.>
///////////////////////////////////////////////////////////////

#include "bullet.h"
#include "UGFW.h"
#include <math.h>

extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oBullet::SetIsActive(bool a_IsActive)
{
	bIsActive = a_IsActive;
}

void oBullet::SetIsDrawn(bool a_IsDrawn)
{
	bIsDrawn = a_IsDrawn;
}

void oBullet::SetHasExpired(bool a_HasExpired)
{
	bHasExpired = a_HasExpired;
}

void oBullet::GetDimensions(int & a_iWidth, int & a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oBullet::GetPos(float & a_PosX, float & a_PosY)
{
	a_PosX = pos.fX;
	a_PosY = pos.fY;
}

void oBullet::GetRadius(float & a_fRadius)
{
	a_fRadius = fRadius;
}

void oSpaceshipBullet::Draw(oSpaceshipBullet & a_SpaceshipBullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY)
{
	a_SpaceshipBullet.bIsDrawn = true;
	a_SpaceshipBullet.bIsActive = true;
	a_SpaceshipBullet.bHasExpired = false;
	//Direction of Bullet = Direction Ship is Facing
	a_SpaceshipBullet.vNew.fX = cosf(fSpaceshipFacingAngle);
	a_SpaceshipBullet.vNew.fY = sinf(fSpaceshipFacingAngle);
	// Set Initial Position of Bullet
	a_SpaceshipBullet.pos.fX = fSpaceshipPosX;
	a_SpaceshipBullet.pos.fY = fSpaceshipPosY;
	//Move Bullet in front of ship
	a_SpaceshipBullet.pos.fX += vNew.fX * 20;
	a_SpaceshipBullet.pos.fY += vNew.fY * 20;
	//Set Bullet Speed
	a_SpaceshipBullet.vNew.fX *= 5;
	a_SpaceshipBullet.vNew.fY *= 5;
	a_SpaceshipBullet.vNew.Set(a_SpaceshipBullet.vNew.fX, a_SpaceshipBullet.vNew.fY);
	a_SpaceshipBullet.iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_SpaceshipBullet.iWidth, (float)a_SpaceshipBullet.iHeight);
	UG::DrawSprite(a_SpaceshipBullet.iSpriteID);
	UG::MoveSprite(a_SpaceshipBullet.iSpriteID, a_SpaceshipBullet.pos.fX, a_SpaceshipBullet.pos.fY);
}

void oSpaceshipBullet::CheckCollision(oSpaceshipBullet& a_SpaceshipBullet, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount, int& a_UFOEasydeathcount, int& a_UFOHarddeathcount, oScorecontroller & a_Scorecontroller)
{
	//Check Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_aAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_SpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_SpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_SpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_SpaceshipBullet.IsDrawn(a_SpaceshipBullet))
				{
					a_SpaceshipBullet.Destroy(a_SpaceshipBullet);
				}
				a_aAsteroidLargeArray[i].Destroy(a_aAsteroidLargeArray[i]);
				if (!a_aAsteroidLargeArray[i].ScoreUpdated())
				{
					a_Scorecontroller.UpdateScore(a_aAsteroidLargeArray[i].Score(a_aAsteroidLargeArray[i]));
					a_aAsteroidLargeArray[i].SetScoreUpdated(true);
				}
				++a_asteroidlargedeathcount;
			}
		}
	}
	//Check Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_aAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_SpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_SpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_SpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_SpaceshipBullet.IsDrawn(a_SpaceshipBullet))
				{
					a_SpaceshipBullet.Destroy(a_SpaceshipBullet);
				}
				a_aAsteroidMediumArray[i].Destroy(a_aAsteroidMediumArray[i]);
				if (!a_aAsteroidMediumArray[i].ScoreUpdated())
				{
					a_Scorecontroller.UpdateScore(a_aAsteroidMediumArray[i].Score(a_aAsteroidMediumArray[i]));
					a_aAsteroidMediumArray[i].SetScoreUpdated(true);
				}
				++a_asteroidmediumdeathcount;
			}
		}
	}
	//Check Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_aAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_SpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_SpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_SpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_SpaceshipBullet.IsDrawn(a_SpaceshipBullet))
				{
					a_SpaceshipBullet.Destroy(a_SpaceshipBullet);
				}
				a_aAsteroidSmallArray[i].Destroy(a_aAsteroidSmallArray[i]);
				if (!a_aAsteroidSmallArray[i].ScoreUpdated())
				{
					a_Scorecontroller.UpdateScore(a_aAsteroidSmallArray[i].Score(a_aAsteroidSmallArray[i]));
					a_aAsteroidSmallArray[i].SetScoreUpdated(true);
				}
				++a_asteroidsmalldeathcount;
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

		if ((a_SpaceshipBullet.pos.fX - a_SpaceshipBullet.fRadius < fUFOPosX + iHalfUFOWidth && a_SpaceshipBullet.pos.fX + a_SpaceshipBullet.fRadius > fUFOPosX - iHalfUFOWidth) && (a_SpaceshipBullet.pos.fY - a_SpaceshipBullet.fRadius < fUFOPosY + iHalfUFOHeight && a_SpaceshipBullet.pos.fY + a_SpaceshipBullet.fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (a_SpaceshipBullet.IsDrawn(a_SpaceshipBullet))
			{
				a_SpaceshipBullet.Destroy(a_SpaceshipBullet);

			}
			a_UFOEasy.Destroy(a_UFOEasy);
			if (!a_UFOEasy.ScoreUpdated())
			{
				a_Scorecontroller.UpdateScore(a_UFOEasy.Score(a_UFOEasy));
				a_UFOEasy.SetScoreUpdated(true);
			}
			++a_UFOEasydeathcount;
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

		if ((a_SpaceshipBullet.pos.fX - a_SpaceshipBullet.fRadius < fUFOPosX + iHalfUFOWidth && a_SpaceshipBullet.pos.fX + a_SpaceshipBullet.fRadius > fUFOPosX - iHalfUFOWidth) && (a_SpaceshipBullet.pos.fY - a_SpaceshipBullet.fRadius < fUFOPosY + iHalfUFOHeight && a_SpaceshipBullet.pos.fY + a_SpaceshipBullet.fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (a_SpaceshipBullet.IsDrawn(a_SpaceshipBullet))
			{
				a_SpaceshipBullet.Destroy(a_SpaceshipBullet);
			}
			a_UFOHard.Destroy(a_UFOHard);
			if (!a_UFOHard.ScoreUpdated())
			{
				a_Scorecontroller.UpdateScore(a_UFOHard.Score(a_UFOHard));
				a_UFOHard.SetScoreUpdated(true);
			}
			++a_UFOHarddeathcount;
		}
	}
}

bool oSpaceshipBullet::IsActive(oSpaceshipBullet & a_SpaceshipBullet)
{
	return a_SpaceshipBullet.bIsActive;
}

bool oSpaceshipBullet::IsDrawn(oSpaceshipBullet & a_SpaceshipBullet)
{
	return a_SpaceshipBullet.bIsDrawn;
}

bool oSpaceshipBullet::HasExpired(oSpaceshipBullet & a_SpaceshipBullet)
{
	return a_SpaceshipBullet.bHasExpired;
}

void oSpaceshipBullet::Destroy(oSpaceshipBullet & a_SpaceshipBullet)
{
	fCurrentDistance = 0.f;
	pos.fX = 0.f;
	pos.fY = 0.f;
	vNew = Vector(0.0f, 0.0f);
	a_SpaceshipBullet.SetIsDrawn(false);
	a_SpaceshipBullet.SetIsActive(false);
	a_SpaceshipBullet.SetHasExpired(true);
	UG::StopDrawingSprite(a_SpaceshipBullet.iSpriteID);
	UG::DestroySprite(a_SpaceshipBullet.iSpriteID);
	a_SpaceshipBullet.iSpriteID = -1;
}

void oUFOBullet::Draw(oUFOBullet& a_UFOBullet, float fUFOPosX, float fUFOPosY, Vector& a_velocity)
{
	a_UFOBullet.bIsDrawn = true;
	a_UFOBullet.bIsActive = true;
	a_UFOBullet.bHasExpired = false;
	a_UFOBullet.vNew = a_velocity;
	// Set Initial Position of Bullet
	a_UFOBullet.pos.fX = fUFOPosX;
	a_UFOBullet.pos.fY = fUFOPosY;

	a_UFOBullet.iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_UFOBullet.iWidth, (float)a_UFOBullet.iHeight);
	UG::DrawSprite(a_UFOBullet.iSpriteID);
	UG::MoveSprite(a_UFOBullet.iSpriteID, a_UFOBullet.pos.fX, a_UFOBullet.pos.fY);
}

void oUFOBullet::CheckCollision(oUFOBullet & a_UFOBullet, oSpaceship & a_Spaceship, oAsteroidLarge * a_aAsteroidLargeArray, oAsteroidMedium * a_aAsteroidMediumArray, oAsteroidSmall * a_aAsteroidSmallArray, oLivescontroller a_Livescontroller, int & a_asteroidlargedeathcount, int & a_asteroidmediumdeathcount, int & a_asteroidsmalldeathcount)
{
	//Check Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_aAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_UFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_UFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_UFOBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_UFOBullet.IsDrawn(a_UFOBullet))
				{
					a_UFOBullet.Destroy(a_UFOBullet);
				}
				a_aAsteroidLargeArray[i].Destroy(a_aAsteroidLargeArray[i]);
				++a_asteroidlargedeathcount;
			}
		}
	}
	//Check Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_aAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_UFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_UFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_UFOBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_UFOBullet.IsDrawn(a_UFOBullet))
				{
					a_UFOBullet.Destroy(a_UFOBullet);
				}
				a_aAsteroidMediumArray[i].Destroy(a_aAsteroidMediumArray[i]);
				++a_asteroidmediumdeathcount;
			}
		}
	}
	//Check Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_aAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_aAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_aAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_UFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_UFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_UFOBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_UFOBullet.IsDrawn(a_UFOBullet))
				{
					a_UFOBullet.Destroy(a_UFOBullet);
				}
				a_aAsteroidSmallArray[i].Destroy(a_aAsteroidSmallArray[i]);
				++a_asteroidsmalldeathcount;
			}
		}
	}

	//Check Spaceship Collision
	if (a_Spaceship.IsActive())
	{
		float fSpaceshipRadius = 0;
		float fSpaceshipPosX = 0.f, fSpaceshipPosY = 0.f;
		a_Spaceship.GetRadius(fSpaceshipRadius);
		a_Spaceship.GetPos(fSpaceshipPosX, fSpaceshipPosY);
		float fDistanceX = a_UFOBullet.pos.fX - fSpaceshipPosX;
		float fDistanceY = a_UFOBullet.pos.fY - fSpaceshipPosY;
		float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
		if (fDistanceSquared < a_UFOBullet.fRadius + fSpaceshipRadius)
		{
			if (a_UFOBullet.IsDrawn(a_UFOBullet))
			{
				a_UFOBullet.Destroy(a_UFOBullet);
			}
			a_Spaceship.Destroy(a_Spaceship, a_Livescontroller);
			++a_asteroidsmalldeathcount;
			a_Spaceship.SetCollision(true);
		}
		else
		{
			a_Spaceship.SetCollision(false);
		}
	}
}

Vector oUFOBullet::NewFireDirection(oUFOHard & a_UFOHard, oSpaceship & a_Spaceship)
{
	float fSpaceshipPosX, fSpaceshipPosY;
	a_Spaceship.GetPos(fSpaceshipPosX, fSpaceshipPosY);

	Vector vDirection = Vector(fSpaceshipPosX - a_UFOHard.pos.fX, fSpaceshipPosY - a_UFOHard.pos.fY);
	vDirection.Normalise();
	vDirection*a_UFOHard.BulletSpeed();
	return vDirection;
}

bool oUFOBullet::IsActive(oUFOBullet & a_UFOBullet)
{
	return a_UFOBullet.bIsActive;
}

bool oUFOBullet::IsDrawn(oUFOBullet & a_UFOBullet)
{
	return a_UFOBullet.bIsDrawn;
}

bool oUFOBullet::HasExpired(oUFOBullet & a_UFOBullet)
{
	return a_UFOBullet.bHasExpired;
}

void oUFOBullet::Destroy(oUFOBullet & a_UFOBullet)
{
	fCurrentDistance = 0.f;
	pos.fX = 0.f;
	pos.fY = 0.f;
	vNew = Vector(0.0f, 0.0f);
	a_UFOBullet.SetIsDrawn(false);
	a_UFOBullet.SetIsActive(false);
	a_UFOBullet.SetHasExpired(true);
	UG::StopDrawingSprite(a_UFOBullet.iSpriteID);
	UG::DestroySprite(a_UFOBullet.iSpriteID);
	a_UFOBullet.iSpriteID = -1;
}
