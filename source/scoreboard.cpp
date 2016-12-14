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
		iNewScore = a_iNewScore; // Sets Possible New Score to Function Parameter Input
		ClearScreen(); //Resets Screen
		bReadSuccess = ReadVectorFromFile(); //Read Scoreboardfile
		std::vector<score>::iterator Iter; //Declare Iterator
		for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter)
		{
			if (!Iter->first == 0)
			{
				iScoreQty++; //Count Quantity of Elements
			}
		}
		if (iNewScore >= 0) //If New Score (Greater than or Equal to 0)
		{
			std::cout << "New Score: " << iNewScore << "!" << std::endl;
			std::cout << "Please Enter Your Name:" << std::endl;
			std::cin >> sNewName; //Stores New Name
			ClearScreen(); //Resets Screen
			if (iScoreQty == 9)
			{
				int iSmallestScore;
				std::sort(scoreboard.begin(), scoreboard.end(), SortAscending()); //Sort Scoreboard by Ascending
				iSmallestScore = scoreboard.back().first;
				if (iNewScore > iSmallestScore) //If New Score is Greater than Smallest Score
				{
					score NewPair(iNewScore, sNewName);
					scoreboard.back().swap(NewPair); //Swap Scores
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
				scoreboard[iScoreQty] = std::make_pair(iNewScore, sNewName); //Add New Score to Vector
				++iScoreQty;
			}
			std::sort(scoreboard.begin(), scoreboard.end(), SortDecending()); //Sort Descending Order
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
		bWriteSuccess = WriteVectorToFile(); //Write to File
		system("pause"); //User Presses Enter
		Sleep(2000);
		gsNewState = GameState::MENU; //Returns to Menu
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
	return a_Pair1.first < a_Pair2.first; //Sorts Vector by Ascending Scores
}

bool oScoreboard::SortDecending::operator()(const score& a_Pair1, const score& a_Pair2) const
{
	return a_Pair1.first > a_Pair2.first; //Sorts Descending by Ascending Scores
}

bool oScoreboard::WriteVectorToFile() //Writes Scores to File
{
	std::string Names[9];  //Create Name Array
	int iScores[9];  //Create Scores Array
	std::vector<score>::iterator Iter;
	int i = 0;
	for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter, ++i) //Iterates through Scoreboard Vector
	{
		Names[i] = Iter->second;  //Adds Names to Array
		iScores[i] = Iter->first; //Adds Scores to Array
	}
	std::fstream file;
	file.open("Names.txt", std::ios_base::out); //Open File
	if (file.is_open())
	{
		for (int j = 0; j < 9; ++j)
		{
			file << Names[j] << std::endl; //Input Names
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close(); //Close File
	file.clear();

	file.open("Scores.txt", std::ios_base::out); //Open File
	if (file.is_open())
	{
		for (int k = 0; k < 9; ++k)
		{
			file << iScores[k] << std::endl; //Input Scores
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close(); //Close File
	file.clear();
	return true;
}

bool oScoreboard::ReadVectorFromFile() //Reads Scores from File
{
	std::string Names[9]; //Create Name Array
	int iScores[9];  //Create Scores Array
	std::fstream file;
	file.open("Names.txt", std::ios_base::in); //Open File
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			std::getline(file, Names[i]); //Read File Items to Array
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close(); // Close File
	file.clear();
	file.open("Scores.txt", std::ios_base::in); // Open File
	if (file.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			file >> iScores[i]; // Read File Items to Array
		}
	}
	else
	{
		return false;
	}
	file.sync();
	file.close(); // Close File
	file.clear();

	std::vector<score>::iterator Iter;
	int i = 0;
	for (Iter = scoreboard.begin(); Iter < scoreboard.end(); ++Iter, ++i)	//Iterate through scoreboard vector
	{
		score NewPair(iScores[i], Names[i]);	//Add Scores to Pair
		Iter->swap(NewPair); // Replace Vector with new Pairs
	}

	return true;
}

