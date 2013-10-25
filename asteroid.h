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
	Asteroid(int scale = 1);
	~Asteroid(void);
	void draw(void);
	void update(void);
	bool collisionDetect(Spaceship* spaceship, list<Asteroid*>& list);
	bool isGone() const;
};

