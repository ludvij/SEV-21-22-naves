#include "GameLayer.h"
#include <random>

#include "Utility.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) 
{
	//llama al constructor del padre : Layer(renderer)
	init();
}
GameLayer::~GameLayer()
{
	enemies.clear();
	projectiles.clear();
}
void GameLayer::init() 
{
	audioBackground.reset(new Audio("res/musica_ambiente.mp3", true));
	audioBackground->play();

	points = 0;
	textPoints.reset(new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game));

	textPoints->content = std::to_string(points);

	player.reset(new Player(50, 50, game));

	background.reset(new Background("res/fondo.png", (WIDTH * 0.5f), (HEIGHT * 0.5f), game));

	backgroundPoints.reset(new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game));

	lives.clear();
	coins.clear();
	// por algún motivo si la variable de control del loop no es uint64_t o unsigned __int64 va a dar
	// el aviso C26451 
	for (uint64_t i = 0; i < player->baseHealth; i++)
	{
		lives.emplace_back(new Actor("res/corazon.png", WIDTH * 0.05 + i * 24, HEIGHT * 0.05, 24, 24, game));
	}
	


	enemies.clear(); 
	enemies.emplace_back(new RedSaucer(300, 50, game));
	enemies.emplace_back(new GraySaucer(300, 200, game));
	
	projectiles.clear();

	points = 0;
	newEnemyTime   = 110;
	newCoinTime    = 220;
	newPowerUpTime = 330;
}
void GameLayer::processControls() 
{
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		keysToControls(event);
		if (event.type == SDL_QUIT) game->loopActive = false;
	}
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* p = player->shoot();
		if (p != nullptr) projectiles.emplace_back(p);
	}
	// Eje X
	if      (controlMoveX == Movement::RIGHT)player->moveX(Movement::RIGHT);
	else if (controlMoveX == Movement::LEFT) player->moveX(Movement::LEFT);
	else if (controlMoveX == Movement::STOP) player->moveX(Movement::STOP);
	// Eje Y
	if      (controlMoveY == Movement::DOWN) player->moveY(Movement::DOWN);
	else if (controlMoveY == Movement::UP)   player->moveY(Movement::UP);
	else if (controlMoveY == Movement::STOP) player->moveY(Movement::STOP);
	
}

void GameLayer::update() 
{
	std::cout << "update GameLayer" << std::endl;

	player->update();
	for (auto const& enemy : enemies) enemy->update();
	for (auto const& projectile : projectiles) projectile->update();
	
	newEnemyTime--;
	if (newEnemyTime <= 0)
	{
		int rX = rndNum(500, 600);
		int rY = rndNum(60, 300);
		enemies.emplace_back(new GraySaucer(rX, rY, game));

		rX = rndNum(500, 600);
		rY = rndNum(60, 300);
		enemies.emplace_back(new RedSaucer(rX, rY, game));
		// bad dificulty formula
		newEnemyTime = 110;
	}
	newCoinTime--;
	if (newCoinTime <= 0)
	{

		int rX = rndNum(WIDTH * 0.05, WIDTH * 0.95);
		int rY = rndNum(HEIGHT * 0.05, HEIGHT * 0.95);
		coins.emplace_back(new Collectable("res/moneda.png", rX, rY, 35, 35, game));
		newCoinTime = 220;
	}
	newPowerUpTime--;
	if (newPowerUpTime <= 0)
	{
		int rX = rndNum(WIDTH * 0.05, WIDTH * 0.95);
		int rY = rndNum(HEIGHT * 0.05, HEIGHT * 0.95);

		auto powerUp = new Collectable("res/icono_recolectable.png", rX, rY, 35, 35, game);
		powerUp->setAnimation("res/recolectable.png", 3, 8);
		powerUps.emplace_back(powerUp);
		newPowerUpTime = 330;
	}

	for (const auto& pw : powerUps) pw->update();
	for (const auto& c : coins) c->update();

	// Colisiones
	updateCollisions();
	// delete out of bounds
	deleteOutOfBounds();
}

void GameLayer::draw() 
{
	background->draw();
	for (const auto& coin       : coins)       coin->draw();
	for (const auto& powerUp    : powerUps)    powerUp->draw();
	for (const auto& enemy      : enemies)     enemy->draw();
	for (const auto& projectile : projectiles) projectile->draw();
	player->draw();
	textPoints->draw();
	backgroundPoints->draw();
	for (int i = 0; i < player->baseHealth; i++)lives[i]->draw();
	
	SDL_RenderPresent(game->renderer); // Renderiza
}
void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_d: // derecha
			controlMoveX = Movement::RIGHT;
			break;
		case SDLK_a: // izquierda
			controlMoveX = Movement::LEFT;
			break;
		case SDLK_w: // arriba
			controlMoveY = Movement::UP;
			break;
		case SDLK_s: // abajo
			controlMoveY = Movement::DOWN;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_ESCAPE: game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		}
	}
	if (event.type == SDL_KEYUP) 
	{
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == Movement::RIGHT) 
				controlMoveX = Movement::STOP;
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == Movement::LEFT) 
				controlMoveX = Movement::STOP;
			break;
		case SDLK_w: // arriba
			if (controlMoveY == Movement::UP) 
				controlMoveY = Movement::STOP;
			break;
		case SDLK_s: // abajo
			if (controlMoveY == Movement::DOWN)
				controlMoveY = Movement::STOP;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}


void GameLayer::updateCollisions()
{

	for (auto const& coin : coins) {
		if (player->isOverlap(coin.get())) {
			if (player->health < player->baseHealth) {
				lives[player->health]->texture = game->getTexture("res/corazon.png");
				player->health++;
			}
			coin->deleteMark = true;
		}
	}
	for (const auto& powerUp : powerUps) {
		if (player->isOverlap(powerUp.get())) {
			powerUp->deleteMark = true;
			player->upgradeProjectile();
		}
	}
	
	for (auto const& enemy : enemies)
	{
		if (player->isOverlap(enemy.get()))
		{
			if (player->health > 1) {
				player->health--;
				lives[player->health]->texture = game->modTexture("res/corazon.png", "corazon_vacio", 0x00, 0x00, 0x00);
				enemy->deleteMark = true;
			}
			else {
				init();
				return; // Cortar el for
			}
		}
		// Colisiones , Enemy - Projectile 
		for (auto const& projectile : projectiles)
		{
			if (enemy->isOverlap(projectile.get()))
			{
				projectile->deleteMark = true;
				if (enemy->health > 1) enemy->health--;
				else {
					enemy->deleteMark = true;
					points++;
					textPoints->content = std::to_string(points);
				}
			}
		}
		
	}

	deleteActors(projectiles);
	deleteActors(enemies);
	deleteActors(powerUps);
	deleteActors(coins);
}

void GameLayer::deleteOutOfBounds()
{
	for (auto const& e : enemies) {
		if (e->x <= 0) e->deleteMark = true;
	}

	for (auto const& projectile : projectiles)
	{
		if (!projectile->isInRender()) {
			projectile->deleteMark = true;
		}
	}

	deleteActors(enemies);
	deleteActors(projectiles);
}

template <class T>
void GameLayer::deleteActors(std::list<T>& actors)
{
	auto it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->deleteMark == true) 
			actors.erase(it++);
		else 
			it++;
	}
}