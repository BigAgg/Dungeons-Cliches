#include "vector.h"

Vector2::Vector2(float xPos = 0, float yPos = 0){
	x = xPos;
	y = yPos;
	baseX = xPos;
	baseY = yPos;
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