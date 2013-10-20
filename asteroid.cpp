#include "asteroid.h"
#include "blasteroids.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

Asteroid::Asteroid(int scale)
{
	color = al_map_rgb(255,255,255);
	srand((unsigned int)time(NULL));
	twist = DEGTORAD(rand() % 360);
	speed = rand() % 5 + 3;
	rot_velocity = DEGTORAD(rand() % 10);
	sx = rand() % SCREEN_W;
	sy = rand() % SCREEN_H;
	this->scale = scale;
	heading = DEGTORAD(rand() % 360);
	gone = false;
	width = 25;
	height = 25;
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
	if (!gone) {
		ALLEGRO_TRANSFORM transform;
		al_identity_transform(&transform);
		al_rotate_transform(&transform, twist);
		al_translate_transform(&transform, sx*scale, sy*scale);
		al_scale_transform(&transform,1/scale,1/scale);
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
}

void Asteroid::update(void) {
	if (!gone) {
		twist += rot_velocity;
		sx += cos(heading) * speed;
		sy += sin(heading) * speed;
		if (sx > SCREEN_W) {
		   sx = 0;
		} else if (sx < 0) {
		   sx = SCREEN_W;
		}
		if (sy > SCREEN_H) {
		   sy = 0;
		} else if (sy < 0) {
		   sy = SCREEN_H;
		}
	} else {
		
	
	}
}

/* True stands for it creating another two tiny asteroid , False otherwise */
bool Asteroid::collisionDetect(Spaceship* spaceship, list<Asteroid*>& list){
	bool collisionWithSpaceship = spaceship->collisionWithAsteroid(sx,sy,width,height);
	bool collisionWithBlast = spaceship->asteroidCollisionWithBlast(sx, sy, width, height);
	if (collisionWithSpaceship) {
		cout << "Collision with spaceship!" << endl;
		gone = true;
		return true;
	}
	if (collisionWithBlast) {
		cout << "Collision with Blast!" << endl;
		gone = true;
		if (scale == 1) {
			Asteroid* left = new Asteroid(2);
			Asteroid* right = new Asteroid(2);
			left->heading = heading - DEGTORAD(20);
			left->sx = sx/scale;
			left->sy = sy/scale;
			right->heading = heading + DEGTORAD(20);
			right->sx = sx/scale;
			right->sy = sy/scale;
			list.push_back(left);
			list.push_back(right);
		}
	}
	return false;
}

bool Asteroid::isGone() {
	return gone;
}