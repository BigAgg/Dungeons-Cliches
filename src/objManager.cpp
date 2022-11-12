#include "objManager.h"

int gameObjectCount = 0;
std::vector<gameObject*> allObjects;

std::vector<gameObject*> getObjects(){
	return allObjects;
}

int getGameObjectCount(){
	return gameObjectCount;
}

void clearGameObjects(){
	for (gameObject* i : allObjects){
		delete i;
	}
	allObjects.clear();
	gameObjectCount = 0;
}

SDL_Surface* getSurf(int sizeW, int sizeH){
	SDL_Surface* surf = SDL_CreateRGBSurface(0, sizeW, sizeH, 32, 0, 0, 0, 0);
	surf->w = sizeW;
	surf->h = sizeH;
	SDL_SetColorKey(surf, true, 0);
	return surf;
}

SDL_Rect* getRect(int sizeW, int sizeH, int posX=0, int posY=0){
	SDL_Rect* rect;
	rect = new SDL_Rect();
	rect->x = posX;
	rect->y = posY;
	rect->w = sizeW;
	rect->h = sizeH;
	return rect;
}

// tile class
tile::tile(const char* name, int id[2], int collisionLayer, SDL_Surface* texture, int idxW, int idxH, int sizeW, int sizeH){
	this->name = name;
	this->id[0] = id[0];
	this->id[1] = id[1];
	colLayer = collisionLayer;
	srcrect = getRect(sizeW, sizeH, idxW*16, idxH*16);
	dstrect = getRect(sizeW, sizeH);
	tileSurf = getSurf(sizeW, sizeH);
	SDL_BlitSurface(texture, srcrect, tileSurf, dstrect);
}

tile::~tile(){
	SDL_FreeSurface(tileSurf);
	SDL_DestroyTexture(tileTex);
}

void tile::createOwnTexture(SDL_Renderer* renderer){
	tileTex = SDL_CreateTextureFromSurface(renderer, tileSurf);
}

const char* tileNames[128] = {
	"stonewalldown1",
	"stonewall1",
	"stonewalldown2",
	"stonewall2",
	"redstonewalldown1",
	"redstonewall1",
	"redstonewalldown2",
	"redstonewall2",
	"woodfloordiagonal",
	"redcarpet",
	"sandfloor",
	"grass",
	"grasswithflowers",
	"water",
	"stonefloor",
	"dirtcliff",
	"woodfloor",
	"redyellowcarpet",
	"sandcircle",
	"grasscircle",
	"bush",
	"waterfall",
	"black",
	"dirtcliffrender",
	"dungeondirtcornerlt",
	"dungeondirtmidtop",
	"dungeondirtcornerrt",
	"pot",
	"potbroken",
	"wateranimation1",
	"tanne",
	"well",
	"dungeondirtmidleft",
	"dungeonentrance",
	"dungeondirtmidright",
	"chestopen",
	"chestclosed",
	"wateranimation2",
	"singletree",
	"destroyedpillar",
	"dungeondirtcornerlb",
	"dungeondirtmidbot",
	"dungeondirtcornerrb",
	"smallredcastle",
	"smallvillageicon",
	"bed",
	"podest",
	"statue",
	"closedwoodendoor",
	"closedirondoor",
	"dungeonentranceoutside",
	"lanternposts",
	"papermap",
	"EMPTY",
	"table",
	"kommode",
	"stairsup",
	"stairsdown",
	"pebbles",
	"lanternpostsclose",
	"firepot1",
	"firepot2",
	"dirtmountain",
	"icystonemountain",
	"grasswithlittlegrass",
	"densegrass",
	"dirtoverlava",
	"post",
	"stonepile",
	"juwelry",
	"armorbanner",
	"sicklebanner",
	"dirtpath",
	"stonepath",
	"lava1",
	"lava2",
	"tree2",
	"2trees",
	"swordbanner",
	"potionbanner",
	"stonebridgevertical",
	"stonebridgehorizontal",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"woodenbridgevertical",
	"woodenbridgehorizontal",
	"EMPTY",
	"Stonepillar",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY",
	"EMPTY"
};

// objManager class
objManager::objManager(SDL_Renderer* renderer){
	tileset = IMG_Load("res/Textures/basictiles.png");
	characters = IMG_Load("res/Textures/characters.png");
	dead = IMG_Load("res/Textures/dead.png");
	things = IMG_Load("res/Textures/things.png");
	int x = 0;
	int y = 0;
	for (int i = 0; i<128; i++){
		tile* newTile;
		int id[2] = {0, i};
		if (i == 45 || i == 91){
			newTile = new tile(tileNames[i], id, 0, tileset, x, y, 16, 32);
		}
		else{
			newTile = new tile(tileNames[i], id, 0, tileset, x, y, 16, 16);
		}
		newTile->createOwnTexture(renderer);
		tiles[i] = newTile;

		x++;
		if (x>7){
			y++;
			x=0;
		}
	}


	x = 0;
	y = 0;
	int idx = 0;
	for (int i = 0; i < 100000; i++){
		sprite* testSprite;
		testSprite = new sprite(x * 16, y * 16, 16, 16, 0, tiles[idx]->tileTex);
		allObjects.push_back(testSprite);
		x++;
		idx ++;
		if (idx >= 128){
			idx = 0;
		}
		if (x >= 8){
			y++;
			x-=x;
		}
	}
	
	// checking if every texture was loaded in properly
	if(tileset && characters && dead && things){
		isInitialised = true;
		std::cout << "[TM] created!...\n";
		return;
	}
	std::cout << "[TM] init failed!...\n";
};

objManager::~objManager(){
	SDL_FreeSurface(tileset);
	SDL_FreeSurface(characters);
	SDL_FreeSurface(dead);
	SDL_FreeSurface(things);
	for (tile* t : tiles){
		delete t;
	}
	std::cout << "[TM] deleted!...\n";
};
