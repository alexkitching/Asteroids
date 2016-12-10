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

bool oBullet::Update(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet)
{
	a_Bullet->pos.Get(a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->vNew.Get(a_Bullet->fVNewX, a_Bullet->fVNewY);
	a_Bullet->fPosX = a_Bullet->fPosX + a_Bullet->fVNewX;
	a_Bullet->fPosY = a_Bullet->fPosY + a_Bullet->fVNewY;
	if (a_Bullet->fPosY >= g_iScreenHeight + a_Bullet->iHeight)
	{
		a_Bullet->fPosY = (0.f * (float)g_iScreenHeight) - (float)a_Bullet->iHeight;
	}
	else if (a_Bullet->fPosY <= -a_Bullet->iHeight)
	{
		a_Bullet->fPosY = ((float)g_iScreenHeight + (float)a_Bullet->iHeight);
	}

	if (a_Bullet->fPosX >= g_iScreenWidth + a_Bullet->iWidth)
	{
		a_Bullet->fPosX = (0.f * (float)g_iScreenWidth) - (float)a_Bullet->iWidth;
	}
	else if (a_Bullet->fPosX <= -a_Bullet->iWidth)
	{
		a_Bullet->fPosX = ((float)g_iScreenWidth + (float)a_Bullet->iWidth);
	}
	UG::MoveSprite(a_Bullet->iSpriteID, a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->pos.Set(a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->fCurrentDistance += a_Bullet->vNew.Magnitude();
	if (a_Bullet->fCurrentDistance >= a_Bullet->fMaxDistance)
	{
		a_Bullet->bIsDrawn = false;
		a_Bullet->bIsActive = false;
	}
	return a_Bullet->bIsActive;
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

void oBullet::CheckLargeAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidLarge& a_AsteroidLarge)
{
	int iAsteroidRadius = 0;
	float fBulletRadius = a_Bullet->fRadius;
	float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
	a_AsteroidLarge.GetRadius(iAsteroidRadius);
	a_AsteroidLarge.GetPos(fAsteroidPosX, fAsteroidPosY);
	float fDistanceX = fBulletPosX - fAsteroidPosX;
	float fDistanceY = fBulletPosY - fAsteroidPosY;
	float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));

	if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
	{
		a_Bullet->bIsDrawn = false;
		a_Bullet->bIsActive = false;
		a_AsteroidLarge.SetIsDead(true);
	}
}

void oBullet::CheckMediumAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidMedium & a_AsteroidMedium)
{
	int iAsteroidRadius = 0;
	float fBulletRadius = a_Bullet->fRadius;
	float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
	a_AsteroidMedium.GetRadius(iAsteroidRadius);
	a_AsteroidMedium.GetPos(fAsteroidPosX, fAsteroidPosY);
	float fDistanceX = fBulletPosX - fAsteroidPosX;
	float fDistanceY = fBulletPosY - fAsteroidPosY;
	float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
	if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
	{
		a_Bullet->bIsDrawn = false;
		a_Bullet->bIsActive = false;
		a_AsteroidMedium.SetIsDead(true);
	}
}

void oBullet::CheckSmallAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidSmall & a_AsteroidSmall)
{
	int iAsteroidRadius = 0;
	float fBulletRadius = a_Bullet->fRadius;
	float fAsteroidPosX = 0.f, fAsteroidPosY = 0.f, fBulletPosX = a_Bullet->fPosX, fBulletPosY = a_Bullet->fPosY;
	a_AsteroidSmall.GetRadius(iAsteroidRadius);
	a_AsteroidSmall.GetPos(fAsteroidPosX, fAsteroidPosY);
	float fDistanceX = fBulletPosX - fAsteroidPosX;
	float fDistanceY = fBulletPosY - fAsteroidPosY;
	float fDistanceSquared = sqrtf((fDistanceX * fDistanceX) + (fDistanceY * fDistanceY));
	if (fDistanceSquared < fBulletRadius + (float)iAsteroidRadius)
	{
		a_Bullet->bIsDrawn = false;
		a_Bullet->bIsActive = false;
		a_AsteroidSmall.SetIsDead(true);
	}
}
