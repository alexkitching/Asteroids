#ifndef _POSITION_H_
#define _POSITION_H_

class Position
{
public:
	Position();
	void Set(float a_x, float a_y);
	void Get(float& a_x, float& a_y);

private:
	float x;
	float y;
};

#endif
