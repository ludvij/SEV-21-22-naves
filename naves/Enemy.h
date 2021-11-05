#pragma once
#include "Actor.h"
#include "Animation.h"


class Enemy : public Actor
{
public:
	Enemy(std::string texFile, std::string animationFile, int width, int height, float x, float y, Game* game);

	virtual void update() = 0;

	virtual void draw() override;

	int health = 0;

protected:
	std::shared_ptr<Animation> aMoving;
	std::shared_ptr<Animation> animation;
};


class GraySaucer : public Enemy 
{
public:
	GraySaucer(float x, float y, Game* game);
	virtual void update() override;

};

class RedSaucer : public Enemy
{
public:
	RedSaucer(float x, float y, Game* game);
	virtual void update() override;

};