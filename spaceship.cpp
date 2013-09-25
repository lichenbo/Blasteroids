#include "spaceship.h"
#include "blasteroids.h"

Spaceship::Spaceship(void)
{
	sx = SCREEN_W / 2;
	sy = SCREEN_H / 2;
	color = al_map_rgb(0,255,0);
	heading = 0;
	speed = 10;
	gone = false;

}


Spaceship::~Spaceship(void)
{
}

void Spaceship::draw(void) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, heading * 3.14159 / 180);		// Convert degree to radius.
	al_translate_transform(&transform, sx, sy);
	al_use_transform(&transform);

	al_draw_line(-8, 9, 0, -11, this->color, 3.0f);
	al_draw_line(0, -11, 8, 9, this->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, this->color, 3.0f);
	al_draw_line(6, 4, 1, 4, this->color, 3.0f);

}

void Spaceship::update(void) {

}