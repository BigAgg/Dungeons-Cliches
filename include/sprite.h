#pragma once

#include "gameObject.h"
#include <SDL2/SDL.h>

class sprite : public gameObject{
public:
	sprite(int posX, int posY, int sizeW, int sizeH, int colisionLayer, SDL_Texture* t);
	~sprite();
};