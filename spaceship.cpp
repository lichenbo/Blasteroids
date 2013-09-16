#include "spaceship.h"


Spaceship::Spaceship(void)
{
}


Spaceship::~Spaceship(void)
{
}

void Spaceship::draw(void) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, DEGREES(this->heading));
	al_draw_line(-8, 9, 0, -11, this->color, 3.0f);
	al_draw_line(0, -11, 8, 9, this->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, this->color, 3.0f);
	al_draw_line(6, 4, 1, 4, this->color, 3.0f);

}