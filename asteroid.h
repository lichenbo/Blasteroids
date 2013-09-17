#pragma once
#include "flying.h"
class Asteroid :
	public Flying
{
private:
	float twist;
	float rot_velocity;
	float scale;
public:
	Asteroid(void);
	~Asteroid(void);
	void draw(void);
	void adjust(void);
};

