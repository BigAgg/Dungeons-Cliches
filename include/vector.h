#pragma once

#include <math.h>

class Vector2{
public:
	Vector2(float xPos, float yPos);
	~Vector2();

	void normalize();
	void zero();
	void reset();

	float x;
	float y;

private:
	float baseX;
	float baseY;
};
