#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{

private:
	int x;
	int y;
	int dx;
	int dy;
	int radius;
	int centerX;
	int centerY;

	// RGB values.
	int rgbR;
	int rgbG;
	int rgbB;
	int rgbA;
	
	


public:
	Circle();
	~Circle();

	// Setters
	void setX(int value)  { x  = value; }
	void setY(int value)  { y  = value; }
	void setDx(int value) { dx = value; }
	void setDy(int value) { dy = value; }

	void setRadius(int value) { radius = value; }

	void addDx(int value) { dx += value; }
	void addDy(int value) { dy += value; }

	void clearDx() { dx = 0; }
	void clearDy() { dy = 0; }

	// RGB setters
	void setRgbR(int value) { rgbR = value; }
	void setRgbG(int value) { rgbG = value; }
	void setRgbB(int value) { rgbB = value; }
	void setRgbA(int value) { rgbA = value; }

	// Getters
	int getX()  { return x;  }
	int getY()  { return y;  }
	int getDx() { return dx; }
	int getDy() { return dy; }

	int getRadius() { return radius; }

	// RGB getters
	int getRgbR() { return rgbR; }
	int getRgbG() { return rgbG; }
	int getRgbB() { return rgbB; }
	int getRgbA() { return rgbA; }

	void advance();

	// Collision
	bool intersects(Circle & circle);
	bool contains(int x, int y);
};

#endif