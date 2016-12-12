#ifndef _LIVESCONTROLLER_H_
#define _LIVESCONTROLLER_H_

class oLivesController
{
public:
	oLivesController();
	void DrawLives();
	void UpdateLives(int a_inewlives);
	
	friend class oObjectController;
private:
	int iCurrentLives = 3;
};
#endif // !_LIVESCONTROLLER_H_
