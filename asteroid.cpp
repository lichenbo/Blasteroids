#include "asteroid.h"
#include "blasteroids.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

Asteroid::Asteroid(void)
{
	color = al_map_rgb(255,255,255);
	srand((unsigned int)time(NULL));
	twist = rand() % 360 * 3.14159 / 180;
	speed = rand() % 5 + 3;
	rot_velocity = rand() % 10 * 3.14159 / 180;
	sx = rand() % SCREEN_W;
	sy = rand() % SCREEN_H;
	scale = 1;
	heading = rand() % 360 * 3.14159 / 180;
	gone = false;
	if (SCREEN_H*sx > SCREEN_W*sy && sx*sy*4 < SCREEN_H*SCREEN_W) {
		sy = 0;
	} else if (SCREEN_H*sx > SCREEN_W*sy) {
		sx = SCREEN_W;
	} else if (sx*sy*4 < SCREEN_H*SCREEN_W) {
		sx = 0;
	} else {
		sy = SCREEN_H;
	}
	cout << "Asteroid created at " << sx << "," << sy << "; Heading: " << heading << ";" << endl;
}


Asteroid::~Asteroid(void)
{
}

void Asteroid::draw(void) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, twist);
	al_translate_transform(&transform, sx, sy);
	al_scale_transform(&transform,scale,scale);
	al_use_transform(&transform);

	al_init_primitives_addon();
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
	twist += rot_velocity;
	sx += cos(heading) * speed;
	sy += sin(heading) * speed;
	if (sx > SCREEN_W/scale) {
	   sx = 0;
	} else if (sx < 0) {
	   sx = SCREEN_W/scale;
	}
	if (sy > SCREEN_H/scale) {
	   sy = 0;
	} else if (sy < 0) {
	   sy = SCREEN_H/scale;
	}
}