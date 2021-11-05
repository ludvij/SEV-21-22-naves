#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) 
{
	audioShoot.reset(new Audio("res/efecto_disparo.wav", false));
}

Projectile* Player::shoot()
{
	if (shotTime == 0)
	{
		audioShoot->play();
		shotTime = shotCadence;
		return new Projectile(x, y, projectileWidth, projectileHeight, game);
	}
	return nullptr;
}

void Player::update() {
	if (shotTime > 0) {
		shotTime--;
	}
	x = x + (int)vx;
	y = y + vy;
}

void Player::upgradeProjectile()
{
	projectileWidth += 1;
	projectileHeight += 1;
	if (shotCadence > 1)
		shotCadence -= 1;	
}

void Player::moveX(float axis) {
	vx = axis * 3;
}
void Player::moveY(float axis) {
	vy = axis * 3;
}