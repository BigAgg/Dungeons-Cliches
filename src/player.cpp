#include "player.h"

player::player(SDL_Texture* t, int chosenCharacter){
	// setting up position
	position.x = 0;
	position.y = 0;

	// setting up dstrect for rendering at position
	dstrect.w = 16;
	dstrect.h = 16;
	dstrect.x = 480;
	dstrect.y = 270;

	// setting the hitbox size
	hitbox.w = 10;
	hitbox.h = 16;

	// setting srcrect for rendering the right image
	srcrect.h = 16;
	srcrect.w = 16;
	srcrect.x = chosenCharacter * 48;
	srcrect.y = 0;

	// saving pointer to the texture that should be used for rendering
	texture = t;

	// getting the chosen charecter for rendering
	this->chosenCharacter = chosenCharacter * 48;

	// setting the timer for player activities to 0
	timer = 0;
};

player::~player(){

};

void player::onTick(Uint32 delta){

}

void player::update(Uint32 delta){
	timer += delta;
	// check if player was moving this update
	if (velocity.x != 0 || velocity.y != 0){
		velocity.normalize();							// normalizing the vector2 movement
		float tmpfloat = delta / 1000.0;				// for calculating the position
		position.x += velocity.x * speed * tmpfloat;	// setting up position
		position.y += velocity.y * speed * tmpfloat;

		// getting the current rotation for rendering the right image
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

		// check if enought time has gone to take next frame of animation based on delta
		if (timer > 150){
			timer = 0;
			frame++;
			if (frame >= 3){
				frame = 0;
			}
		}
	}
	else{
		frame = 1;	// first frame if player is not moving
	}
	// frame out of texture
	srcrect.x = chosenCharacter + frame * 16;
	srcrect.y = rotation * 16;
}

void player::move(float x, float y){

}