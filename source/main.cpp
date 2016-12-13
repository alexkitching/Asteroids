#include "UGFW.h"
#include "Enumerations.h"
#include <time.h>
#include <sstream>
#include <string>
#include <iostream>
#include "GameStates.h"
#include "menu.h"
#include "spaceship.h"
#include "asteroids.h" 
#include "assetinit.h"
#include "objectupdatecontroller.h"
#include "scorecontroller.h"
#include "livescontroller.h"

int g_iScreenWidth = 0;
int g_iScreenHeight = 0;
float g_DeltaTime = 0.0f;

int main(int argv, char* argc[])
{
	srand(static_cast<unsigned int>(time(0))); //Seed
	GameState currentState = MENU;
	bool bShouldQuit = false;
	
	do
	{
		switch (currentState)
		{
		case MENU:
		{
			Menu menu;
			currentState = menu.Initialise();
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
				oObjectUpdateController objectupdatecontroller;
				oScorecontroller scorecontroller;
				oLivesController livescontroller;
				oSpaceship spaceship;
				oAsteroidLarge asteroidlargearray[5];
				oAsteroidMedium asteroidmediumarray[15];
				oAsteroidSmall asteroidsmallarray[45];
				
				InitialiseGameAssets(spaceship, asteroidlargearray, asteroidmediumarray, asteroidsmallarray, objectupdatecontroller);
				do
				{
					UG::ClearScreen();
					float fSpaceshipXPos = 0.f, fSpaceshipYPos = 0.f;
					spaceship.pos.Get(fSpaceshipXPos, fSpaceshipYPos);
					g_DeltaTime = UG::GetDeltaTime();
					currentState = objectupdatecontroller.Spaceship(spaceship, asteroidlargearray, asteroidmediumarray, asteroidsmallarray, livescontroller);
					if (currentState == GAMEOVER)
					{
						break;
					}
					for (int i = 0; i < 5; i++)
					{
						if (asteroidlargearray[i].IsActive())
						{
							objectupdatecontroller.AsteroidLarge(asteroidlargearray[i], asteroidmediumarray, scorecontroller);
						}
					}
					for (int i = 0; i < 15; i++)
					{
						if (asteroidmediumarray[i].IsActive())
						{
							objectupdatecontroller.AsteroidMedium(asteroidmediumarray[i], asteroidsmallarray, scorecontroller);
						}
					}
					for (int i = 0; i < 45; i++)

					{
						if (asteroidsmallarray[i].IsActive())
						{
							objectupdatecontroller.AsteroidSmall(asteroidsmallarray[i], scorecontroller);
						}
					}
					scorecontroller.DrawScore();
					livescontroller.DrawLives();
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