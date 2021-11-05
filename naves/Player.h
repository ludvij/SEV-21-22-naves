#pragma once
#include "Actor.h"
#include "Audio.h"
#include "Projectile.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);

	Projectile* shoot();
	void update();
	void upgradeProjectile();
	void moveX(float axis);
	void moveY(float axis);

	std::unique_ptr<Audio> audioShoot;

	int shotCadence = 30;
	int shotTime = 0;
	int projectileWidth = 18;
	int projectileHeight = 6;

	int baseHealth = 3;
	int health = baseHealth;

};

