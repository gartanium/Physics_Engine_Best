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



/**************************************************************************
* Function: HandleEvents
* Function never implemented. Kept incase it is used in the future.
* Usefull for handeling keyboard input and other events.
**************************************************************************/
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
* Definition: All game advance logic goes in here. Function used for
* Single threaded version of program. All collision logic is called in this
* function.
**************************************************************************/
void advance(Game & game)
{
	game.advance();
	game.handleCollisions();
	game.handleScreen();
}

/**************************************************************************
* Function: AdvanceThread1
* Used for advancing the multithreaded version of the program. This
* function advances the position of each object and checks for all screen 
* collisions.
**************************************************************************/
void advanceThread1(Game & game)
{
	game.advance();
	game.handleScreen();
}

/**************************************************************************
* Function: AdvanceThread2
* Used for advancing the multithreaded version of the program. When called,
* the game updates all collisions.
**************************************************************************/
void advanceThread2(Game & game)
{
	game.handleCollisions();
}

/**************************************************************************
* Function: Single Thread
* Runs the program using one thread.
* Single thread handles opengl, object to object collision, and
* object to screen collisions.
**************************************************************************/
void singleThread(Game game, UiDraw ui, Timer frameTimer, Timer timer, bool quit, long frameCount)
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

/**************************************************************************
* Function: Two Threads
* Runs the program using two threads. One thread handles Opengl,
* the other thread handles object to object collisions and object to screen
* collisions. Having the extra thread to handel open_gl does not
* significantly increase performance. According to the Visual Studios Analyze tool,
* most of the program time is spent on collision detection. This is no shock as
* I used an N^2 ( N squared ) algorithim for object to object collision detection.
**************************************************************************/
void twoThreads(Game game, UiDraw ui, Timer frameTimer, Timer timer, bool quit, long frameCount)
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

/**************************************************************************
* Function: Three Threads
* Runs the program using three Threads. With the appropriate settings, the program
* runs at 63 frames a second or double the time of the single and double threaded
* options.
**************************************************************************/
void threeThreads(Game game, UiDraw ui, Timer frameTimer, Timer timer, bool quit, long frameCount)
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

/**************************************************************************
* Function: getSettings
* Gets the program settings from the User.
**************************************************************************/
void getSettings(int & option, int & maxVelocity, int & minVelocity, int & maxRadius, int & minRadius)
{
	std::cout << "Max Velocity: ";
	std::cin >> maxVelocity;

	std::cout << "Min Velocity: ";
	std::cin >> minVelocity;

	std::cout << "Max Radius: ";
	std::cin >> maxRadius;

	std::cout << "Min Radius: ";
	std::cin >> minRadius;


	std::cout << "Choose an option: ";
	std::cin >> option;

	if (option == 1)
		std::cout << "Open Mp 2 thread Option chosen\n";
	else if (option == 0)
		std::cout << "Single threaded Option chosen\n";
	else if (option == 2)
		std::cout << "Three threads openMP Option chosen\n";
}

/**************************************************************************
* Function: Main
* Driver for the program.
**************************************************************************/
int main(int argc, char* args[])
{
	int option;
	int maxVelocity, minVelocity, maxRadius, minRadius;

	getSettings(option, maxVelocity, minVelocity, maxRadius, minRadius);

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
			// Timer for max frame time. Used to make sure we only have 62 frames a minute.
			Timer timer; 
			timer.updateTimer(SDL_GetTicks());
			
			// Class for handleing rendering Circles on the screen.
			UiDraw ui;

			// Class for updating and advancing circles
			Game game(SCREEN_WIDTH, SCREEN_HEIGHT, minRadius, maxRadius, minVelocity, maxVelocity);

			// Timer used to keep track how many frames are run every second.
			Timer frameTimer;

			// Number of frames per second
			long frameCount = 0;
			bool displayThreadCount = true;

			// Boolean for determining when to exit the program.
			bool quit = false;

			// Single thread option.
			if (option == 0) 
			{
				singleThread(game, ui, frameTimer, timer, quit, frameCount);	
			}
			// Two threads. One thread handles OpenGl. The other thread handles Physics.
			else if (option == 1) 
			{
				twoThreads(game, ui, frameTimer, timer, quit, frameCount);
			}
			// Three threads. One thread handles OpenGl. 
			// One thread handles screen collisions. One thread handles object to object collisions.
			else if (option == 2) 
			{					  
				threeThreads(game, ui, frameTimer, timer, quit, frameCount);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}