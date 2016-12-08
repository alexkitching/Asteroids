#include "bullet.h"
#include "UGFW.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

oBullet::oBullet()
{
}

oBullet::~oBullet()
{
}

void oBullet::SetActive(bool a_active)
{
	bActive = a_active;
}

void oBullet::SetDrawn(bool a_drawn)
{
	bDrawn = a_drawn;
}

bool oBullet::IsActive()
{
	return bActive;
}

bool oBullet::IsDrawn()
{
	return bDrawn;
}

void oBullet::Update(oBullet & a_Bullet)
{
	if (bActive)
	{
		a_Bullet.pos.Get(a_Bullet.fPosX, a_Bullet.fPosY);
		a_Bullet.vNew.Get(a_Bullet.fVNewX, a_Bullet.fVNewY);
		a_Bullet.fPosX = a_Bullet.fPosX + a_Bullet.fVNewX;
		a_Bullet.fPosY = a_Bullet.fPosY + a_Bullet.fVNewY;
		if (a_Bullet.fPosY >= g_iScreenHeight + a_Bullet.iHeight)
		{
			a_Bullet.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_Bullet.iHeight;
		}
		else if (a_Bullet.fPosY <= -a_Bullet.iHeight)
		{
			a_Bullet.fPosY = ((float)g_iScreenHeight + (float)a_Bullet.iHeight);
		}

		if (a_Bullet.fPosX >= g_iScreenWidth + a_Bullet.iWidth)
		{
			a_Bullet.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_Bullet.iWidth;
		}
		else if (a_Bullet.fPosX <= -a_Bullet.iWidth)
		{
			a_Bullet.fPosX = ((float)g_iScreenWidth + (float)a_Bullet.iWidth);
		}
		UG::MoveSprite(a_Bullet.iSpriteID, a_Bullet.fPosX, a_Bullet.fPosY);
		a_Bullet.pos.Set(a_Bullet.fPosX, a_Bullet.fPosY);
		a_Bullet.fCurrentDistance += a_Bullet.vNew.Magnitude();
		if (a_Bullet.fCurrentDistance >= a_Bullet.fMaxDistance)
		{
			a_Bullet.bActive = false;
			a_Bullet.fCurrentDistance = 0.f;
			UG::DestroySprite(a_Bullet.iSpriteID);
			a_Bullet.fPosX = 0.f;
			a_Bullet.fPosY = 0.f;
		}      
		
		
	}
}

void oBullet::Draw(float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY)
{
	if (bActive)
	{
		//Direction of Bullet = Direction Ship is Facing
		fVNewX = cosf(fSpaceshipFacingAngle);
		fVNewY = sinf(fSpaceshipFacingAngle);
		// Set Initial Position of Bullet
		fPosX = fSpaceshipPosX;
		fPosY = fSpaceshipPosY;
		//Move Bullet in front of ship
		fPosX += fVNewX * 20;
		fPosY += fVNewY * 20;
		pos.Set(fPosX, fPosY);
		//Set Bullet Speed
		fVNewX *= 5;
		fVNewY *= 5;
		vNew.Set(fVNewX, fVNewY);
		iSpriteID = UG::CreateSprite("./images/bullet.png", (float)iWidth, (float)iHeight);
		UG::DrawSprite(iSpriteID);
		UG::MoveSprite(iSpriteID, fPosX, fPosY);
	}
}

