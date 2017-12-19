#pragma once
class Point
{
public:
	Point() { x = 0; y = 0; }
	Point(int x, int y) { this->x = x; this->y = y; }
	~Point();
	int x;
	int y;
};

