#include "objectupdatecontroller.h"
#include "UGFW.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oObjectUpdateController::AsteroidLargeUpdate(oAsteroidLarge & a_AsteroidLarge, std::vector<oAsteroidMedium>& a_asteroidmediumarray)
{
	if (!a_AsteroidLarge.bIsDead)
	{
		a_AsteroidLarge.pos.Get(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
		a_AsteroidLarge.vNew.Get(a_AsteroidLarge.fVNewX, a_AsteroidLarge.fVNewY);
		a_AsteroidLarge.fPosX = a_AsteroidLarge.fPosX + a_AsteroidLarge.fVNewX;
		a_AsteroidLarge.fPosY = a_AsteroidLarge.fPosY + a_AsteroidLarge.fVNewY;
		if (a_AsteroidLarge.fPosY >= g_iScreenHeight + a_AsteroidLarge.iHeight)
		{
			a_AsteroidLarge.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidLarge.iHeight;
		}
		else if (a_AsteroidLarge.fPosY <= -a_AsteroidLarge.iHeight)
		{
			a_AsteroidLarge.fPosY = ((float)g_iScreenHeight + (float)a_AsteroidLarge.iHeight);
		}

		if (a_AsteroidLarge.fPosX >= g_iScreenWidth + a_AsteroidLarge.iWidth)
		{
			a_AsteroidLarge.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidLarge.iWidth;
		}
		else if (a_AsteroidLarge.fPosX <= -a_AsteroidLarge.iWidth)
		{
			a_AsteroidLarge.fPosX = ((float)g_iScreenWidth + (float)a_AsteroidLarge.iWidth);
		}
		UG::MoveSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
		UG::RotateSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fSpriteTurnRate);
		a_AsteroidLarge.pos.Set(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
	}
	else if (a_AsteroidLarge.bIsDead)
	{
		if (!a_AsteroidLarge.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidmediumarray.push_back(oAsteroidMedium(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY, i));
			}
			a_AsteroidLarge.bShattered = true;
		}
		
		UG::StopDrawingSprite(a_AsteroidLarge.iSpriteID);
	}
}

void oObjectUpdateController::AsteroidMediumUpdate(std::vector<*T>::iterator a_AsteroidMedium, std::vector<oAsteroidSmall>& a_asteroidsmallarray)
{
	if (!a_AsteroidMedium->bIsDead)
	{
		a_AsteroidMedium->pos.Get(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
		a_AsteroidMedium->vNew.Get(a_AsteroidMedium->fVNewX, a_AsteroidMedium->fVNewY);
		a_AsteroidMedium->fPosX = a_AsteroidMedium->fPosX + a_AsteroidMedium->fVNewX;
		a_AsteroidMedium->fPosY = a_AsteroidMedium->fPosY + a_AsteroidMedium->fVNewY;
		if (a_AsteroidMedium->fPosY >= g_iScreenHeight + a_AsteroidMedium->iHeight)
		{
			a_AsteroidMedium->fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidMedium->iHeight;
		}
		else if (a_AsteroidMedium->fPosY <= -a_AsteroidMedium->iHeight)
		{
			a_AsteroidMedium->fPosY = ((float)g_iScreenHeight + (float)a_AsteroidMedium->iHeight);
		}

		if (a_AsteroidMedium->fPosX >= g_iScreenWidth + a_AsteroidMedium->iWidth)
		{
			a_AsteroidMedium->fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidMedium->iWidth;
		}
		else if (a_AsteroidMedium->fPosX <= -a_AsteroidMedium->iWidth)
		{
			a_AsteroidMedium->fPosX = ((float)g_iScreenWidth + (float)a_AsteroidMedium->iWidth);
		}
		UG::MoveSprite(a_AsteroidMedium->iSpriteID, a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
		UG::RotateSprite(a_AsteroidMedium->iSpriteID, a_AsteroidMedium->fSpriteTurnRate);
		a_AsteroidMedium->pos.Set(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
	}
	else if (a_AsteroidMedium->bIsDead)
	{
		if (!a_AsteroidMedium->bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidsmallarray.push_back(oAsteroidSmall(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY, i));
			}
		}
		UG::StopDrawingSprite(a_AsteroidMedium->iSpriteID);
	}
}
