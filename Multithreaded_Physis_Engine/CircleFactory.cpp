#include "stdafx.h"
#include "CircleFactory.h"

CircleFactory::CircleFactory(int screenHeight, int screenWidth)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;

	xMax = screenWidth / 2 + screenWidth / 4;
	yMax = screenHeight / 2 + screenHeight / 4;

	xMin = screenWidth / 2 - screenWidth / 4;
	yMin = screenHeight / 2 - screenHeight / 4;

	dXMax = 1;
	dXMin = 1;
	dYMax = 1;
	dYMin = 1;

	radiusMax = 8;
	radiusMin = 5;

	//radiusMax = 3;
	//radiusMin = 1;
}

CircleFactory::CircleFactory()
{
	xMax = 0;
	xMin = 0;
	yMin = 0;
	yMax = 0;
	screenHeight = 0;
	screenWidth = 0;
	radiusMax = 0;
	radiusMin = 0;
	dXMax = 0;
	dXMin = 0;
	dYMax = 0;
	dYMin = 0;
}


CircleFactory::~CircleFactory()
{
}

void CircleFactory::addCircle(int x, int y, std::vector<Circle> & circles)
{


	srand(time(NULL) + circles.size() * 1000 % time(NULL));

	int randDx = rand() % dXMax + dXMin;
	int randDy = rand() % dYMax + dYMin;
	int randRadius = rand() % radiusMax + radiusMin;


	Circle newObj;
	newObj.setX(x);
	newObj.setY(y);
	newObj.setDx(randDx);
	newObj.setDy(randDy);
	newObj.setRadius(randRadius);

	circles.push_back(newObj);


}
