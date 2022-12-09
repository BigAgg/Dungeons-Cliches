#include "vector.h"

Vector2::Vector2(){
	x = 0;
	y = 0;
	baseX = 0;
	baseY = 0;
};

Vector2::~Vector2(){

};

void Vector2::normalize(){
	// calculating the multipier to normalize x and y
	float result;
	result = pow((x*x) + (y*y), 0.5);

	// calculate x and y using given multiplier result
	x = x / result;
	y = y / result;
};

void Vector2::zero(){
	// nulling positions
	x = 0;
	y = 0;
};

void Vector2::reset(){
	// reset to baseposition
	x = baseX;
	y = baseY;
};