#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "vector.h"
#include <iostream>
#include <fstream>

class gameObject{
public:
	gameObject();
	virtual ~gameObject();

	virtual void draw(SDL_Renderer* renderer);
	virtual void update(Uint32 delta);
	virtual void onTick(Uint32 delta);
	virtual void onHit(gameObject* obj);
	virtual void move(float x, float y);
	virtual void save(std::ofstream* fileObj);

	bool isAlive();

	SDL_Rect dstrect;
	SDL_Rect srcrect;
	SDL_Rect hitbox;
	SDL_Texture* texture;
	Vector2 position;
	Vector2 velocity;
	int32_t index;
	int32_t collisionLayer;
	int32_t textureID;
	bool isInChunk = false;
	bool Rendered = true;

	struct {
		char type[20];
		int32_t sizeW;
		int32_t sizeH;
		int32_t collisionLayer;
		int32_t texID;
		int32_t positionX;
		int32_t positionY;
	} saveStruct;

private:
	bool Alive = true;
};
