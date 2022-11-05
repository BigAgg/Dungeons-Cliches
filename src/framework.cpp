#include "framework.h"

bool KEYS[322];
bool JUSTPRESSED[322];

framework::framework(const char* title, int width, int height, bool fullscreen)
{
	// create the window and renderer
	if (createWindow(title, width, height, fullscreen)){
		tM = new textureManager(renderer);
		if (tM->isInitialised){
			isRunning = true;

			// initialising keys
			for (int i = 0; i < 322; i++)
			{
				KEYS[i] = false;
				JUSTPRESSED[i] = false;
			}
			return;
		}
	}
	isRunning = false;
}

framework::~framework()
{
	std::cout << "[FW] System deleted!...\n";
}

bool framework::createWindow(const char* title, int width, int height, bool fullscreen)
{
	float wscale = width / 1920;
	float hscale = height / 1080;
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG))		// Init SDL and SDL_image
	{
		std::cout << "[FW] Subsystems Initialised!..." << "\n";
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_RENDERER_ACCELERATED);		// Building Window with basic Settings
		if (window)
		{
			std::cout << "[FW] Window created!..." << "\n";
			renderer = SDL_CreateRenderer(window, -1, 0);		// Creating renderer
			if (renderer)
			{
				SDL_RenderSetScale(renderer, wscale, hscale);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		// Setting renderer background color to black
				std::cout << "[FW] Renderer created!..." << "\n";
				return true;

			}
		}
	}
	return false;
}

void framework::handleEvents()
{
	// getting window events
	SDL_Event event;
	SDL_PollEvent(&event);
	int keycode;
	switch (event.type)
	{
		// closing game
		case SDL_QUIT:
			isRunning = false;
			break;

		// storing button pressed in array
		case SDL_KEYDOWN:
			keycode = event.key.keysym.sym;
			if (!KEYS[keycode]){
				JUSTPRESSED[keycode] = true;
			}
			KEYS[keycode] = true;
			break;

		// storing button released in array
		case SDL_KEYUP:
			keycode = event.key.keysym.sym;
			KEYS[keycode] = false;
			break;

		default:
			break;
	}
}

void framework::handleInput()
{
	if (KEYS[SDLK_ESCAPE]){
		isRunning = false;
	}
	if(JUSTPRESSED[SDLK_w]){
		std::cout << "w was pressed\n";
	}
	// resetting pressed buttons of current frame
	for (int i=0; i<322; i++){
		JUSTPRESSED[i] = false;
	}
	return;
}

void framework::onTick(double delta)
{
	return;
}

void framework::update(double delta)
{
	return;
}

void framework::handleCollision()
{
	return;
}

void framework::render()
{
	SDL_RenderClear(renderer);

	// adding stuff to render
	SDL_RenderCopy(renderer, tM->things, NULL, NULL);
	

	SDL_RenderPresent(renderer);
}

void framework::clean()
{
	isRunning = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete tM;
	IMG_Quit();
	SDL_Quit();
	std::cout << "[FW] cleaned!..." << "\n";
}