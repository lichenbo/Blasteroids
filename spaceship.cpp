#include "spaceship.h"
#include "blasteroids.h"
#include <cmath>

Spaceship::Spaceship(void)
{
	sx = SCREEN_W / 2;
	sy = SCREEN_H / 2;
	color = al_map_rgb(0,255,0);
	// initial heading is right up to the sky
	heading = DEGTORAD(90);
	speed = 10;
	gone = false;
	width = 8;
	height = 20;

}


Spaceship::~Spaceship(void)
{
}

void Spaceship::draw(void) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	// adjust the heading match the drawing
	al_rotate_transform(&transform, DEGTORAD(90)-heading);
	al_translate_transform(&transform, sx, sy);
	al_use_transform(&transform);

	al_init_primitives_addon();
	al_draw_line(-8, 9, 0, -11, this->color, 3.0f);
	al_draw_line(0, -11, 8, 9, this->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, this->color, 3.0f);
	al_draw_line(6, 4, 1, 4, this->color, 3.0f);

}

void Spaceship::update(void) {
	// nothing changed
}

void Spaceship::update(bool key[]) {
	

	// update with key stroke
	if (key[KEY_UP]) {
		sx = sx + cos(heading);
		sy = sy - sin(heading);
	}
	if (key[KEY_DOWN]) {
		sx = sx - cos(heading);
		sy = sy + sin(heading);
	}
	if (key[KEY_LEFT]) {
		heading += DEGTORAD(5);
	}
	if (key[KEY_RIGHT]) {
		heading -= DEGTORAD(5);
	}
	if (key[KEY_SPACE]) {
	
	}

	// boundary for spaceship
	if (sx < 0) {
		sx = 0;
	} else if (sx > SCREEN_W) {
		sx = SCREEN_W;
	}
	if (sy < 0) {
		sy = 0;
	} else if (sy > SCREEN_H) {
		sy = SCREEN_H;
	}
	assert(sx >= 0 && sx <= SCREEN_W);
	assert(sy >= 0 && sy <= SCREEN_H);
}

bool Spaceship::collisionWithAsteroid(float assx, float assy, float aswidth, float asheight) {
	return (bounding_box_collision(sx - width/2, sy - height/2, width, height, assx - aswidth/2, assy - asheight/2, aswidth, asheight));
}