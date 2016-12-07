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
}

void oAsteroidLarge::Initialise(oSpawnController& a_spawncontroller, int a_AsteroidNumber, const char * a_AsteroidLargeImageFileName)
{
	
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	float fPosX = 0.f, fPosY = 0.f;
	pos.Set(a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][0], a_spawncontroller.iSpawnPosArray[a_AsteroidNumber][1]);
	pos.Get(fPosX, fPosY);
	NewVec.SetRandom(iSpeedMin, iSpeedMax);
	SetRotation(iSpriteTurnRate);
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
	UG::RotateSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.iSpriteTurnRate);
	a_AsteroidLarge.pos.Set(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);

}

void oAsteroidLarge::GetDimensions(int &a_iWidth, int &a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oAsteroidLarge::CollisionCheck(oAsteroidLarge* a_asteroidlarge)
{
	for (int i = 0; i < 4; i++)
	{

		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{

			}
			else 
			{
				int iHalfAsteroidWidth = (int)(a_asteroidlarge[i].iWidth * 0.5f);
				int iHalfAsteroidHeight = (int)(a_asteroidlarge[i].iHeight * 0.5f);
				float fAPosX = 0.f, fAPosY = 0.f;
				a_asteroidlarge[i].pos.Get(fAPosX, fAPosY);
				float fBPosX = 0.f, fBPosY = 0.f;
				a_asteroidlarge[j].pos.Get(fBPosX, fBPosY);

				if (fAPosX - iHalfAsteroidWidth < fBPosX + iHalfAsteroidWidth && fAPosX + iHalfAsteroidWidth > fBPosX - iHalfAsteroidWidth) 
				{ //Collision on X Axis
					if (fAPosY - iHalfAsteroidHeight < fBPosY + iHalfAsteroidHeight && fAPosY + iHalfAsteroidHeight > fBPosY - iHalfAsteroidHeight)
					{ //Collision on Y Axis
						//Flip Asteroid Direction
						a_asteroidlarge[i].fNewVecX *= -1;
						a_asteroidlarge[i].fNewVecY *= -1;
						a_asteroidlarge[j].fNewVecX *= -1;
						a_asteroidlarge[j].fNewVecY *= -1;
						a_asteroidlarge[i].NewVec.Set(a_asteroidlarge[i].fNewVecX, a_asteroidlarge[i].fNewVecY);
						a_asteroidlarge[j].NewVec.Set(a_asteroidlarge[j].fNewVecX, a_asteroidlarge[j].fNewVecY);
						fAPosX = fAPosX + a_asteroidlarge[i].fNewVecX;
						fAPosY = fAPosY + a_asteroidlarge[i].fNewVecY;
						fBPosX = fBPosX + a_asteroidlarge[j].fNewVecX;
						fBPosY = fBPosY + a_asteroidlarge[j].fNewVecY;
						UG::MoveSprite(a_asteroidlarge[i].iSpriteID, fAPosX, fAPosY);
						UG::MoveSprite(a_asteroidlarge[j].iSpriteID, fBPosX, fBPosY);
						a_asteroidlarge[i].pos.Set(fAPosX, fAPosY);
						a_asteroidlarge[j].pos.Set(fBPosX, fBPosY); 
					}
				}
				if (fAPosY - iHalfAsteroidHeight < fBPosY + iHalfAsteroidHeight && fAPosY + iHalfAsteroidHeight > fBPosY - iHalfAsteroidHeight)
				{ //Collision on Y Axis
					if (fAPosX - iHalfAsteroidWidth < fBPosX + iHalfAsteroidWidth && fAPosX + iHalfAsteroidWidth > fBPosX - iHalfAsteroidWidth)
					{//Collision on X Axis
						//Flip Asteroid Direction
						a_asteroidlarge[i].fNewVecX *= -1;
						a_asteroidlarge[i].fNewVecY *= -1;
						a_asteroidlarge[j].fNewVecX *= -1;
						a_asteroidlarge[j].fNewVecY *= -1;
						a_asteroidlarge[i].NewVec.Set(a_asteroidlarge[i].fNewVecX, a_asteroidlarge[i].fNewVecY);
						a_asteroidlarge[j].NewVec.Set(a_asteroidlarge[j].fNewVecX, a_asteroidlarge[j].fNewVecY);
						fAPosX = fAPosX + a_asteroidlarge[i].fNewVecX;
						fAPosY = fAPosY + a_asteroidlarge[i].fNewVecY;
						fBPosX = fBPosX + a_asteroidlarge[j].fNewVecX;
						fBPosY = fBPosY + a_asteroidlarge[j].fNewVecY;
						UG::MoveSprite(a_asteroidlarge[i].iSpriteID, fAPosX, fAPosY);
						UG::MoveSprite(a_asteroidlarge[j].iSpriteID, fBPosX, fBPosY);
						a_asteroidlarge[i].pos.Set(fAPosX, fAPosY);
						a_asteroidlarge[j].pos.Set(fBPosX, fBPosY);
						
					}
				}
			}
		}
	}
}

void oAsteroidLarge::SetRotation(int &a_CurrentRotation)
{
	int iValue = rand() % 2;
	if (iValue == 0)
	{
		a_CurrentRotation = -1;
	}
	else if (iValue == 1)
	{
		a_CurrentRotation = 1;
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