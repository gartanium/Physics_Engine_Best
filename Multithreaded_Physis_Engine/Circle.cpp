#include "stdafx.h"
#include "Circle.h"
#include <iostream>

/**************************************************************************
* Function: Constructor
**************************************************************************/
Circle::Circle()
{
}

/**************************************************************************
* Function: Deconstructor
**************************************************************************/
Circle::~Circle()
{
	
}

/**************************************************************************
* Function: Advance
**************************************************************************/
void Circle::advance()
{
	x += dx;
	y += dy;
}

/**************************************************************************
* Function: Intersects
* Definition: Returns true if a circle intersects this circle
**************************************************************************/
bool Circle::intersects(Circle & circle)
{
	float distanceX = x - circle.x;
	float distanceY = y - circle.y;
	float radiusSum = radius + circle.radius;
	return distanceX * distanceX + distanceY * distanceY <= radiusSum * radiusSum + radiusSum;
}

/**************************************************************************
* Function: Contains
* Definition: Returns true if a point intersects this circle.
**************************************************************************/
bool Circle::contains(int pntX, int pntY)
{
	float distanceX = x - pntX;
	float distanceY = y - pntY;
	return distanceX * distanceX + distanceY * distanceY <= radius * radius;
}
