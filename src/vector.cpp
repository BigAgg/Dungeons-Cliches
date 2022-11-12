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
	float result;
	result = pow((x*x) + (y*y), 0.5);
	x = x / result;
	y = y / result;
};

void Vector2::zero(){
	x = 0;
	y = 0;
};

void Vector2::reset(){
	x = baseX;
	y = baseY;
};