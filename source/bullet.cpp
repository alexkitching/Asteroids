#include "bullet.h"
#include "UGFW.h"
#include "math.h"
#include <vector>
extern int g_iScreenHeight;
extern int g_iScreenWidth;

oBullet::oBullet()
{

}

oBullet::~oBullet()
{
}

bool oBullet::IsActive(std::vector<oBullet>::iterator a_Bullet)
{
	return a_Bullet->bIsActive;
}

bool oBullet::IsDrawn(std::vector<oBullet>::iterator a_Bullet)
{
	return a_Bullet->bIsDrawn;
}

void oBullet::Draw(std::vector<oBullet>::iterator a_Bullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY)
{
	a_Bullet->bIsDrawn = true;
	a_Bullet->bIsActive = true;
	//Direction of Bullet = Direction Ship is Facing
	a_Bullet->fVNewX = cosf(fSpaceshipFacingAngle);
	a_Bullet->fVNewY = sinf(fSpaceshipFacingAngle);
	// Set Initial Position of Bullet
	a_Bullet->fPosX = fSpaceshipPosX;
	a_Bullet->fPosY = fSpaceshipPosY;
	//Move Bullet in front of ship
	a_Bullet->fPosX += fVNewX * 20;
	a_Bullet->fPosY += fVNewY * 20;
	a_Bullet->pos.Set(a_Bullet->fPosX, a_Bullet->fPosY);
	//Set Bullet Speed
	a_Bullet->fVNewX *= 5;
	a_Bullet->fVNewY *= 5;
	a_Bullet->vNew.Set(a_Bullet->fVNewX, a_Bullet->fVNewY);
	a_Bullet->iSpriteID = UG::CreateSprite("./images/bullet.png", (float)a_Bullet->iWidth, (float)a_Bullet->iHeight);
	UG::DrawSprite(a_Bullet->iSpriteID);
	UG::MoveSprite(a_Bullet->iSpriteID, a_Bullet->fPosX, a_Bullet->fPosY);
}

void oBullet::CheckLargeAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, std::vector<oAsteroidLarge>& a_asteroidlargearray)
{
	for (std::vector<oAsteroidLarge>::iterator i = a_asteroidlargearray.begin(); i != a_asteroidlargearray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = a_Bullet->fRadius;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));

			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				a_Bullet->bIsDrawn = false;
				a_Bullet->bIsActive = false;
				i->SetIsDead(true);
			}
		}
		i++;
	}

}

void oBullet::CheckMediumAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, std::vector<oAsteroidMedium>& a_asteroidmediumarray)
{
	for (std::vector<oAsteroidMedium>::iterator i = a_asteroidmediumarray.begin(); i != a_asteroidmediumarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = a_Bullet->fRadius;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				a_Bullet->bIsDrawn = false;
				a_Bullet->bIsActive = false;
				i->SetIsDead(true);
			}
		}
		i++;
	}
}

void oBullet::CheckSmallAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, std::vector<oAsteroidSmall>& a_asteroidsmallarray)
{
	for (std::vector<oAsteroidSmall>::iterator i = a_asteroidsmallarray.begin(); i != a_asteroidsmallarray.end();)
	{
		if (!i->IsDead())
		{
			int iAsteroidRadius = 0;
			float fBulletRadius = a_Bullet->fRadius;
			float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
			i->GetRadius(iAsteroidRadius);
			i->GetPos(fAsteroidPosX, fAsteroidPosY);
			float fDistanceX = fBulletPosX - fAsteroidPosX;
			float fDistanceY = fBulletPosY - fAsteroidPosY;
			float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
			if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
			{
				a_Bullet->bIsDrawn = false;
				a_Bullet->bIsActive = false;
				i->SetIsDead(true);
			}

		}
		i++;
	}
}
