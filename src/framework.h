#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "sprite.h"
#include "vector.h"

class framework{
public:
	framework(const char* title, int width, int height, bool fullscreen);
	~framework();

	bool createWindow(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void handleInput();
	void handleCollision();
	void onTick(double delta);
	void update(double delta);
	void render();
	void clean();

	bool running()
	{
		return isRunning;
	};

private:
	bool isRunning = false;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* display;
	textureManager* tM;
};