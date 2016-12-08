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
	void SetDrawn(bool a_drawn);
	bool IsActive();
	bool IsDrawn();
	void Update(oBullet & a_Bullet);
	void Draw(float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY);
	int iSpriteID = -1;
private:
	bool bDrawn = false;
	bool bActive = false;
	int const iHeight = 3;
	int const iWidth = 3;
	float const fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	int const fMaxDistance = 400.f;
	float fPosX = 0.f;
	float fPosY = 0.f;
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	Vector vNew = Vector(0.0f, 0.0f);
	Position pos;

};
#endif
