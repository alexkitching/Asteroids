#include "UGFW.h"
#include "Enumerations.h"
#include <time.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
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
				std::vector<oAsteroidLarge> asteroidlarge;
				std::vector<oAsteroidMedium> asteroidmedium;
				std::vector<oAsteroidSmall> asteroidsmall;
				
				InitialiseGameAssets(spaceship, asteroidlarge);
				do
				{
					float fSpaceshipXPos = 0.f, fSpaceshipYPos = 0.f;
					spaceship.pos.Get(fSpaceshipXPos, fSpaceshipYPos);
					g_DeltaTime = UG::GetDeltaTime();
					objectupdatecontroller.SpaceshipUpdate(spaceship, asteroidlarge, asteroidmedium, asteroidsmall, livescontroller);
					for (int i = 0; i < 5; i++)
					{
						objectupdatecontroller.AsteroidLargeUpdate(asteroidlarge[i], asteroidmedium, scorecontroller);
					}
					for (std::vector<oAsteroidMedium>::iterator i = asteroidmedium.begin(); i != asteroidmedium.end(); i++)
					{
						objectupdatecontroller.AsteroidMediumUpdate(i, asteroidsmall, scorecontroller);
					}
					for (std::vector<oAsteroidSmall>::iterator i = asteroidsmall.begin(); i != asteroidsmall.end(); i++)
					{
						objectupdatecontroller.AsteroidSmallUpdate(i, scorecontroller);
					}
					scorecontroller.DrawScore();
					livescontroller.DrawLives();
					UG::ClearScreen();
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