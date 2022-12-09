#include "objManager.h"

int gameObjectCount = 0;
int chunkSize = 32;		// 32x32 tiles
int tileSize = 16;
std::vector<gameObject*> allObjects;
std::vector<gameObject*> chunks;

std::vector<gameObject*> getChunks(){
	return chunks;
}

std::vector<gameObject*> getObjects(){
	return allObjects;
}

int getGameObjectCount(){
	return gameObjectCount;
}

void clearGameObjects(){
	// clears all objects and resets counter to 0
	allObjects.clear();
	gameObjectCount = 0;
}

void pushBackChunks(gameObject* obj){
	chunks.push_back(obj);
}

void pushBackObjects(gameObject* obj){
	allObjects.push_back(obj);
}

SDL_Surface* getSurf(int sizeW, int sizeH){
	// creating surface with given size and returning it
	SDL_Surface* surf = SDL_CreateRGBSurface(0, sizeW, sizeH, 32, 0, 0, 0, 0);
	surf->w = sizeW;
	surf->h = sizeH;
	SDL_SetColorKey(surf, true, 0);
	return surf;
}

SDL_Rect* getRect(int sizeW, int sizeH, int posX=0, int posY=0){
	// giving back a rect with given size and position
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
	// setting up tile name and id
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

void createChunks(){
	// setting up positions needed for creating chunks
	float maxleft;
	float maxright;
	float maxtop;
	float maxbot;
	int chunksNeeded;
	int chunksHorizontal;
	int chunksVertical;
	int chunkCnt = 0;

	// if loading level while chunks are alrdy created reset position
	for (gameObject* obj : chunks){
		obj->Rendered = true;
		obj->move(0, 0);
	}
	chunks.clear();

	// looping all objects and getting all coordinates
	for (gameObject* obj : allObjects){
		if (!maxleft && !maxright && !maxtop && !maxbot){
			maxleft = obj->position.baseX;
			maxright = obj->position.baseX;
			maxtop = obj->position.baseY;
			maxbot = obj->position.baseY;
			continue;
		}
		if (obj->position.x < maxleft) maxleft = obj->position.baseX;
		if (obj->position.x > maxright) maxright = obj->position.baseX;
		if (obj->position.y < maxtop) maxtop = obj->position.baseY;
		if (obj->position.y > maxbot) maxbot = obj->position.baseY;
	}

	// calculating number of chunks needed
	chunksHorizontal = std::ceil((maxright - maxleft) / (chunkSize * 16));
	chunksVertical = std::ceil((maxbot - maxtop) / (chunkSize * 16));
	chunksNeeded = chunksHorizontal * chunksVertical;

	// setting value "isInChunk" of all objects to false in case reloading
	for (gameObject* obj : allObjects) obj->isInChunk = false;

	int xpos;
	int ypos;
	chunk* newChunk;

	// creating chunks and include gameObjects and add chunk to chunks if it isnt empty
	for (int y=0; y < chunksVertical; y++){
		for (int x=0; x < chunksHorizontal; x++){
			xpos = maxleft + (chunkSize * 16 * x);
			ypos = maxtop + (chunkSize * 16 * y);
			newChunk = new chunk(xpos, ypos, chunkSize * 16);
			for (gameObject* obj : allObjects){
				obj->hitbox.x = obj->position.baseX;
				obj->hitbox.y = obj->position.baseY;
				if (SDL_HasIntersection(&newChunk->hitbox, &obj->hitbox) && !obj->isInChunk){
					obj->isInChunk = true;
					newChunk->onHit(obj);
				}
			}
			if (newChunk->objCnt > 0){
				pushBackChunks(newChunk);
				chunkCnt++;
			}
		}
	}
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
	// setup surfaces by loading in all images
	tileset = IMG_Load("res/Textures/basictiles.png");
	characters = IMG_Load("res/Textures/characters.png");
	dead = IMG_Load("res/Textures/dead.png");
	things = IMG_Load("res/Textures/things.png");

	// setting up tiles
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

void objManager::loadLevel(std::string filename){
	using namespace std;
	clearGameObjects();

	gameObject tmpObj;

	// open file
	ifstream fileObj;
	fileObj.open(filename, ios::binary);
	if (fileObj.is_open()){
		char emptyStr[20];
		strcpy(emptyStr, "empty");

		// loading in every single gameObject saved to given file
		// later changed so sprites, entities, player and mobs get own file that you load from
		while (fileObj.good() && !fileObj.eof()){
			string str = "sprite";
			strcpy(tmpObj.saveStruct.type, emptyStr);
			fileObj.read((char*)&tmpObj.saveStruct, sizeof(tmpObj.saveStruct));
			if (tmpObj.saveStruct.type == str){
				int32_t posX = tmpObj.saveStruct.positionX;
				int32_t posY = tmpObj.saveStruct.positionY;
				int32_t width = tmpObj.saveStruct.sizeW;
				int32_t height = tmpObj.saveStruct.sizeH;
				int32_t layer = tmpObj.saveStruct.collisionLayer;
				int32_t id = tmpObj.saveStruct.texID;
				sprite* sp;
				sp = new sprite(posX, posY, width, height, layer, tiles[id]->tileTex, id);
				allObjects.push_back(sp);
				gameObjectCount++;
			}
			else{
				break;
			}
		}
	}
	SDL_Log("%d Objects loaded", gameObjectCount);
	fileObj.close();
}

void objManager::saveLevel(std::string filename){
	// saving all gameObjects to one file
	// later on saving every type of object to another file for simplicity
	using namespace std;
	int objectsSaved = 0;
	ofstream fileObj;
	fileObj.open(filename, ios::binary);
	if (fileObj.is_open()){
		for (gameObject* obj : allObjects){
			obj->save(&fileObj);
			objectsSaved++;
		}
	}
	SDL_Log("%d Objects saved", objectsSaved);
	fileObj.close();
}
