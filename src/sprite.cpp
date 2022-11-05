#include "sprite.h"

// loading texture from given file, returning SDL_Texture
SDL_Texture* getTex(const char* filename, SDL_Renderer* renderer){
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(filename);
	// check if surface was created
	if (surface){
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}

textureManager::textureManager(SDL_Renderer* renderer){
	tileset = getTex("res/Textures/basictiles.png", renderer);
	characters = getTex("res/Textures/characters.png", renderer);
	dead = getTex("res/Textures/dead.png", renderer);
	things = getTex("res/Textures/things.png", renderer);
	
	// checking if every texture was loaded in properly
	if(tileset && characters && dead && things){
		isInitialised = true;
		std::cout << "[TM] created!...\n";
		return;
	}
	std::cout << "[TM] init failed!...\n";
};

textureManager::~textureManager(){
	SDL_DestroyTexture(tileset);
	SDL_DestroyTexture(characters);
	SDL_DestroyTexture(dead);
	SDL_DestroyTexture(things);
	std::cout << "[TM] deleted!...\n";
};