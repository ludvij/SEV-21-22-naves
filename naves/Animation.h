#pragma once
#include "Game.h"


class Animation
{
public:
	Animation(std::string filename, float actorWidth, float actorHeight,
		int updateFrecuence, int totalFrames, Game* game);
	~Animation();
	bool update();
	void draw(float x, float y);
	int actorWidth; // Actor Width
	int actorHeight; // Actor height
	int fileWidth; // Sprite Sheet width
	int fileHeight; // Sprite Sheet height
	int currentFrame;
	int totalFrames;

private:
	Game* game;
	// Auxiliares
	SDL_Texture* texture; // imagen
	SDL_Rect source; // Parte de la imagen que se recorta del fichero
	float frameWidth; // Ancho de un fotograma
	float frameHeigt; // Alto de un fotograma
	int updateFrecuence = 0;
	int updateTime = 0;
};
