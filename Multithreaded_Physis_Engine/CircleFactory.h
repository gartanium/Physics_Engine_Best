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

	// Settings used to create a circle. 
	int xMax;
	int xMin;
	int yMax;
	int yMin;
	int dXMax; // dx and dy implies velocity
	int dXMin;
	int dYMax;
	int dYMin;
	int screenHeight;
	int screenWidth;
	int radiusMax;
	int radiusMin;

public:
	CircleFactory(int minRadius, int maxRadius, int minVelocity, int maxVelocity, int screenHeight, int screenWidth);
	CircleFactory();
	~CircleFactory();
	void addCircle(int x, int y, std::vector<Circle> & circles);
};

#endif