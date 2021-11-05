#include "Collectable.h"

Collectable::Collectable(std::string texFile, int x, int y, int width, int height, Game* game)
	: Actor(texFile, x, y, width, height, game)
{
}

void Collectable::draw() 
{
	if (animated) 
		idleAnimation->draw(x, y);
	else
		Actor::draw();
}


void Collectable::setAnimation(std::string filename, int updatefreq, int frames)
{
	idleAnimation.reset(new Animation(filename, width, height, updatefreq, frames, game));
	animated = true;
}

void Collectable::update()
{
	if (animated) idleAnimation->update();
}
