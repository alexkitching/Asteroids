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

void oBullet::SetIsActive(bool a_bIsActive)
{
	bIsActive = a_bIsActive;
}

void oBullet::SetIsDrawn(bool a_bIsDrawn)
{
	bIsDrawn = a_bIsDrawn;
}

void oBullet::SetHasExpired(bool a_bHasExpired)
{
	bHasExpired = a_bHasExpired;
}

void oBullet::GetDimensions(int & a_riWidth, int & a_riHeight)
{
	a_riWidth = iWidth, a_riHeight = iHeight;
}

void oBullet::GetPos(float & a_rfPosX, float & a_rfPosY)
{
	a_rfPosX = pos.fX;
	a_rfPosY = pos.fY;
}

void oBullet::GetRadius(float & a_rfRadius)
{
	a_rfRadius = fRadius;
}

void oSpaceshipBullet::Draw(oSpaceshipBullet & a_rSpaceshipBullet, float a_fSpaceshipFacingAngle, float a_fSpaceshipPosX, float a_fSpaceshipPosY)
{
	a_rSpaceshipBullet.bIsDrawn = true;
	a_rSpaceshipBullet.bIsActive = true;
	a_rSpaceshipBullet.bHasExpired = false;
	//Direction of Bullet = Direction Ship is Facing
	a_rSpaceshipBullet.vNew.fX = cosf(a_fSpaceshipFacingAngle);
	a_rSpaceshipBullet.vNew.fY = sinf(a_fSpaceshipFacingAngle);
	// Set Initial Position of Bullet
	a_rSpaceshipBullet.pos.fX = a_fSpaceshipPosX;
	a_rSpaceshipBullet.pos.fY = a_fSpaceshipPosY;
	//Move Bullet in front of ship
	a_rSpaceshipBullet.pos.fX += vNew.fX * 20;
	a_rSpaceshipBullet.pos.fY += vNew.fY * 20;
	//Set Bullet Speed
	a_rSpaceshipBullet.vNew.fX *= 5;
	a_rSpaceshipBullet.vNew.fY *= 5;
	a_rSpaceshipBullet.vNew.Set(a_rSpaceshipBullet.vNew.fX, a_rSpaceshipBullet.vNew.fY);
	a_rSpaceshipBullet.iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_rSpaceshipBullet.iWidth, (float)a_rSpaceshipBullet.iHeight);
	UG::DrawSprite(a_rSpaceshipBullet.iSpriteID);
	UG::MoveSprite(a_rSpaceshipBullet.iSpriteID, a_rSpaceshipBullet.pos.fX, a_rSpaceshipBullet.pos.fY);
}

