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

void gameObject::save(std::ofstream* fileObj){
	struct {
		const char* type;
		int sizeW;
		int sizeH;
		int collisionLayer;
		int texID;
		int positionX;
		int positionY;
	} saveStruct;
	saveStruct.type = type;
	saveStruct.sizeW = hitbox.w;
	saveStruct.sizeH = hitbox.h;
	saveStruct.collisionLayer = collisionLayer;
	saveStruct.texID = textureID;
	saveStruct.positionX = position.baseX;
	saveStruct.positionY = position.baseY;
	fileObj->write((char*)&saveStruct, sizeof(saveStruct));
}

bool gameObject::isAlive(){
	return Alive;
};
