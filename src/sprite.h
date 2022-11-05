#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* getTex(const char* filename, SDL_Renderer* renderer);

class textureManager{
public:
	textureManager(SDL_Renderer* renderer);
	~textureManager();

	SDL_Texture* tileset = NULL;
	SDL_Texture* characters = NULL;
	SDL_Texture* dead = NULL;
	SDL_Texture* things = NULL;
	bool isInitialised = false;
};

class sprite{
public:

};
