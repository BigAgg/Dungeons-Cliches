#include "gameObject.h"

gameObject::gameObject()
{

};
gameObject::~gameObject()
{

};

void gameObject::draw(SDL_Renderer* renderer){
	// render texture if the gameObject should be
	if (Rendered){
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
};
void gameObject::update(Uint32 delta){

};
void gameObject::onTick(Uint32 delta){

};

void gameObject::onHit(gameObject* obj){

};

void gameObject::move(float x, float y){
	// move every rect and calc new position of gameObject
	position.x = position.baseX + x;
	position.y = position.baseY + y;
	dstrect.x = position.x;
	dstrect.y = position.y;
	hitbox.x = dstrect.x;
	hitbox.y = dstrect.y;
}

void gameObject::save(std::ofstream* fileObj){
	// setting up saveStruct before saving to file
	saveStruct.sizeW = hitbox.w;
	saveStruct.sizeH = hitbox.h;
	saveStruct.collisionLayer = collisionLayer;
	saveStruct.texID = textureID;
	saveStruct.positionX = std::floor(position.baseX);
	saveStruct.positionY = std::floor(position.baseY);

	// saving saveStruct to given fileObj
	fileObj->write((char*)&saveStruct, sizeof(saveStruct));
}

bool gameObject::isAlive(){
	return Alive;
};
