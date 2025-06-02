#include "Game.hpp"
#include <cmsis_os.h>
Game game;

Game::Game() {
count=0;
}
Game::~Game() {

}

void Game::update() {
	count++;

	    if (count >= 7) {
		if(galaga.isFire)
			galaga.fire();
		count = 0;
	}

}

void GameThread(void *argument) {
	while (1) {
		game.update();
		game.galaga.update();
		osDelay(16);
	}
}

