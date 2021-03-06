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
	void draw(void) const;
	void update(void);
	void update(const bool[]);
	bool collisionWithAsteroid(float sx, float sy, float width, float height);
	bool asteroidCollisionWithBlast(float sx, float sy, float width, float height) const;
	bool isGone() const;
};

