#include "stdafx.h"
#include "CircleFactory.h"

/**************************************************************************
* Function: Non-default constructor
* Initializes the Circle Factory with given settings as inputs.
* Creates each circle based upon the settings.
**************************************************************************/
CircleFactory::CircleFactory(int minRadius, int maxRadius, int minVelocity, int maxVelocity, int screenHeight, int screenWidth)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;

	xMax = screenWidth / 2 + screenWidth / 4;
	yMax = screenHeight / 2 + screenHeight / 4;

	xMin = screenWidth / 2 - screenWidth / 4;
	yMin = screenHeight / 2 - screenHeight / 4;

	dXMax = maxVelocity;
	dXMin = minVelocity;
	dYMax = maxVelocity;
	dYMin = minVelocity;

	radiusMax = maxRadius;
	radiusMin = minRadius;

	//radiusMax = 3;
	//radiusMin = 1;
}

/**************************************************************************
* Function: Default constructor.
* Sets all values to default.
**************************************************************************/
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

/**************************************************************************
* Function: Deconstructor
**************************************************************************/
CircleFactory::~CircleFactory()
{
}

/**************************************************************************
* Function: AddCircle
* Addes a circle to a vector. Takes as inputs the position of the circle.
* The factory generates each circle based upon the circle settings.
**************************************************************************/
void CircleFactory::addCircle(int x, int y, std::vector<Circle> & circles)
{


	srand(time(NULL) + circles.size() * 1000 % time(NULL));

	int randDx = rand() % dXMax + dXMin;
	int randDy = rand() % dYMax + dYMin;
	int randRadius = rand() % radiusMax + radiusMin;
	

	/*int randDx = 2;
	int randDy = 2;
	int randRadius = 8;
	*/
	Circle newObj;
	newObj.setX(x);
	newObj.setY(y);
	newObj.setDx(randDx);
	newObj.setDy(randDy);
	newObj.setRadius(randRadius);

	circles.push_back(newObj);


}
