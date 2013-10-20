#pragma once
#include "flying.h"
#include <list>
#include "blast.h"
class Spaceship :
	public Flying
{
private:
	// linkedlist of blasts which are still on the screen
	std::list<Blast*> blasts_list;
public:
	Spaceship(void);
	~Spaceship(void);
	void draw(void);
	void update(void);
	void update(bool[]);
	bool collisionWithAsteroid(float sx, float sy, float width, float height);
	bool asteroidCollisionWithBlast(float sx, float sy, float width, float height);
	bool isGone();
};

