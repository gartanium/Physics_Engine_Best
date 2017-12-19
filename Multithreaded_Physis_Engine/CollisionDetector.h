#pragma once
#ifndef COLLISSIONDETECTOR_H
#define COLLISIONDETECTOR_H
#include "Circle.h"
#include <vector>
#include "Point.h"

class CollisionDetector
{

private:
	int screenWidth;
	int screenHeight;
	void updateCircleVelocity(Circle & circle, int x, int y);
	void updateCircleVelocity(Circle & circle, Circle & circleRhs);
	void updateCircleX(Circle & circle, int x);
	void updateCircleY(Circle & circle, int y);

public:
	CollisionDetector() { screenWidth = 0; screenHeight = 0; }
	CollisionDetector(int screenWidth, int screenHeight);
	~CollisionDetector();
	void handleCircleCollisions(std::vector<Circle> & obj);
	void handleScreenCollisions(std::vector<Circle> & obj);
	void handleCircleCollisionsMulti(int numThreads, std::vector<Circle>& obj);
};

#endif