////////////////////////////////////////////////////////////////////
// File: <main.cpp>
// Author: <Alex Kitching>
// Date Created: <29/11/16>
// Brief: <Source file for the Main Function.>
////////////////////////////////////////////////////////////////////

#include "UGFW.h"
#include "GameStates.h"
#include "menu.h"
#include "scoreboard.h"
#include "howtoplay.h"
#include "Spaceship.h"
#include "asteroids.h" 
#include "assetinit.h"
#include "ObjectUpdateController.h"
#include "Scorecontroller.h"
#include "Livescontroller.h"
#include <Enumerations.h>
#include <time.h>
#include <sstream>
#include <string>
#include <iostream>

int g_iScreenWidth = 0;
int g_iScreenHeight = 0;
float g_fDeltaTime = 0.0f;

void ClearObjects(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller, oScorecontroller& a_rScorecontroller, oObjectUpdateController& a_rObjectUpdateController, oSpawncontroller& a_rSpawncontroller);

int main(int argv, char* argc[])
{
	srand(static_cast<unsigned int>(time(0))); //Seed
	GameState gsCurrentState = MENU;
	bool bShouldQuit = false;
	bool bQuitGameplay = false;
	int iFinalScore = -1;

	do
	{
		switch (gsCurrentState)
		{
		case MENU:
		{
			Menu menu;
			gsCurrentState = menu.Initialise();
			break;
		}
		case SCOREBOARD:
		{
			oScoreboard Scoreboard;
			gsCurrentState = Scoreboard.Initialise(iFinalScore);
			break;
		}
		case HOWTOPLAY:
		{
			Howtoplay howtoplay;
			gsCurrentState = howtoplay.Initialise();
			break;
		}

		case GAMEPLAY:
		{
			//Screen Dimensions
			if (UG::Create(800, 600, false, "Asteroids", 100, 100))
			{
				UG::GetScreenSize(g_iScreenWidth, g_iScreenHeight);

				UG::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
				UG::AddFont("./fonts/invaders.fnt");
				UG::SetFont("./fonts/invaders.fnt");
				//Create Objects
				oObjectUpdateController ObjectUpdateController;
				oScorecontroller Scorecontroller;
				oLivescontroller Livescontroller;
				oSpawncontroller Spawncontroller;
				oSpaceship Spaceship;
				oAsteroidLarge aAsteroidLargeArray[5];
				oAsteroidMedium aAsteroidMediumArray[15];
				oAsteroidSmall aAsteroidSmallArray[45];
				oUFOEasy UFOEasy;
				oUFOHard UFOHard;

				InitialiseGameAssets(Spaceship, aAsteroidLargeArray, aAsteroidMediumArray, aAsteroidSmallArray, UFOEasy, UFOHard, ObjectUpdateController, Spawncontroller);
				do
				{
					UG::ClearScreen();
					float fSpaceshipXPos = 0.f, fSpaceshipYPos = 0.f;
					Spaceship.pos.Get(fSpaceshipXPos, fSpaceshipYPos);
					g_fDeltaTime = UG::GetDeltaTime();
					bQuitGameplay = ObjectUpdateController.Spaceship(Spaceship, aAsteroidLargeArray, aAsteroidMediumArray, aAsteroidSmallArray, UFOEasy, UFOHard, Livescontroller, Scorecontroller);
					if (bQuitGameplay == true)
					{
						iFinalScore = Scorecontroller.CurrentScore();
						ClearObjects(Spaceship, aAsteroidLargeArray, aAsteroidMediumArray, aAsteroidSmallArray, UFOEasy, UFOHard, Livescontroller, Scorecontroller, ObjectUpdateController, Spawncontroller);
						gsCurrentState = SCOREBOARD;
						bQuitGameplay = false;
						break;
					}
					for (int i = 0; i < 5; i++)
					{
						if (aAsteroidLargeArray[i].IsActive())
						{
							ObjectUpdateController.AsteroidLarge(aAsteroidLargeArray[i], aAsteroidMediumArray);
						}
					}
					for (int i = 0; i < 15; i++)
					{
						if (aAsteroidMediumArray[i].IsActive())
						{
							ObjectUpdateController.AsteroidMedium(aAsteroidMediumArray[i], aAsteroidSmallArray);
						}
					}
					for (int i = 0; i < 45; i++)

					{
						if (aAsteroidSmallArray[i].IsActive())
						{
							ObjectUpdateController.AsteroidSmall(aAsteroidSmallArray[i]);
						}
					}
					if (UFOEasy.IsActive())
					{
						ObjectUpdateController.UFOEasy(UFOEasy, Spaceship, aAsteroidLargeArray, aAsteroidMediumArray, aAsteroidSmallArray, Livescontroller);
					}
					if (UFOHard.IsActive())
					{
						ObjectUpdateController.UFOHard(UFOHard, Spaceship, aAsteroidLargeArray, aAsteroidMediumArray, aAsteroidSmallArray, Livescontroller);

					}

					Spawncontroller.UFOSpawncontroller(UFOEasy, UFOHard, Scorecontroller);

					//Extra Life Gained Every 10,000 points
					if (Scorecontroller.LivesScore() > 10000)
					{
						Livescontroller.ExtraLife();
						Scorecontroller.ResetLivesScore();
					}
					Scorecontroller.DrawScore();
					Livescontroller.DrawLives();
				} while (UG::Process());
			}
			UG::Dispose();
			break;
		}
		case GAMEOVER:
		{
			bShouldQuit = true;
			break;
		}
		}
	} while (!bShouldQuit);

	return 0;
}

//Clears Game Of Sprites and Objects
void ClearObjects(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller, oScorecontroller& a_rScorecontroller, oObjectUpdateController& a_rObjectUpdateController, oSpawncontroller& a_rSpawncontroller)
{
	if (a_rSpaceship.IsActive())
	{
		a_rSpaceship.Destroy(a_rSpaceship, a_rLivescontroller);
	}
	a_rSpaceship.~oSpaceship();
	for (int i = 0; i < 5; i++)
	{
		if (a_paAsteroidLargeArray[i].IsActive())
		{
			a_paAsteroidLargeArray[i].Destroy(a_paAsteroidLargeArray[i]);
		}
		a_paAsteroidLargeArray[i].~oAsteroidLarge();
	}
	for (int i = 0; i < 15; i++)
	{
		if (a_paAsteroidMediumArray[i].IsActive())
		{
			a_paAsteroidMediumArray[i].Destroy(a_paAsteroidMediumArray[i]);
		}
		a_paAsteroidMediumArray[i].~oAsteroidMedium();
	}
	for (int i = 0; i < 45; i++)
	{
		if (a_paAsteroidSmallArray[i].IsActive())
		{
			a_paAsteroidSmallArray[i].Destroy(a_paAsteroidSmallArray[i]);
		}
		a_paAsteroidSmallArray[i].~oAsteroidSmall();
	}
	if (a_rUFOEasy.IsActive())
	{
		a_rUFOEasy.Destroy(a_rUFOEasy);
	}
	a_rUFOEasy.~oUFOEasy();

	if (a_rUFOHard.IsActive())
	{
		a_rUFOHard.Destroy(a_rUFOHard);
	}
	a_rUFOHard.~oUFOHard();

	a_rLivescontroller.~oLivescontroller();
	a_rScorecontroller.~oScorecontroller();
	a_rSpawncontroller.~oSpawncontroller();
	a_rObjectUpdateController.~oObjectUpdateController();
}