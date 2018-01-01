#pragma once
#include <SDL.h>
class  UiDraw
{

public:
	UiDraw();
	~UiDraw();
	void drawCircle(SDL_Renderer * gRenderer, int radius,  int x0, int y0, SDL_Color color);
	void drawRedCircle(SDL_Renderer * gRenderer, int radius, int x0, int y0);
};

