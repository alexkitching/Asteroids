#include "asteroids.h";
#include "UGFW.h";
#include "algorithm"
#include "iostream"

extern int g_iScreenHeight;
extern int g_iScreenWidth;

oAsteroid::oAsteroid()
{
}

oAsteroidLarge::oAsteroidLarge()
{
	iScore = 20;
	iWidth = 72;
	iHeight = 72;
	iQty = 4; 
	fSpeedMax = 1.0f;
	fSpeedMin = 0.15f;
}

void oAsteroidLarge::Initialise(oSpawnController& a_spawncontroller, int a_AsteroidNumber, const char * a_AsteroidLargeImageFileName)
{
	
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	pos.Set(a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][0], a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][1]);
	pos.Get(fPosX, fPosY);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}



void oAsteroidLarge::Update(oAsteroidLarge & a_AsteroidLarge)
{
	a_AsteroidLarge.pos.Get(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
	a_AsteroidLarge.vNew.Get(a_AsteroidLarge.fVNewX, a_AsteroidLarge.fVNewY);
	a_AsteroidLarge.fPosX = a_AsteroidLarge.fPosX + a_AsteroidLarge.fVNewX;
	a_AsteroidLarge.fPosY = a_AsteroidLarge.fPosY + a_AsteroidLarge.fVNewY;
	if (a_AsteroidLarge.fPosY >= g_iScreenHeight + a_AsteroidLarge.iHeight)
	{
		a_AsteroidLarge.fPosY = (0.f * (float) g_iScreenHeight) - (float) a_AsteroidLarge.iHeight;
	}
	else if (a_AsteroidLarge.fPosY <= -a_AsteroidLarge.iHeight)
	{
		a_AsteroidLarge.fPosY = ((float) g_iScreenHeight + (float) a_AsteroidLarge.iHeight);
	}

	if (a_AsteroidLarge.fPosX >= g_iScreenWidth + a_AsteroidLarge.iWidth)
	{
		a_AsteroidLarge.fPosX = (0.f * (float) g_iScreenWidth) - (float) a_AsteroidLarge.iWidth;
	}
	else if (a_AsteroidLarge.fPosX <= -a_AsteroidLarge.iWidth)
	{
		a_AsteroidLarge.fPosX = ((float) g_iScreenWidth + (float) a_AsteroidLarge.iWidth);
	}
	UG::MoveSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
	UG::RotateSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fSpriteTurnRate);
	a_AsteroidLarge.pos.Set(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);

}

void oAsteroidLarge::GetDimensions(int &a_iWidth, int &a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oAsteroidLarge::SetRotation(float &a_CurrentRotation)
{
	int iValue = rand() % 2;
	if (iValue == 0)
	{
		a_CurrentRotation = -1.f;
	}
	else if (iValue == 1)
	{
		a_CurrentRotation = 1.f;
	}
}

oAsteroidSmall::oAsteroidSmall()
{
	iScore = 50;
	iWidth = 36;
	iHeight = 36;
}

void oAsteroidSmall::Initialise(oAsteroidSmall & a_AsteroidSmall, const char * a_AsteroidSmallImageFileName)
{
}

void oAsteroidSmall::Update(oAsteroidSmall & a_AsteroidSmall)
{
}

void oAsteroidSmall::GetDimensions(int a_iWidth, int a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}