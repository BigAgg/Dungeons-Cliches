#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "sprite.cpp"
#include "vector.cpp"

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

	tile* testTile;

private:
	bool isRunning = false;

	int mousePos[2] = {0, 0};
	Uint32 mouseButtons;
	float windowScaleW, windowScaleH;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* display;
	SDL_Rect* clippingRect;
	SDL_Rect* mouseColider;
	textureManager* tM;
};