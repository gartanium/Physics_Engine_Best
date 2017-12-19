/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include "stdafx.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Game.h"
#include "uiDraw.h"
#include "Timer.h"
#include <omp.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;  // I have commited the unpardonable sin

							 //The window renderer
SDL_Renderer* gRenderer = NULL; // I have commited the unpardonable sin

void handleEvents(SDL_Event e, bool & quit)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
	}
}

/**************************************************************************
* Function: Init
* Definition: Initializes SDL
**************************************************************************/
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

/**************************************************************************
* Function: Load Media
* Definition: Loads any media associated with the project.
**************************************************************************/
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

/**************************************************************************
* Function: Close
* Definition: Destroys SDL. Deallocates memory associates with SDL
**************************************************************************/
void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/**************************************************************************
* Function: LoadTexture
* Definition: Loads any texture required.
**************************************************************************/
SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

/**************************************************************************
* Function: Update Graphics
* Definition: Called to update the Graphics
**************************************************************************/
void updateGraphics(Game & game, UiDraw & ui)
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_Color color; color.a = 0x88; color.b = 0xFF; color.b = 0x00;
	color.r = 0x00;

	game.draw(gRenderer, ui);

	//Update screen
	SDL_RenderPresent(gRenderer);
}

/**************************************************************************
* Function: Advance
* Definition: All game advance logic goes in here.
**************************************************************************/
void advance(Game & game)
{
	game.advance();
	game.handleCollisions();
	game.handleScreen();
}

void advanceThread1(Game & game)
{
	game.advance();
	game.handleScreen();
}

void advanceThread2(Game & game)
{
	game.handleCollisions();
}

int main(int argc, char* args[])
{
	int option;

	std::cout << "Choose an option: ";
	std::cin >> option;

	if (option == 1)
		std::cout << "Open Mp 2 thread Option chosen\n";
	else if (option == 0)
		std::cout << "Single threaded Option chosen\n";
	else if (option == 2)
		std::cout << "Three threads openMP Option chosen\n";


	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			Timer timer;
			timer.updateTimer(SDL_GetTicks());
			UiDraw ui;
			Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
			Timer frameTimer;
			long frameCount = 0;
			bool displayThreadCount = true;
			bool quit = false;

			if (option == 0)
			{

				frameTimer.startTimer(SDL_GetTicks());
				//Event handler
				while (quit == false)
				{




					updateGraphics(game, ui);
					timer.startTimer(SDL_GetTicks());
					advance(game);
					timer.updateTimer(SDL_GetTicks());

					timer.resetTimer();
					frameCount++;
					frameTimer.updateTimer(SDL_GetTicks());
					if (frameTimer.hasTimeElapsed(1000))
					{
						std::cout << "Frames: " << frameCount;
						std::cout << " Time: " << frameTimer.timeElapsed();
						std::cout << '\n';
						frameCount = 0;
						frameTimer.startTimer(SDL_GetTicks());
					}

					// pause the program until end of frame.
					while (!timer.hasTimeElapsed(SCREEN_TICKS_PER_FRAME))
					{
						timer.updateTimer(SDL_GetTicks());
					}
				}
			}
			else if (option == 1)
			{



#pragma omp parallel num_threads(2)
				{
					frameTimer.startTimer(SDL_GetTicks());
					int ID = omp_get_thread_num();

					//Game Loop
					while (!quit)
					{
						if (ID == 0)
						{
							updateGraphics(game, ui);
						}
						else
						{
							timer.startTimer(SDL_GetTicks());
							advance(game);
							timer.updateTimer(SDL_GetTicks());

							// pause the program until end of frame.
							while (!timer.hasTimeElapsed(SCREEN_TICKS_PER_FRAME))
							{
								timer.updateTimer(SDL_GetTicks());
							}

							timer.resetTimer();
							frameCount++;
							frameTimer.updateTimer(SDL_GetTicks());
							if (frameTimer.hasTimeElapsed(1000))
							{
								std::cout << "Frames: " << frameCount;
								std::cout << " Time: " << frameTimer.timeElapsed();
								std::cout << '\n';
								frameCount = 0;
								frameTimer.startTimer(SDL_GetTicks());
							}

						}

#pragma omp barrier
					}

				}
			}
			else if (option == 2)
			{
#pragma omp parallel num_threads(3)
				{
					frameTimer.startTimer(SDL_GetTicks());
					int ID = omp_get_thread_num();

					//Game Loop
					while (!quit)
					{
						if (ID == 0)
						{
							updateGraphics(game, ui);
						}
						else if (ID == 1)
						{
							timer.startTimer(SDL_GetTicks());
							advanceThread1(game);
							timer.updateTimer(SDL_GetTicks());

							// pause the program until end of frame.
							while (!timer.hasTimeElapsed(SCREEN_TICKS_PER_FRAME))
							{
								timer.updateTimer(SDL_GetTicks());
							}

							timer.resetTimer();
							frameCount++;
							frameTimer.updateTimer(SDL_GetTicks());
							if (frameTimer.hasTimeElapsed(1000))
							{
								std::cout << "Frames: " << frameCount;
								std::cout << " Time: " << frameTimer.timeElapsed();
								std::cout << '\n';
								frameCount = 0;
								frameTimer.startTimer(SDL_GetTicks());
							}

						}
						else
						{
							advanceThread2(game);

						}

#pragma omp barrier
					}

				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}