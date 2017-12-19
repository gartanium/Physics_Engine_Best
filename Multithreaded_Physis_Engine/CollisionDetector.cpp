#include "stdafx.h"
#include "CollisionDetector.h"
#include <iostream>


void CollisionDetector::updateCircleVelocity(Circle & circle, int x, int y)
{
	#pragma omp critical
	{
		circle.setDx(x);
		circle.setDy(y);
	}
	
}

void CollisionDetector::updateCircleVelocity(Circle & circle, Circle & circleRhs)
{
	#pragma omp critical
	{
		circle.setDx(circleRhs.getDx());
		circle.setDy(circleRhs.getDy());
	}
}

void CollisionDetector::updateCircleX(Circle & circle, int x)
{
	#pragma omp critical
		circle.setDx(x);
}

void CollisionDetector::updateCircleY(Circle & circle, int y)
{
	#pragma omp critical
		circle.setDy(y);
}

CollisionDetector::CollisionDetector(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

/**************************************************************************
* Function:
**************************************************************************/
CollisionDetector::~CollisionDetector()
{
}

/**************************************************************************
* Function: Handle Circle Collisions
* Definition: updates each circle's velocity after a collision
**************************************************************************/
void CollisionDetector::handleCircleCollisions(std::vector<Circle>& obj)
{
	int circleSize = obj.size();

	int starter = 0;
	// Cycle through each Circle.
	for (int i = 0; i < circleSize; i++)
	{
		for (int j = i; j < circleSize; j++)
		{
			// Don't collide with it's self.
			if (i == j)
				continue;
			else
			{

				if (obj[i].intersects(obj[j]))
				{
					int tempX = obj[i].getDx();
					int tempY = obj[i].getDy();

					obj[i].setDx(obj[j].getDx());
					obj[i].setDy(obj[j].getDy());

					


					obj[j].setDx(tempX);
					obj[j].setDy(tempY);
					
				}

				
			}
			

		}
		
	}
}

/**************************************************************************
* Function: Handle Circle Collisions Multithreaded
* Definition: updates each circle's velocity after a collision
**************************************************************************/
void CollisionDetector::handleCircleCollisionsMulti(int numThreads, std::vector<Circle>& obj)
{

	int starter = 0;
	// Cycle through each Circle.
	for (int i = 0; i < obj.size(); i++)
	{
		for (int j = i; j < obj.size(); j++)
		{
			// Don't collide with it's self.
			if (i == j)
				continue;
			else
			{

				if (obj[i].intersects(obj[j]))
				{
					int tempX = obj[i].getDx();
					int tempY = obj[i].getDy();

					obj[i].setDx(obj[j].getDx());
					obj[i].setDy(obj[j].getDy());
					obj[j].setDx(tempX);
					obj[j].setDy(tempY);

				}


			}


		}

	}
}

/**************************************************************************
* Function: Handle Screen Collision
* Definition: Handle's each circle's screen collision.
**************************************************************************/
void CollisionDetector::handleScreenCollisions(std::vector<Circle>& obj)
{

	for (int i = 0; i < obj.size(); i++)
	{
		int objX = obj[i].getX();
		int objY = obj[i].getY();
		int radius = obj[i].getRadius();

		// Left side
		if (objX - radius <= 0)
			obj[i].setDx(obj[i].getDx() * -1);
		// Right side
		if (objX + radius >= screenWidth)
			obj[i].setDx(obj[i].getDx() * -1);
		// Top
		if (objY - radius <= 0)
			obj[i].setDy(obj[i].getDy() * -1);
		// Bottom
		if (objY + radius >= screenHeight)
			obj[i].setDy(obj[i].getDy() * -1);
	}
}
