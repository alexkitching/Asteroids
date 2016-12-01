#include "asteroids.h";
#include "UGFW.h";

oAsteroidLarge::oAsteroidLarge()
{

}

void oAsteroidLarge::Initialise(const char * a_AsteroidLargeImageFileName)
{

	pos.SetRandom();
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	float fX = 0.f, fY = 0.f;
	pos.Get(fX, fY);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fX, fY);
}

void oAsteroidLarge::SetSpriteID(int a_id)
{
	iSpriteID = a_id;
}

void oAsteroidLarge::Update(oAsteroidLarge & a_AsteroidLarge)
{
}

void oAsteroidLarge::CheckSpawnCollision(oAsteroidLarge & a_asteroidlarge)
{
}

oAsteroidSmall::oAsteroidSmall()
{
}

void oAsteroidSmall::Initialise(oAsteroidSmall & a_AsteroidSmall, const char * a_AsteroidSmallImageFileName)
{
}

void oAsteroidSmall::Update(oAsteroidSmall & a_AsteroidSmall)
{
}
