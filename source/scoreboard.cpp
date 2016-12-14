////////////////////////////////////////////////////////////////////
// File: <scoreboard.cpp>
// Author: <Alex Kitching>
// Date Created: <14/12/16>
// Brief: <Source file for the Scoreboard Class.>
////////////////////////////////////////////////////////////////////

#include "scoreboard.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

GameState oScoreboard::Initialise(int a_iNewScore)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Sets Console Text to White
	while (bActive == true)
	{
		bIsSorted = false;
		iNewScore = a_iNewScore;
		ClearScreen(); //Resets Screen
		bReadSuccess = ReadVectorFromFile();
		std::vector<score>::iterator Iter; //Declare Iterator
		for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter)
		{
			if (!Iter->first == 0)
			{
				iScoreQty++;
			}
		}
		if (iNewScore >= 0) //If New Score
		{
			std::cout << "New Score: " << iNewScore << "!" << std::endl;
			std::cout << "Please Enter Your Name:" << std::endl;
			std::cin >> sNewName;
			ClearScreen(); //Resets Screen
			if (iScoreQty == 9)
			{
				int iSmallestScore;
				std::sort(scoreboard.begin(), scoreboard.end(), SortAscending());
				iSmallestScore = scoreboard.back().first;
				if (iNewScore > iSmallestScore)
				{
					score NewPair(iNewScore, sNewName);
					scoreboard.back().swap(NewPair);
				}
				else
				{
					std::cout << "No Highscore Set, Better Luck Next Time!" << std::endl;
					iNewScore = 0;
					sNewName = "";
					system("PAUSE");
				}
			}
			else
			{
				scoreboard[iScoreQty] = std::make_pair(iNewScore, sNewName);
				++iScoreQty;
			}
			std::sort(scoreboard.begin(), scoreboard.end(), SortDecending());
			bIsSorted = true;
		}
		if (!bIsSorted) //If Not Sorted
		{
			std::sort(scoreboard.begin(), scoreboard.end(), SortDecending()); //Sort
		}
		//Begin Printing Scores
		ClearScreen();
		std::cout << "Position:           Name:            Score:" << std::endl;
		int i = 0; //Counter
		for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter, ++i)
		{
			if (i < iScoreQty)
			{
				std::cout << " " <<  i + 1 << "                  " << Iter->second << "              " << Iter->first << std::endl;
			}
			else
			{
				std::cout << " " << i + 1 << "              Score not set" << std::endl;
			}
		}
		bWriteSuccess = WriteVectorToFile();
		system("pause");
		Sleep(2000);
		gsNewState = GameState::MENU;
		bActive = false;
	}
	system("cls");
	return gsNewState;
}

void oScoreboard::ClearScreen()
{
	system("cls");
	std::cout << "Asteroids Scoreboard" << std::endl;
}

bool oScoreboard::SortAscending::operator()(const score& a_Pair1, const score& a_Pair2) const
{
	return a_Pair1.first < a_Pair2.first;
}

bool oScoreboard::SortDecending::operator()(const score& a_Pair1, const score& a_Pair2) const
{
	return a_Pair1.first > a_Pair2.first;
}

bool oScoreboard::WriteVectorToFile()
{
	std::string Names[9];
	int Scores[9];
	std::vector<score>::iterator Iter;
	int i = 0;
	for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter, ++i)
	{
		Names[i] = Iter->second;
		Scores[i] = Iter->first;
	}
	std::fstream file;
	file.open("Names.txt", std::ios_base::out);
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			file << Names[i] << std::endl;
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close();
	file.clear();

	file.open("Scores.txt", std::ios_base::out);
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			file << Scores[i] << std::endl;
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close();
	file.clear();
	return true;
}

bool oScoreboard::ReadVectorFromFile()
{
	std::string Names[9];
	int Scores[9];
	std::fstream file;
	file.open("Names.txt", std::ios_base::in);
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			std::getline(file, Names[i]);
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close();
	file.clear();
	file.open("Scores.txt", std::ios_base::in);
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			file >> Scores[i];
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close();
	file.clear();

	std::vector<score>::iterator Iter;
	int i = 0;
	for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter, ++i)
	{
		score NewPair(Scores[i], Names[i]);
		Iter->swap(NewPair);
	}

	return true;
}

