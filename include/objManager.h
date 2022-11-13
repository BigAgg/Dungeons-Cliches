#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "vector.h"
#include "gameObject.h"
#include "sprite.h"
#include "player.h"
#include <iostream>

std::vector<gameObject*> getObjects();

int getGameObjectCount();

void clearGameObjects();

void pushBackObjects(gameObject* obj);

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


class objManager{
public:
	objManager(SDL_Renderer* renderer);
	~objManager();

	void saveLevel(std::string filename);
	void loadLevel(std::string filename);


	SDL_Surface* tileset = NULL;
	SDL_Surface* characters = NULL;
	SDL_Surface* dead = NULL;
	SDL_Surface* things = NULL;

	tile* tiles[128];

	bool isInitialised = false;
	std::vector<gameObject*> objects;
};