void oSpaceshipBullet::CheckCollision(oSpaceshipBullet& a_rSpaceshipBullet, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
	 oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, int& a_rAsteroidLargedeathcount, int& a_rAsteroidMediumdeathcount,
	 int& a_rAsteroidSmalldeathcount, int& a_rUFOEasydeathcount, int& a_rUFOHarddeathcount, oScorecontroller & a_rScorecontroller)
{
	//Check Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_paAsteroidLargeArray[i].IsActive()) //Check Asteroid Is Active
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rSpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rSpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rSpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_rSpaceshipBullet.IsDrawn(a_rSpaceshipBullet))
				{
					a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet 
				}
				a_paAsteroidLargeArray[i].Destroy(a_paAsteroidLargeArray[i]); //Destroy Asteroid
				if (!a_paAsteroidLargeArray[i].ScoreUpdated())
				{
					a_rScorecontroller.UpdateScore(a_paAsteroidLargeArray[i].Score(a_paAsteroidLargeArray[i])); //Update Score
					a_paAsteroidLargeArray[i].SetScoreUpdated(true); 
				}
				++a_rAsteroidLargedeathcount; //Increase Asteroid Death Count
			}
		}
	}
	//Check Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_paAsteroidMediumArray[i].IsActive()) //Check Asteroid Is Active
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rSpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rSpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rSpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (a_rSpaceshipBullet.IsDrawn(a_rSpaceshipBullet))
				{
					a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet 
				}
				a_paAsteroidMediumArray[i].Destroy(a_paAsteroidMediumArray[i]);
				if (!a_paAsteroidMediumArray[i].ScoreUpdated())
				{
					a_rScorecontroller.UpdateScore(a_paAsteroidMediumArray[i].Score(a_paAsteroidMediumArray[i])); //Update Score
					a_paAsteroidMediumArray[i].SetScoreUpdated(true);
				}
				++a_rAsteroidMediumdeathcount; //Increase Asteroid Death Count
			}
		}
	}
	//Check Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_paAsteroidSmallArray[i].IsActive()) //Check Asteroid Is Active
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rSpaceshipBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rSpaceshipBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rSpaceshipBullet.fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (a_rSpaceshipBullet.IsDrawn(a_rSpaceshipBullet))
				{
					a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet 
				}
				a_paAsteroidSmallArray[i].Destroy(a_paAsteroidSmallArray[i]);
				if (!a_paAsteroidSmallArray[i].ScoreUpdated())
				{
					a_rScorecontroller.UpdateScore(a_paAsteroidSmallArray[i].Score(a_paAsteroidSmallArray[i])); //Update Score
					a_paAsteroidSmallArray[i].SetScoreUpdated(true);
				}
				++a_rAsteroidSmalldeathcount; //Increase Asteroid Death Count
			}
		}
	}
	//Check for UFOEasy Collision
	if (a_rUFOEasy.IsActive()) //Check UFO Is Active
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_rUFOEasy.GetPos(fUFOPosX, fUFOPosY);
		a_rUFOEasy.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((a_rSpaceshipBullet.pos.fX - a_rSpaceshipBullet.fRadius < fUFOPosX + iHalfUFOWidth &&
			a_rSpaceshipBullet.pos.fX + a_rSpaceshipBullet.fRadius > fUFOPosX - iHalfUFOWidth) &&
			(a_rSpaceshipBullet.pos.fY - a_rSpaceshipBullet.fRadius < fUFOPosY + iHalfUFOHeight &&
				a_rSpaceshipBullet.pos.fY + a_rSpaceshipBullet.fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (a_rSpaceshipBullet.IsDrawn(a_rSpaceshipBullet))
			{
				a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet 

			}
			a_rUFOEasy.Destroy(a_rUFOEasy);
			if (!a_rUFOEasy.ScoreUpdated())
			{
				a_rScorecontroller.UpdateScore(a_rUFOEasy.Score(a_rUFOEasy)); //Update Score
				a_rUFOEasy.SetScoreUpdated(true);
			}
			++a_rUFOEasydeathcount; //Increase UFO Death Count
		}
	}
	//Check for UFOHard Collision
	if (a_rUFOHard.IsActive()) //Check UFO Is Active
	{
		int iUFOWidth, iUFOHeight;
		float fUFOPosX = 0.f, fUFOPosY = 0.f;
		a_rUFOHard.GetPos(fUFOPosX, fUFOPosY);
		a_rUFOHard.GetDimensions(iUFOWidth, iUFOHeight);
		int iHalfUFOWidth = (int)(iUFOWidth * 0.5);
		int iHalfUFOHeight = (int)(iUFOHeight * 0.5);

		if ((a_rSpaceshipBullet.pos.fX - a_rSpaceshipBullet.fRadius < fUFOPosX + iHalfUFOWidth && a_rSpaceshipBullet.pos.fX + a_rSpaceshipBullet.fRadius > fUFOPosX - iHalfUFOWidth) && (a_rSpaceshipBullet.pos.fY - a_rSpaceshipBullet.fRadius < fUFOPosY + iHalfUFOHeight && a_rSpaceshipBullet.pos.fY + a_rSpaceshipBullet.fRadius > fUFOPosY - iHalfUFOHeight))
		{
			//Collision
			if (a_rSpaceshipBullet.IsDrawn(a_rSpaceshipBullet))
			{
				a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet 
			}
			a_rUFOHard.Destroy(a_rUFOHard);
			if (!a_rUFOHard.ScoreUpdated())
			{
				a_rScorecontroller.UpdateScore(a_rUFOHard.Score(a_rUFOHard)); //Update Score
				a_rUFOHard.SetScoreUpdated(true);
			}
			++a_rUFOHarddeathcount; //Increase UFO Death Count
		}
	}
}
//Return Status Variables
bool oSpaceshipBullet::IsActive(oSpaceshipBullet & a_rSpaceshipBullet)
{
	return a_rSpaceshipBullet.bIsActive;
}

