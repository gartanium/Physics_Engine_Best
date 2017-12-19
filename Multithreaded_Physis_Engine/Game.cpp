#include "stdafx.h"
#include "Game.h"

/**************************************************************************
* Function: Initialize
* Definition: Randomly adds circles to the game.
**************************************************************************/
void Game::Initialize()
{
	for (int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
			factory.addCircle(25*i + 10, j*25 + 10, circles);
	}
}

/**************************************************************************
* Function: Non-Default Constructor
**************************************************************************/
Game::Game(int screenWidth, int screenHeight)
{
	collisionDetector = CollisionDetector(screenWidth, screenHeight);
	factory = CircleFactory(screenHeight, screenWidth);
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	Initialize();

	
}

/**************************************************************************
* Function: Deconstructor
**************************************************************************/
Game::~Game()
{

}

/**************************************************************************
* Function: Advance
* Definition: Advances all object in the game.
**************************************************************************/
void Game::advance()
{
	for (int i = 0; i < circles.size(); i++)
	{
		circles[i].advance();
	}

	collisionDetector.handleCircleCollisions(circles);
	
}

void Game::handleCollisions()
{
	
	collisionDetector.handleCircleCollisions(circles);
}

void Game::handleScreen()
{
	collisionDetector.handleScreenCollisions(circles);
}



/**************************************************************************
* Function: Draw
* Definition: Renders all object to the screen.
* SDL_Renderer * renderer: The Graphics renderer
**************************************************************************/
void Game::draw(SDL_Renderer * renderer, UiDraw & ui)
{
	for (int i = 0; i < circles.size(); i++)
	{
		ui.drawBlueCircle(renderer, circles[i].getRadius(),
			circles[i].getX(), circles[i].getY());
	}

}

/**************************************************************************
* Function: HandleInput
* Definition: Handle's user input
**************************************************************************/
void Game::handleInput()
{
}
