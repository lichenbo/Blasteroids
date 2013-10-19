#include "spaceship.h"
#include "blasteroids.h"
#include <cmath>
#include <list>

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
	// linkedlist of blasts which are still on the screen
	std::list<Blast*> blasts_list;

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
	
	std::list<Blast*>::iterator itBlast;
	for (itBlast = blasts_list.begin(); itBlast != blasts_list.end(); itBlast++) {
		(*itBlast)->draw();
	} 
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
		float time = al_current_time();
		// static to avoid assignment every time
		static float old_time = 0;
		if (time - old_time > 0.1) {
			Blast* newBlast = new Blast(sx, sy, heading);
			blasts_list.push_back(newBlast);
			old_time = time;
		}

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

	std::list<Blast*>::iterator itBlast;
	for (itBlast = blasts_list.begin(); itBlast != blasts_list.end();) {
		(*itBlast)->update();

		if ((*itBlast)->isGone()) {
			blasts_list.erase(itBlast++);
		} else {
			itBlast++;
		}
	} 
}

bool Spaceship::collisionWithAsteroid(float assx, float assy, float aswidth, float asheight) {
	return (bounding_box_collision(sx - width/2, sy - height/2, width, height, assx - aswidth/2, assy - asheight/2, aswidth, asheight));
}

bool Spaceship::asteroidCollisionWithBlast(float assx, float assy, float aswidth, float asheight) {
	std::list<Blast*>::iterator itBlast;
	for (itBlast = blasts_list.begin(); itBlast != blasts_list.end(); itBlast++) {
		if ((*itBlast)->collisionWithAsteroid(assx, assy, aswidth, asheight)) {
			return true;
		}
	} 
	return false;
}