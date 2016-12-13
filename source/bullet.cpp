#include "bullet.h"
#include "UGFW.h"
#include "math.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

bool oBullet::IsActive(oBullet& a_Bullet)
{
	return a_Bullet.bIsActive;
}

bool oBullet::IsDrawn(oBullet& a_Bullet)
{
	return a_Bullet.bIsDrawn;
}

bool oBullet::HasExpired(oBullet & a_Bullet)
{
	return a_Bullet.bHasExpired;
}

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

void oBullet::Draw(oBullet& a_Bullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY)
{
	a_Bullet.bIsDrawn = true;
	a_Bullet.bIsActive = true;
	a_Bullet.bHasExpired = false;
	//Direction of Bullet = Direction Ship is Facing
	a_Bullet.fVNewX = cosf(fSpaceshipFacingAngle);
	a_Bullet.fVNewY = sinf(fSpaceshipFacingAngle);
	// Set Initial Position of Bullet
	a_Bullet.fPosX = fSpaceshipPosX;
	a_Bullet.fPosY = fSpaceshipPosY;
	//Move Bullet in front of ship
	a_Bullet.fPosX += fVNewX * 20;
	a_Bullet.fPosY += fVNewY * 20;
	a_Bullet.pos.Set(a_Bullet.fPosX, a_Bullet.fPosY);
	//Set Bullet Speed
	a_Bullet.fVNewX *= 5;
	a_Bullet.fVNewY *= 5;
	a_Bullet.vNew.Set(a_Bullet.fVNewX, a_Bullet.fVNewY);
	a_Bullet.iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_Bullet.iWidth, (float)a_Bullet.iHeight);
	UG::DrawSprite(a_Bullet.iSpriteID);
	UG::MoveSprite(a_Bullet.iSpriteID, a_Bullet.fPosX, a_Bullet.fPosY);
}

void oBullet::Destroy(oBullet & a_Bullet)
{
	fCurrentDistance = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	pos.Set(fPosX, fPosY);
	vNew = Vector(0.0f, 0.0f);
	a_Bullet.SetIsDrawn(false);
	a_Bullet.SetIsActive(false);
	a_Bullet.SetHasExpired(true);
	UG::StopDrawingSprite(a_Bullet.iSpriteID);
	UG::DestroySprite(a_Bullet.iSpriteID);
	a_Bullet.iSpriteID = -1;
}

void oBullet::CheckAsteroidCollision(oBullet & a_Bullet, oAsteroidLarge * a_asteroidlargearray, oAsteroidMedium * a_asteroidmediumarray, oAsteroidSmall * a_asteroidsmallarray, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount)
{
	//Check Large Asteroid Collision
	for (int i = 0; i < 5; ++i)
	{
		if (a_asteroidlargearray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = 0.f;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = 0.f, fBulletPosY = 0.f;

			a_Bullet.GetRadius(fBulletRadius);
			a_asteroidlargearray[i].GetRadius(iAsteroidRadius);
			a_Bullet.GetPos(fBulletPosX, fBulletPosY);
			a_asteroidlargearray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));

			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				if (a_Bullet.bIsDrawn)
				{
					a_Bullet.Destroy(a_Bullet);
				}
				a_asteroidlargearray[i].Destroy(a_asteroidlargearray[i]);
				++a_asteroidlargedeathcount;
			}
		}
	}
	//Check Medium Asteroid Collision
	for (int i = 0; i < 15; ++i)
	{
		if (a_asteroidmediumarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = 0.f;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = 0.f, fBulletPosY = 0.f;
			a_Bullet.GetRadius(fBulletRadius);
			a_asteroidmediumarray[i].GetRadius(iAsteroidRadius);
			a_Bullet.GetPos(fBulletPosX, fBulletPosY);
			a_asteroidmediumarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				if (a_Bullet.bIsDrawn)
				{
					a_Bullet.Destroy(a_Bullet);
				}
				a_asteroidmediumarray[i].Destroy(a_asteroidmediumarray[i]);
				++a_asteroidmediumdeathcount;
			}
		}
	}
	//Check Small Asteroid Collision
	for (int i = 0; i < 45; ++i)
	{
		if (a_asteroidsmallarray[i].IsActive())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = 0.f;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = 0.f, fBulletPosY = 0.f;
			a_Bullet.GetRadius(fBulletRadius);
			a_asteroidsmallarray[i].GetRadius(iAsteroidRadius);
			a_Bullet.GetPos(fBulletPosX, fBulletPosY);
			a_asteroidsmallarray[i].GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				if (a_Bullet.bIsDrawn)
				{
					a_Bullet.Destroy(a_Bullet);
				}
				a_asteroidsmallarray[i].Destroy(a_asteroidsmallarray[i]);
				++a_asteroidsmalldeathcount;
			}
		}
	}
}

void oBullet::GetDimensions(int & a_iWidth, int & a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oBullet::GetPos(float & a_PosX, float & a_PosY)
{
	a_PosX = fPosX;
	a_PosY = fPosY;
}

void oBullet::GetRadius(float & a_fRadius)
{
	a_fRadius = fRadius;
}