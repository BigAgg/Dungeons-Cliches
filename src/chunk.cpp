#include "chunk.h"

chunk::chunk(int x, int y, int size){
	// setting up hitbox and position
	hitbox.h = size;
	hitbox.w = size;
	hitbox.x = x;
	hitbox.y = y;
	position.baseX = x;
	position.baseY = y;
	position.x = x;
	position.y = y;
};

chunk::~chunk(){

};

void chunk::update(Uint32 delta){
	// updating every object inside chunk
	for (gameObject* obj : containingObjects){
		obj->update(delta);
	}
}

void chunk::onTick(Uint32 delta){
	// calling onTick of every object inside chunk
	for (gameObject* obj : containingObjects){
		obj->onTick(delta);
	}
}

void chunk::draw(SDL_Renderer* renderer){
	// rendering every obj in chunk
	for (gameObject* obj : containingObjects){
		obj->draw(renderer);
	}
}

void chunk::move(float x, float y){
	// updating position of chunk
	position.x = position.baseX + x;
	position.y = position.baseY + y;
	hitbox.x = position.x;
	hitbox.y = position.y;
	// updating position of objects in chunk if it is inside clippingRect
	if (Rendered){
		for (gameObject* obj : containingObjects){
			obj->move(x, y);
		}
	}
}

void chunk::save(std::ofstream* fileObj){
	// saving all files inside chunk *NOT WORKING AND USED YET, SAVES ARE USED THROUGH allObjects*
	for (gameObject* obj : containingObjects){
		obj->save(fileObj);
	}
}

void chunk::onHit(gameObject* obj){
	// pushing obj in vector and counting objects inside chunk
	containingObjects.push_back(obj);
	objCnt++;
}
