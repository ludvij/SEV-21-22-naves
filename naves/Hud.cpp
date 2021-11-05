#include "Hud.h"

void Hud::draw() const
{
	for (const auto& a : actors) a->draw();
}

Hud::~Hud()
{
	actors.clear();
}

void Hud::addActor(Actor* actor)
{
	actors.emplace_back(actor);
}

void Hud::addText(Text* text)
{
	texts.emplace_back(text);
}

void Hud::update()
{
}
