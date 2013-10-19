#pragma once
#include "flying.h"
class Spaceship :
	public Flying
{
public:
	Spaceship(void);
	~Spaceship(void);
	void draw(void);
	void update(void);
	void update(bool[]);
};

