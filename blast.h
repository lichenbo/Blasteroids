#pragma once
#include "flying.h"
class Blast :
	public Flying
{
public:
	Blast(void);
	Blast(float,float,float);
	~Blast(void);
	void draw(void);
	void update(void);
	bool collisionWithAsteroid(float,float,float,float);
	bool isGone();
};

