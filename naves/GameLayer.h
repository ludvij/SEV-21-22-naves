#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Collectable.h"

#include "Audio.h"

#include <list>
#include <vector>
#include <memory>


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	~GameLayer();

	virtual void init() override;
	virtual void processControls() override;
	virtual void update() override;
	virtual void draw() override;

	virtual void keysToControls(SDL_Event event);


private:
	int points;

	bool controlShoot = false;

	int controlMoveY = 0;
	int controlMoveX = 0;

	int newEnemyTime   = 0;
	int newPowerUpTime = 0;
	int newCoinTime    = 0;

	// punteros inteligentes para evitar memory leaks
	std::unique_ptr<Player>		player;
	std::unique_ptr<Background>	background;
	std::unique_ptr<Actor>		backgroundPoints;

	std::vector<std::unique_ptr<Actor>>		lives;

	std::list<std::unique_ptr<Enemy>>		enemies;
	std::list<std::unique_ptr<Projectile>>	projectiles;
	std::list<std::unique_ptr<Collectable>>	coins;
	std::list<std::unique_ptr<Collectable>> powerUps;


	std::unique_ptr<Audio> audioBackground;
	std::unique_ptr<Text>  textPoints;

	template <class T>
	void deleteActors(std::list<T>& actors);

	void updateCollisions();

	void deleteOutOfBounds();

	enum Movement : int {
		UP     = -1,
		DOWN   =  1,
		LEFT   = -1,
		RIGHT  =  1,
		STOP   =  0
	};
};

