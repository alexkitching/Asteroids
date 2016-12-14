////////////////////////////////////////////////////////////////////
// File: <Scorecontroller.h>
// Author: <Alex Kitching>
// Date Created: <12/12/16>
// Brief: <Header file for the Score Controller Class.>
////////////////////////////////////////////////////////////////////
#ifndef _Scorecontroller_H_
#define _Scorecontroller_H_

class oScorecontroller
{
public:

	oScorecontroller() {}; //Constructor
	~oScorecontroller() {}; //Destructor

	//Functions
	void DrawScore();
	void UpdateScore(int a_inewscore);
	void ResetRoundScore();
	void ResetLivesScore();
	int CurrentScore();
	int RoundScore();
	int LivesScore();

	//Friend Classes
	friend class oObjectUpdateController;
private:

	//Score Variables
	int iCurrentScore = 0;
	int iRoundScore = 0;
	int iLivesScore = 0;
};

#endif // !_Scorecontroller_H_
