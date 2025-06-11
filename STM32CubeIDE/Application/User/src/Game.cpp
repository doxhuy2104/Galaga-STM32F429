#include "Game.hpp"
#include <cmsis_os.h>
Game game;

Game::Game() {
	count = 0;
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemies[i].x = 10 + 20 * i;
		enemies[i].y = 48;
		enemies[i].status = ALIVE;
	}
	for (int i = 0; i < MAX_BEE; i++) {
		bees[i].x = 20 + 20 * i;
		bees[i].y = 70;
		bees[i].status = ALIVE;
	}
}
Game::~Game() {

}

void Game::update() {
	count++;
	if (count >= 10) {
		if (ship.isFire)
			ship.fire();
		count = 0;
	}
	if (count % 4 == 0) {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (game.enemies[i].direction == 'L') {
				game.enemies[i].moveL();
			} else {
				game.enemies[i].moveR();
			}
			if (game.bees[i].direction == 'L') {
							game.bees[i].moveL();
						} else {
							game.bees[i].moveR();
						}
		}
	}

	//Kiem tra va cham giua dan va ke dich
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemies[i].status == DIE || enemies[i].status == DEAD)
			continue;
		for (int j = 0; j < MAX_BULLET; j++) {
			if (ship.bullets[j].status == INACTIVE)
				continue;
			else if (Entity::checkCollision(enemies[i], ship.bullets[j])) {
				ship.bullets[j].status = INACTIVE;
				enemies[i].status = DIE;
			}
		}
	}
	for (int i = 0; i < MAX_BEE; i++) {
			if (bees[i].status == DIE || bees[i].status == DEAD)
				continue;
			for (int j = 0; j < MAX_BULLET; j++) {
				if (ship.bullets[j].status == INACTIVE)
					continue;
				else if (Entity::checkCollision(bees[i], ship.bullets[j])) {
					ship.bullets[j].status = INACTIVE;
					bees[i].status = DIE;
				}
			}
		}
}

void GameThread(void *argument) {
	while (1) {
		game.update();
		game.ship.update();
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (game.enemies[i].status == ALIVE)
				game.enemies[i].update();
		}
		for (int i = 0; i < MAX_BEE; i++) {
			if (game.bees[i].status == ALIVE)
				game.bees[i].update();
		}
		osDelay(16);
	}
}

