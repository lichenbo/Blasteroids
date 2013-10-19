#pragma once
#include "flying.h"
#include "spaceship.h"
#include "blast.h"
#include <list>

using namespace std;

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
	void update(void);
	void collisionDetect(Spaceship*);
};

