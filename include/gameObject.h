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

	void draw(SDL_Renderer* renderer);
	virtual void update(Uint32 delta);
	virtual void onTick(Uint32 delta);
	virtual void move(float x, float y);
	virtual void save(std::ofstream* fileObj);

	bool isAlive();

	SDL_Rect dstrect;
	SDL_Rect srcrect;
	SDL_Rect hitbox;
	SDL_Texture* texture;
	Vector2 position;
	Vector2 velocity;
	int index;
	Uint32 collisionLayer;
	Uint32 textureID;

	struct {
		char type[20];
		Uint32 sizeW;
		Uint32 sizeH;
		Uint32 collisionLayer;
		Uint32 texID;
		Uint32 positionX;
		Uint32 positionY;
	} saveStruct;

private:
	bool Rendered = true;
	bool Alive = true;
};
