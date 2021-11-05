#include "Projectile.h"

Projectile::Projectile(float x, float y, int width, int height, Game* game) :
	Actor("res/disparo_jugador.png", x, y, width, height, game) {
	vx = 9;
}

void Projectile::update() {
	x = x + vx;
}