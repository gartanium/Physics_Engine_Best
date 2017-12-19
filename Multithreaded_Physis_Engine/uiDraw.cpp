#include "stdafx.h"
#include "uiDraw.h"


UiDraw::UiDraw()
{
}


UiDraw::~UiDraw()
{
}

/*
 * Draw a circle to the screen.
 * Function courtesy of Wikipedia.
 */
void UiDraw::drawCircle(SDL_Renderer * gRenderer, int radius,
	int x0, int y0, SDL_Color color)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
	
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 - y);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 - y);
		

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
		
	}
}

void UiDraw::drawBlueCircle(SDL_Renderer * gRenderer, int radius, int x0, int y0)
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0x88);

	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 - y);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 - y);


		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}

	}
}
