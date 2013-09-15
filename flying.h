#pragma once
#include <allegro5\allegro.h>

class Flying
{
private:
	float sx;
	float sy;
	float heading;
	float speed;
	bool gone;
	ALLEGRO_COLOR color;
public:
	virtual void draw(void) = 0;
};

