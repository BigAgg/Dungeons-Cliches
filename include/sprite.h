#pragma once

#include "gameObject.h"
#include <SDL2/SDL.h>

class sprite : public gameObject{
public:
	sprite(float posX, float posY, int sizeW, int sizeH, int colisionLayer, SDL_Texture* t, int texID);
	~sprite();
};