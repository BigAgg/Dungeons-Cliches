#pragma once

#include "gameObject.h"

class player : public gameObject{
public:
	player(SDL_Texture* texture, int chosenCharacter);
	~player();

	void onTick(Uint32 delta);
	void update(Uint32 delta);
	void move(float x, float y);

private:
	Uint32 timer;
	int speed = 150;
	int chosenCharacter;
	int rotation = 0;
	int frame = 1;
};