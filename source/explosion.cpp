#include "explosion.h"
#include "UGFW.h"

extern float g_DeltaTime;

Explosion::Explosion()
{
	fCurrentLife = fMaxLife;
}

Explosion::~Explosion()
{
}

void Explosion::Update(float a_fPosX, float a_fPosY)
{
	while (fCurrentLife > 0.f)
	{
		if (!bDrawn)
		{
			for (int i = 0; i < 4; i++)
			{
				pos[i].Set(a_fPosX, a_fPosY);
				pos[i].Get(fPosX[i], fPosY[i]);
			}
			bDrawn = true;
		}

		if (bDrawn)
		{
			UG::DrawLine(fPosX[1] + iLineLength, fPosY[1] + iLineLength, fPosX[1] - iLineLength, fPosY[1] - iLineLength);
			UG::DrawLine(fPosX[2] + iLineLength, fPosY[2] + iLineLength, fPosX[2] - iLineLength, fPosY[3] - iLineLength);
			UG::DrawLine(fPosX[3] + iLineLength, fPosY[3] - iLineLength, fPosX[3] - iLineLength, fPosY[3] + iLineLength);
			UG::DrawLine(fPosX[4] + iLineLength, fPosY[4] - iLineLength, fPosX[4] - iLineLength, fPosY[4] + iLineLength);

			for (int i = 0; i < 4; i++)
			{
				float fVecX = 0.f, fVecY = 0.f;
				vec[i].Get(fVecX, fVecY);
				fPosX[i] += fVecX;
				fPosY[i] += fVecY;
			}
		}
		fCurrentLife -= g_DeltaTime;
	}
}