bool oSpaceshipBullet::IsDrawn(oSpaceshipBullet & a_rSpaceshipBullet)
{
	return a_rSpaceshipBullet.bIsDrawn;
}

bool oSpaceshipBullet::HasExpired(oSpaceshipBullet & a_rSpaceshipBullet)
{
	return a_rSpaceshipBullet.bHasExpired;
}

void oSpaceshipBullet::Destroy(oSpaceshipBullet & a_rSpaceshipBullet)
{
	fCurrentDistance = 0.f; //Reset Position and Movement Variables
	pos.fX = 0.f;
	pos.fY = 0.f;
	vNew = Vector(0.0f, 0.0f);
	a_rSpaceshipBullet.SetIsDrawn(false); //Set Status Variables
	a_rSpaceshipBullet.SetIsActive(false);
	a_rSpaceshipBullet.SetHasExpired(true);
	UG::StopDrawingSprite(a_rSpaceshipBullet.iSpriteID); //Stop Drawing Bullet
	UG::DestroySprite(a_rSpaceshipBullet.iSpriteID); //Destroy Bullet
	a_rSpaceshipBullet.iSpriteID = -1; //Reset iSpriteID
}

void oUFOBullet::Draw(oUFOBullet& a_rUFOBullet, float fUFOPosX, float fUFOPosY, Vector a_velocity)
{
	a_rUFOBullet.bIsDrawn = true; //Set Status Variables
	a_rUFOBullet.bIsActive = true;
	a_rUFOBullet.bHasExpired = false;
	a_rUFOBullet.vNew = a_velocity;
	// Set Initial Position of Bullet
	a_rUFOBullet.pos.fX = fUFOPosX;
	a_rUFOBullet.pos.fY = fUFOPosY;
	//Create New BulletSprite
	a_rUFOBullet.iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_rUFOBullet.iWidth, (float)a_rUFOBullet.iHeight);
	UG::DrawSprite(a_rUFOBullet.iSpriteID); //Draw Bullet Sprite
	UG::MoveSprite(a_rUFOBullet.iSpriteID, a_rUFOBullet.pos.fX, a_rUFOBullet.pos.fY); //Move Bullet
}

