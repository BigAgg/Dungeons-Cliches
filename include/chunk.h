#pragma once

#include <SDL2/SDL.h>
#include "gameObject.h"

class chunk : public gameObject{
public:
	chunk(int x, int y, int size);
	~chunk();

	void update(Uint32 delta);
	void onTick(Uint32 delta);
	void draw(SDL_Renderer* renderer);
	void move(float x, float y);
	void save(std::ofstream* fileObj);
	void onHit(gameObject* obj);

	int objCnt = 0;
	std::vector<gameObject*> containingObjects;
};