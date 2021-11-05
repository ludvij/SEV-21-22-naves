#pragma once
#include "Actor.h"
class Projectile : public Actor
{
public:
	Projectile(float x, float y, int width, int height, Game* game);
	void update();
};

