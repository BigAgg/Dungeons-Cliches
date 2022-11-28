#include "framework.h"

bool KEYS[322];
bool JUSTPRESSED[322];
std::vector<gameObject*> objects;

framework::framework(const char* title, int width, int height, bool fullscreen)
{
	// create the window and renderer
	if (createWindow(title, width, height, fullscreen)){
		oM = new objManager(renderer);
		oM->loadLevel("level.txt");
		Player = new player(SDL_CreateTextureFromSurface(renderer, oM->characters), 1);
		mouseColider = new SDL_Rect();
		mouseColider->w = 1;
		mouseColider->h = 1;
		mouseColider->x = 0;
		mouseColider->y = 0;
		if (oM->isInitialised){
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
	float wscale = width / 960;
	float hscale = height / 540;
	windowScaleW = wscale;
	windowScaleH = hscale;
	clippingRect = new SDL_Rect();
	clippingRect->w = 960;
	clippingRect->h = 540;
	clippingRect->x = 0;
	clippingRect->y = 0;
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
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		// Creating renderer
			if (renderer)
			{
				SDL_RenderSetLogicalSize(renderer, 960, 540);
				SDL_RenderSetScale(renderer, wscale, hscale);
				SDL_RenderSetClipRect(renderer, clippingRect);
				SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);		// Setting renderer background color to black
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
	objects = getObjects();
	SDL_Event event;
	SDL_PollEvent(&event);

	// getting mouse position in current frame
	mouseButtons = SDL_GetMouseState(&mousePos[0], &mousePos[1]);
	mousePos[0] = (mousePos[0] / windowScaleW) - 480;
	mousePos[1] = (mousePos[1] / windowScaleH) - 270;
	mouseColider->x = mousePos[0] + 480;
	mouseColider->y = mousePos[1] + 270;

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
		oM->saveLevel("level.txt");
		isRunning = false;
	}

	if (KEYS[SDLK_1]){
		oM->saveLevel("level.txt");
	}

	if (KEYS[SDLK_w]){
		Player->velocity.y = 1;
	}

	if (KEYS[SDLK_s]){
		if (Player->velocity.y == 1){
			Player->velocity.y = 0;
		}
		else Player->velocity.y = -1;
	}

	if (KEYS[SDLK_a]){
		Player->velocity.x = 1;
	}

	if (KEYS[SDLK_d]){
		if (Player->velocity.x == 1){
			Player->velocity.x = 0;
		}
		else Player->velocity.x = -1;
	}

	if (JUSTPRESSED[SDLK_SPACE]){
		sprite* sp;
		sp = new sprite(mouseColider->x - Player->position.x, mouseColider->y - Player->position.y, 16, 16, 0, oM->tiles[0]->tileTex, 0);
		pushBackObjects(sp);
	}
	// resetting pressed buttons of current frame
	for (int i=0; i<322; i++){
		JUSTPRESSED[i] = false;
	}
	return;
}

void framework::onTick(Uint32 delta)
{
	for (gameObject* i : objects){
		if (i->isAlive()){
			i->move(std::round(Player->position.x), std::round(Player->position.y));
			i->onTick(delta);
			i->update(delta);
		}
	}
	Player->onTick(delta);
	Player->update(delta);
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
	for (gameObject* i : objects){
		i->draw(renderer);
		i->velocity.zero();
	}
	Player->draw(renderer);
	Player->velocity.zero();
	// SDL_RenderCopy(renderer, surface, NULL, NULL)
	

	SDL_RenderPresent(renderer);
}

void framework::clean()
{
	isRunning = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete oM;
	IMG_Quit();
	SDL_Quit();
	std::cout << "[FW] cleaned!..." << "\n";
}