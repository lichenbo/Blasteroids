#include "blast.h"
#include "blasteroids.h"
#include <cmath>
#include <iostream>

Blast::Blast(void)
{
}

Blast::Blast(float sx, float sy, float heading) {
	this->sx = sx;
	this->sy = sy;
	this->heading = heading;
	this->speed = 20;
	this->color = al_map_rgb(0, 255, 0);
	this->gone = false;
	this->width = 0;
	this->height = 0;
	std::cout << "Blast created" << std::endl;
}

Blast::~Blast(void)
{
}

void Blast::draw(void) const{
	if (!gone) {
		ALLEGRO_TRANSFORM transform;
		al_identity_transform(&transform);
		al_rotate_transform(&transform, DEGTORAD(90)-heading);
		al_translate_transform(&transform, sx, sy);
		al_use_transform(&transform);

		al_init_primitives_addon();
		al_draw_line(0, -21, 0, -11, color, 3.0f);
	}
}

void Blast::update(void) {
	if (!gone) {
		sx = sx + cos(heading)*speed;
		sy = sy - sin(heading)*speed;
	}
	if (sx < 0 || sx > SCREEN_W || sy < 0 || sy > SCREEN_H) {
		gone = true;
	}
}

bool Blast::collisionWithAsteroid(float assx, float assy, float aswidth, float asheight) {
	// get line segment info
	float x1 = sx + cos(heading)*21;
	float y1 = sy - sin(heading)*21;
	float x2 = sx + cos(heading)*11;
	float y2 = sy - sin(heading)*11;
	if (pointInAsteroid(x1,y1,assx,assy,aswidth,asheight) || pointInAsteroid(x2,y2,assx,assy,aswidth,asheight)) {
		gone = true;
		std::cout << "Bam" << std::endl;
		return true;
	}
	return false;
}

bool Blast::isGone() const{
	return gone;
}

bool Blast::pointInAsteroid(float x, float y, float assx, float assy, float aswidth, float asheight) {
	if (x > assx-aswidth/2 && x < assx+aswidth/2 && y > assy-asheight/2 && y < assy+asheight/2) {
		return true;
	}
	return false;
}