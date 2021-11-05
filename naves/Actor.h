#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height, Game* game);
	~Actor();

	virtual void draw();

	bool isOverlap(Actor* actor);
	bool isInRender();

	// position
	int x;
	int y;
	// velocity in x and y coordinates
	float vx = 0.0f;
	float vy = 0.0f;
	// texture size ingame
	int width;
	int height;
	// texture size in file
	int fileWidth;
	int fileHeight;

	SDL_Texture* texture;

	bool deleteMark = false;

protected:
	Game* game; // referencia al juego


};
