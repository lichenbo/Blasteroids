#include "asteroid.h"


Asteroid::Asteroid(void)
{
}


Asteroid::~Asteroid(void)
{
}

void Asteroid::draw(void) {
	al_draw_line(-20, 20, -25, 5, this->color, 2.0f);
	al_draw_line(-25, 5, -25, -10, this->color, 2.0f);
	al_draw_line(-25, -10, -5, -10, this->color, 2.0f);
	al_draw_line(-5, -10, -10, -20, this->color, 2.0f);
	al_draw_line(-10, -20, 5, -20, this->color, 2.0f);
	al_draw_line(5, -20, 20, -10, this->color, 2.0f);
	al_draw_line(20, -10, 20, -5, this->color, 2.0f);
	al_draw_line(20, -5, 0, 0, this->color, 2.0f);
	al_draw_line(0, 0, 20, 10, this->color, 2.0f);
	al_draw_line(20, 10, 10, 20, this->color, 2.0f);
	al_draw_line(10, 20, 0, 15, this->color, 2.0f);
	al_draw_line(0, 15, -20, 20, this->color, 2.0f);
}

void Asteroid::adjust(void) {

}