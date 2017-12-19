#pragma once
#include <vector>
#include "Circle.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

class CircleFactory
{
private:
	// Screen bounds for the circles being generated.
	int xMax;
	int xMin;
	int yMax;
	int yMin;
	int dXMax;
	int dXMin;
	int dYMax;
	int dYMin;
	int screenHeight;
	int screenWidth;
	int radiusMax;
	int radiusMin;

public:
	CircleFactory(int screenHeight, int screenWidth);
	CircleFactory();
	~CircleFactory();
	void addCircle(int x, int y, std::vector<Circle> & circles);
};

#endif