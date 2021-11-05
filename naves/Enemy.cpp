#include "Enemy.h"

// base class===================================================================================

Enemy::Enemy(std::string texFile, std::string animationFile, int width, int height, float x, float y, Game* game)
	: Actor(texFile, x, y, width, height, game) 
{
	vx = 1;

	aMoving.reset(new Animation(animationFile, width, height, 6, 3, game));
	animation = aMoving;
}

void Enemy::draw() 
{
	animation->draw(x, y);
	animation->update();
}

// sub classes==================================================================================

// gray sacuer===========================================================
GraySaucer::GraySaucer(float x, float y, Game* game)
	: Enemy("res/enemigo.png", "res/enemigo_movimiento.png", 36, 40, x, y, game)
{
	health = 3;
}

void GraySaucer::update()
{
	

	vx = -1.0f;
	x = x + (int)vx;
}
// red saucer============================================================
RedSaucer::RedSaucer(float x, float y, Game* game)
	: Enemy("res/enemigo2.png", "res/enemigo_movimiento2.png", 36, 40, x, y, game)
{
	health = 1;
}

void RedSaucer::update()
{
	vx = -3.0f;
	x = x + (int)vx;
}