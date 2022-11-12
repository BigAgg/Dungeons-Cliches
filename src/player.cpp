#include "player.h"

player::player(SDL_Texture* t, int chosenCharacter){
	position.x = 0;
	position.y = 0;
	dstrect.w = 16;
	dstrect.h = 16;
	dstrect.x = 480;
	dstrect.y = 270;
	hitbox.w = 10;
	hitbox.h = 16;
	srcrect.h = 16;
	srcrect.w = 16;
	srcrect.x = chosenCharacter * 48;
	srcrect.y = 0;
	texture = t;
	this->chosenCharacter = chosenCharacter * 48;
	timer = 0;
};

player::~player(){

};

void player::onTick(Uint32 delta){

}

void player::update(Uint32 delta){
	timer += delta;
	if (velocity.x != 0 || velocity.y != 0){
		velocity.normalize();
		float tmpfloat = delta / 1000.0;
		position.x += velocity.x * speed * tmpfloat;
		position.y += velocity.y * speed * tmpfloat;
		if (velocity.y > 0){
			rotation = 3;
		}
		else if (velocity.y < 0){
			rotation = 0;
		}
		else if (velocity.x > 0){
			rotation = 1;
		}
		else if (velocity.x < 0){
			rotation = 2;
		}
		if (timer > 150){
			timer = 0;
			frame++;
			if (frame >= 3){
				frame = 0;
			}
		}
	}
	else{
		frame = 1;
	}
	srcrect.x = chosenCharacter + frame * 16;
	srcrect.y = rotation * 16;
}

void player::move(float x, float y){

}