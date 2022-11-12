#pragma once

#include <math.h>

class Vector2{
public:
	Vector2();
	~Vector2();

	void normalize();
	void zero();
	void reset();

	float x;
	float y;

	float baseX;
	float baseY;
};
