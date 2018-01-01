#pragma once
#ifndef GAME_H
#define GAME_H


#include "uiDraw.h"
#include <SDL.h>
#include <vector>
#include "Circle.h"
#include "CollisionDetector.h"
#include "CircleFactory.h"

class Game
{

private:
	std::vector<Circle> circles; // All circles to be drawn in game.
	CollisionDetector collisionDetector;
	CircleFactory factory;
	int screenWidth;
	int screenHeight;
	void Initialize(); // Adds all the circles to the game.
	

public:

	Game(int screenWidth, int screenHeight, int minRadius, int maxRadius, int minVelocity, int maxVelocity);
	~Game();

	/**************************************************************************
	 * Advance all objects in the game
	**************************************************************************/
	void advance();

	void handleCollisions();

	void handleScreen();

	/**************************************************************************
	* Draw all objects in the game
	**************************************************************************/
	void draw(SDL_Renderer * renderer, UiDraw & ui);

	/**************************************************************************
	* Handle User Input
	**************************************************************************/
	void handleInput();

};

#endif