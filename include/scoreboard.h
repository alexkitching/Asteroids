////////////////////////////////////////////////////////////////////
// File: <Scoreboard.h>
// Author: <Alex Kitching>
// Date Created: <14/12/16>
// Brief: <Header file for the Scoreboard Class.>
////////////////////////////////////////////////////////////////////
#ifndef _Scoreboard_H_
#define _Scoreboard_H_

#include "GameStates.h"
#include <vector>
#include <string>
#include <iostream>

class oScoreboard
{
public:
	oScoreboard() { bActive = true; };
	~oScoreboard() {};
	GameState Initialise(int a_iNewScore);
private:
	bool bActive;
	bool bIsSorted;
	bool bReadSuccess;
	bool bWriteSuccess;
	int iNewScore;
	int iScoreQty = 0;
	std::string sFileName = "Scoreboardfile";
	GameState gsNewState;

	typedef std::pair<int, std::string> score;

	std::string sNewName;
	std::vector<score> scoreboard = std::vector<score>(9);

	struct SortAscending 
	{
		bool operator()(const score& a_Pair1, const score& a_Pair2) const;
	};
	struct SortDecending
	{
		bool operator()(const score& a_Pair1, const score& a_Pair2) const;
	};

	void ClearScreen();
	bool WriteVectorToFile();
	bool ReadVectorFromFile();
};

#endif // !_Scoreboard_H_
