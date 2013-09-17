#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
class Flying
{
protected:
	float sx;
	float sy;
	float heading;
	float speed;
	bool gone;
	ALLEGRO_COLOR color;
public:
	virtual void draw(void) = 0;
	virtual void adjust(void) = 0;
};

