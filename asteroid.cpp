#include "asteroid.h"


Asteroid::Asteroid(void)
{
	color = al_map_rgb(255,255,255);
	heading = 0;
	sx = sy = 100;
}


Asteroid::~Asteroid(void)
{
}

void Asteroid::draw(void) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, heading);
	al_translate_transform(&transform, sx, sy);
	al_use_transform(&transform);

	al_draw_line(-20, 20, -25, 5, color, 2.0f);
	al_draw_line(-25, 5, -25, -10, color, 2.0f);
	al_draw_line(-25, -10, -5, -10, color, 2.0f);
	al_draw_line(-5, -10, -10, -20, color, 2.0f);
	al_draw_line(-10, -20, 5, -20, color, 2.0f);
	al_draw_line(5, -20, 20, -10, color, 2.0f);
	al_draw_line(20, -10, 20, -5, color, 2.0f);
	al_draw_line(20, -5, 0, 0, color, 2.0f);
	al_draw_line(0, 0, 20, 10, color, 2.0f);
	al_draw_line(20, 10, 10, 20, color, 2.0f);
	al_draw_line(10, 20, 0, 15, color, 2.0f);
	al_draw_line(0, 15, -20, 20, color, 2.0f);
}

void Asteroid::update(void) {

}