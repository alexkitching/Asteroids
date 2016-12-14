#ifndef _POSITION_H_
#define _POSITION_H_

class Position
{
public:

	Position(); //Constructor

	void Set(float a_fX, float a_fY);
	void Get(float& a_rfX, float& a_rfY);
	void SetRandom(); //Set Random Position
private:

	float fX;
	float fY;
};

#endif