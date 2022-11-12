#include "sprite.h"

sprite::sprite(int posX, int posY, int sizeW, int sizeH, int colisionLayer, SDL_Texture* t){
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	this->collisionLayer = colisionLayer;
	texture = t;
	srcrect.h = h;
	srcrect.w = w;
	srcrect.x = 0;
	srcrect.y = 0;
	position.x = posX;
	position.y = posY;
	position.baseX = posX;
	position.baseY = posY;
	dstrect.h = srcrect.h;
	dstrect.w = srcrect.w;
	hitbox.x = posX;
	hitbox.y = posY;
	hitbox.w = sizeW;
	hitbox.h = sizeH;
};

sprite::~sprite(){

};