#ifndef _BULLET_H_
#define _BULLET_H_
#include "position.h"
#include "spaceship.h"
#include "vector.h"
class oBullet
{
public:
	oBullet();
	~oBullet();
	void SetActive(bool a_active);
	bool IsActive();
	void Update(oBullet & a_Bullet);
	void Draw(oSpaceship& a_spaceship);
	int iSpriteID = -1;
	friend class oSpaceship;
private:
	bool bActive = false;
	int const iHeight = 3;
	int const iWidth = 3;
	float const fSpeed = 2.f;
	int const iMaxDistance = 100;
	float fPosX = 0.f;
	float fPosY = 0.f;
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	Vector vNew = Vector(0.0f, 0.0f);
	Position pos;
};
#endif
