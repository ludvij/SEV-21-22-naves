#pragma once

#include "Game.h"
class Text
{
public:
	Text(std::string content, float x, float y, Game* game);
	void draw();
	std::string content; // texto
	int x;
	int y;
	int width;
	int height;
private:
	Game* game; // referencia al juego
};


