#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "Position.h"
#include "vector.h"
class Explosion
{
public:
	Explosion();
	void Update(float a_fPosX, float a_fPosY);
	~Explosion();
private:
	float fCurrentLife = -1.f;
	float fMaxLife = 30.f;
	int iColour = 0xFFFFFF;
	bool bDrawn = false;
	float fMoveRate = 0.5f;
	int iLineLength = 4;
	float fPosX[4];
	float fPosY[4];
	float fNewPosX;

	Position pos[4];
	Vector vec[4] = { { fMoveRate,fMoveRate }, {-fMoveRate,-fMoveRate }, { fMoveRate,-fMoveRate }, {-fMoveRate, fMoveRate } };
};



#endif // !_EXPLOSION_H_
