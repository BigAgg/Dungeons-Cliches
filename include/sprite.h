#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "vector.h"
#include <iostream>

SDL_Surface* getSurf(int sizeW, int sizeH);
SDL_Rect* getRect(int sizeW, int sizeH, int posX, int posY);

class tile{
public:
	tile(const char* name, int id[2], int collisionLayer, SDL_Surface* texture, int idxW, int idxH, int sizeW, int sizeH);
	~tile();
	void createOwnTexture(SDL_Renderer* renderer);

	SDL_Surface* tileSurf = NULL;
	SDL_Texture* tileTex = NULL;
	SDL_Rect* dstrect;
	SDL_Rect* srcrect;
	int width;
	int height;
	const char* name;
	int colLayer;
	int id[2] = {0,0};
};


class sprite{
public:
	sprite(int posX, int posY, int sizeW, int sizeH, int tileid[2], int colisionLayer);
	~sprite();

	SDL_Rect* dstrect;
	int collisionLayer;
	int id[2];
	int pos[2];
};


class textureManager{
public:
	textureManager(SDL_Renderer* renderer);
	~textureManager();


	SDL_Surface* tileset = NULL;
	SDL_Surface* characters = NULL;
	SDL_Surface* dead = NULL;
	SDL_Surface* things = NULL;

	tile* tiles[128];

	bool isInitialised = false;
	std::vector<sprite*> sprites;
};
