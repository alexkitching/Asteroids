////////////////////////////////////////////////////////////////////
// File: <Livescontroller.h>
// Author: <Alex Kitching>
// Date Created: <12/12/16>
// Brief: <Header file for the Lives Controller Class.>
////////////////////////////////////////////////////////////////////
#ifndef _Livescontroller_H_
#define _Livescontroller_H_

class oLivescontroller
{
public:

	oLivescontroller() {}; //Constructor
	~oLivescontroller() {}; //Destructor

	//Functions
	void DrawLives();
	int CurrentLives();
	void UpdateLives(int a_iNewLives);
	void ExtraLife();

	//Friend Classes
	friend class oObjectUpdateController;

private:

	//Variables
	int iCurrentLives = 3;
};
#endif // !_Livescontroller_H_
