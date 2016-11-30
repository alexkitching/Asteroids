#ifndef _POSITION_H_
#define _POSITION_H_

class Position
{
public:
	Position();
	void Set(float a_fX, float a_fY);
	void Get(float& a_fX, float& a_fY);
private:
	float fX;
	float fY;
};

#endif
