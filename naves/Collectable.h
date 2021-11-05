#pragma once

#include "Actor.h"
#include "Animation.h"

class Collectable : public Actor
{
public:
	Collectable(std::string texFile, int x, int y, int width, int height, Game* game);

	virtual void draw() override;

	void setAnimation(std::string filename, int updatefreq, int frames);

	void update();

private:
	std::unique_ptr<Animation> idleAnimation = nullptr;
	bool animated = false;
};

