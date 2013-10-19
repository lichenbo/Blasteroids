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
	float width;
	float height;
	ALLEGRO_COLOR color;
public:
	virtual void draw(void) = 0;
	virtual void update(void) = 0;
};

int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);