#pragma once

// C++ things
#include <iostream>
#include <string>
#include <map>

// Todas las librerias de SDL y otras utilidades
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Layer.h"


// Valores generales
#define WIDTH 480
#define HEIGHT 320

class Layer;

class Game
{
public:
	Game();
	~Game();
	void loop();

	void scale();
	bool scaledToMax = false;
	float scaleLower = 1;

	SDL_Texture* getTexture(std::string filename);
	SDL_Texture* modTexture(std::string filename, std::string name, uint32_t r, uint32_t g, uint32_t b);



	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador

	TTF_Font* font;
	bool loopActive; // Juego activo

private:
	std::map<std::string, SDL_Texture*> mapTextures;
	Layer* gameLayer;
};

