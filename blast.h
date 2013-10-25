#pragma once
#include "flying.h"
class Blast :
	public Flying
{
private:
	bool pointInAsteroid(float x, float y, float assx, float assy, float width, float height);
public:
	Blast(void);
	Blast(float,float,float);
	~Blast(void);
	void draw(void) const;
	void update(void);
	bool collisionWithAsteroid(float,float,float,float);
	bool isGone();
};

