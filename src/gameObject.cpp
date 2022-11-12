#include "gameObject.h"

gameObject::gameObject()
{

};
gameObject::~gameObject()
{

};

void gameObject::draw(SDL_Renderer* renderer){
	if (Rendered){
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
};
void gameObject::update(Uint32 delta){
	dstrect.x = position.x;
	dstrect.y = position.y;
	hitbox.x = position.x;
	hitbox.y = position.y;
};
void gameObject::onTick(Uint32 delta){

};

void gameObject::move(float x, float y){
	position.x = position.baseX + x;
	position.y = position.baseY + y;
	dstrect.x = position.x;
	dstrect.y = position.y;
	hitbox.x = dstrect.x;
	hitbox.y = dstrect.y;
}

bool gameObject::isAlive(){
	return Alive;
};