void oUFOBullet::CheckCollision(oUFOBullet & a_rUFOBullet, oSpaceship & a_rSpaceship, oAsteroidLarge * a_paAsteroidLargeArray, oAsteroidMedium * a_paAsteroidMediumArray, oAsteroidSmall * a_paAsteroidSmallArray, oLivescontroller a_rLivescontroller, int & a_rAsteroidLargedeathcount, int & a_rAsteroidMediumdeathcount, int & a_rAsteroidSmalldeathcount)
{
	//Check Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_paAsteroidLargeArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidLargeArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidLargeArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rUFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rUFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rUFOBullet.fRadius + (float)iAsteroidRadius)
			{
				if (a_rUFOBullet.IsDrawn(a_rUFOBullet))
				{
					a_rUFOBullet.Destroy(a_rUFOBullet); //If Bullet is Drawn, Destroy
				}
				a_paAsteroidLargeArray[i].Destroy(a_paAsteroidLargeArray[i]); //Destroy Asteroid
				++a_rAsteroidLargedeathcount; //Increase Asteroid Death Count
			}
		}
	}
	//Check Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_paAsteroidMediumArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidMediumArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidMediumArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rUFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rUFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rUFOBullet.fRadius + (float)iAsteroidRadius)
			{	//Collision
				if (a_rUFOBullet.IsDrawn(a_rUFOBullet))
				{
					a_rUFOBullet.Destroy(a_rUFOBullet); //If Bullet is Drawn, Destroy
				}
				a_paAsteroidMediumArray[i].Destroy(a_paAsteroidMediumArray[i]); //Destroy Asteroid
				++a_rAsteroidMediumdeathcount; //Increase Asteroid Death Count
			}
		}
	}
	//Check Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_paAsteroidSmallArray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f;
			a_paAsteroidSmallArray[i].GetRadius(iAsteroidRadius);
			a_paAsteroidSmallArray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = a_rUFOBullet.pos.fX - fAsteroidPosX;
			float fDistanceY = a_rUFOBullet.pos.fY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < a_rUFOBullet.fRadius + (float)iAsteroidRadius)
			{
				//Collision
				if (a_rUFOBullet.IsDrawn(a_rUFOBullet))
				{
					a_rUFOBullet.Destroy(a_rUFOBullet); //If Bullet is Drawn, Destroy
				}
				a_paAsteroidSmallArray[i].Destroy(a_paAsteroidSmallArray[i]); //Destroy Asteroid
				++a_rAsteroidSmalldeathcount; //Increase Asteroid Death Count
			}
		}
	}

	//Check Spaceship Collision
	if (a_rSpaceship.IsActive())
	{
		float fSpaceshipRadius = 0;
		float a_fSpaceshipPosX = 0.f, a_fSpaceshipPosY = 0.f;
		a_rSpaceship.GetRadius(fSpaceshipRadius);
		a_rSpaceship.GetPos(a_fSpaceshipPosX, a_fSpaceshipPosY);
		float fDistanceX = a_rUFOBullet.pos.fX - a_fSpaceshipPosX;
		float fDistanceY = a_rUFOBullet.pos.fY - a_fSpaceshipPosY;
		float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
		if (fDistanceSquared < a_rUFOBullet.fRadius + fSpaceshipRadius)
		{
			if (a_rUFOBullet.IsDrawn(a_rUFOBullet))
			{
				a_rUFOBullet.Destroy(a_rUFOBullet); //If Bullet is Drawn, Destroy
			}
			a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller); //Destroy Spaceship
			a_rSpaceship.SetCollision(true); // Spaceship Collided
		}
		else
		{
			a_rSpaceship.SetCollision(false); // Spaceship Hasn't Collided
		}
	}
}

Vector oUFOBullet::NewFireDirection(oUFOHard& a_rUFOHard, oSpaceship & a_rSpaceship)
{
	float a_fSpaceshipPosX, a_fSpaceshipPosY;
	a_rSpaceship.GetPos(a_fSpaceshipPosX, a_fSpaceshipPosY);

	Vector vDirection = Vector(a_fSpaceshipPosX - a_rUFOHard.pos.fX, a_fSpaceshipPosY - a_rUFOHard.pos.fY); //Set Trajectory to Aim at Spaceship
	vDirection.Normalise();
	vDirection * (float) a_rUFOHard.BulletSpeed(); // Increase Bullet Speed
	return vDirection;
}

//Return Status Variables
bool oUFOBullet::IsActive(oUFOBullet & a_rUFOBullet)
{
	return a_rUFOBullet.bIsActive;
}

bool oUFOBullet::IsDrawn(oUFOBullet & a_rUFOBullet)
{
	return a_rUFOBullet.bIsDrawn;
}

bool oUFOBullet::HasExpired(oUFOBullet & a_rUFOBullet)
{
	return a_rUFOBullet.bHasExpired;
}

void oUFOBullet::Destroy(oUFOBullet & a_rUFOBullet)
{
	fCurrentDistance = 0.f; //Reset Position Variables
	pos.fX = 0.f;
	pos.fY = 0.f;
	vNew = Vector(0.0f, 0.0f);
	a_rUFOBullet.SetIsDrawn(false); //Reset Status Variables
	a_rUFOBullet.SetIsActive(false);
	a_rUFOBullet.SetHasExpired(true);
	UG::StopDrawingSprite(a_rUFOBullet.iSpriteID); //Stop Drawing Bullet
	UG::DestroySprite(a_rUFOBullet.iSpriteID); //Destroy Bullet Sprite
	a_rUFOBullet.iSpriteID = -1; //Reset SpriteID;
}
