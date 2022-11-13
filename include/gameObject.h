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

	const char* type = "gameObject";
	SDL_Rect dstrect;
	SDL_Rect srcrect;
	SDL_Rect hitbox;
	SDL_Texture* texture;
	Vector2 position;
	Vector2 velocity;
	int index;
	int collisionLayer;
	int textureID;

private:
	bool Rendered = true;
	bool Alive = true;
};
