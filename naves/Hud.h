#pragma once

#include "Actor.h"
#include "Text.h"

#include <vector>
#include <memory>

class Hud
{
public:
	void draw() const;
	~Hud();

	void addActor(Actor* actor);
	void addText(Text* text);

	void update();

private:
	std::vector<std::unique_ptr<Actor>> actors;
	std::vector<std::unique_ptr<Text>>  texts;
};

