#include <iostream>
#include "framework.h"

// setting up game and getting settings
framework* game = nullptr;
int res[2] = {2560, 1440};
Uint32 FPS = 60;

int main(int argc, char *argv[])
{
	game = new framework("MyRPG", res[0], res[1], 1);
	Uint32 delta;
	Uint32 tick = SDL_GetTicks();

	// main gameloop
	while (game->running()){
		delta = SDL_GetTicks() - tick;		// calculating deltatime of last frame
		//if (delta >= 1000 / FPS)		// locking framerate if game is running too fast
		//{
		tick = SDL_GetTicks();

		game->handleEvents();		// handling events just as closing or resizing the window
		game->handleInput();		// handling button press
		game->onTick(delta);		// calling all objects with onTick function
		game->handleCollision();	// checking collisions
		game->render();				// rendering everything on screen
		//}
		//else
		//{
			//SDL_Delay(1);		// wait 1 tick if delta time is too short
		//}
	}
	// cleaning and deleting game
	game->clean();
	delete game;
	SDL_Delay(3000);
	return 0;
}