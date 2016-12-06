#include "asteroids.h";
#include "UGFW.h";
#include "algorithm"

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
}

void oAsteroidLarge::Initialise(oSpawnController& a_spawncontroller, int a_AsteroidNumber, const char * a_AsteroidLargeImageFileName)
{
	
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	float fPosX = 0.f, fPosY = 0.f;
	pos.Set(a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][0], a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][1]);
	pos.Get(fPosX, fPosY);
	NewVec.SetRandom(iSpeedMin, iSpeedMax);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}



void oAsteroidLarge::Update(oAsteroidLarge & a_AsteroidLarge)
{
	a_AsteroidLarge.pos.Get(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
	a_AsteroidLarge.NewVec.Get(a_AsteroidLarge.fNewVecX, a_AsteroidLarge.fNewVecY);
	a_AsteroidLarge.fCurrentVecX = a_AsteroidLarge.fPosX + a_AsteroidLarge.fNewVecX;
	a_AsteroidLarge.fCurrentVecY = a_AsteroidLarge.fPosY + a_AsteroidLarge.fNewVecY;
	a_AsteroidLarge.fPosX = a_AsteroidLarge.fCurrentVecX;
	a_AsteroidLarge.fPosY = a_AsteroidLarge.fCurrentVecY;
	
	if (a_AsteroidLarge.fPosY >= g_iScreenHeight + a_AsteroidLarge.iHeight)
	{
		a_AsteroidLarge.fPosY = (0 * g_iScreenHeight) - a_AsteroidLarge.iHeight;
	}
	else if (a_AsteroidLarge.fPosY <= -a_AsteroidLarge.iHeight)
	{
		a_AsteroidLarge.fPosY = (g_iScreenHeight + a_AsteroidLarge.iHeight);
	}

	if (a_AsteroidLarge.fPosX >= g_iScreenWidth + a_AsteroidLarge.iWidth)
	{
		a_AsteroidLarge.fPosX = (0 * g_iScreenWidth) - a_AsteroidLarge.iWidth;
	}
	else if (a_AsteroidLarge.fPosX <= -a_AsteroidLarge.iWidth)
	{
		a_AsteroidLarge.fPosX = (g_iScreenWidth + a_AsteroidLarge.iWidth);
	}

	UG::MoveSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fCurrentVecX, a_AsteroidLarge.fCurrentVecY);
	a_AsteroidLarge.pos.Set(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);

}

void oAsteroidLarge::GetDimensions(int a_iWidth, int a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oAsteroidLarge::CollisionCheck(oAsteroidLarge* a_asteroidlarge)
{
	
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