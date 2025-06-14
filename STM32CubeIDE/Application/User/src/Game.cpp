#include "Game.hpp"
#include <cmsis_os.h>
Game game;

Game::Game() {
	count = 0;
	for (int i = 0; i < MAX_ENEMY; i++) {
		bosses[i].x = 10 + 20 * i;
		bosses[i].y = 48;
		bosses[i].status = ALIVE;
	}
	for (int i = 0; i < MAX_BEE; i++) {
		bees[i].x = 20 + 20 * i;
		bees[i].y = 92;
		bees[i].status = ALIVE;
	}
	for (int i = 0; i < MAX_BUTTERFLY; i++) {
		butterflys[i].x = 10 + 20 * i;
		butterflys[i].y = 70;
		butterflys[i].status = ALIVE;
	}
	score=0;
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
			if (bosses[i].direction == 'L') {
				bosses[i].moveL();
			} else {
				bosses[i].moveR();
			}
			if (bees[i].direction == 'L') {
				bees[i].moveL();
			} else {
				bees[i].moveR();
			}
			if (butterflys[i].direction == 'L') {
				butterflys[i].moveL();
			} else {
				butterflys[i].moveR();
			}
		}
	}

	//Kiem tra va cham giua dan va ke dich
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (bosses[i].status == DIE || bosses[i].status == DEAD)
			continue;
		for (int j = 0; j < MAX_BULLET; j++) {
			if (ship.bullets[j].status == INACTIVE)
				continue;
			else if (Entity::checkCollision(bosses[i], ship.bullets[j])) {
				ship.bullets[j].status = INACTIVE;
				bosses[i].status = DIE;
				score+= bosses[i].score;
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
				score+= bees[i].score;
			}
		}
	}

	for (int i = 0; i < MAX_BUTTERFLY; i++) {
		if (butterflys[i].status == DIE || butterflys[i].status == DEAD)
			continue;
		for (int j = 0; j < MAX_BULLET; j++) {
			if (ship.bullets[j].status == INACTIVE)
				continue;
			else if (Entity::checkCollision(butterflys[i], ship.bullets[j])) {
				ship.bullets[j].status = INACTIVE;
				butterflys[i].status = DIE;
				score+= butterflys[i].score;
			}
		}
	}
	//kiem tra va cham giua dan cua ke dich voi tau
	for (int i = 0; i < MAX_EBULLET; i++) {
		if (eBullets[i].status == INACTIVE)
			continue;
		else if (Entity::checkCollision(eBullets[i], ship)) {
//			if(ship.live>1){
//				ship.live--;
//				eBullets[i].status=INACTIVE;
//			}
			ship.status = DIE;
		}
	}
}

void GameThread(void *argument) {
	while (1) {
		game.update();
		game.ship.update();
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (game.bosses[i].status == ALIVE) {
				game.bosses[i].update();
				if (game.bosses[i].isFire) {
					game.bosses[i].isFire = false;
					for (int j = 0; j < MAX_EBULLET; j++) {
						if (game.eBullets[j].status == INACTIVE) {
							game.eBullets[j] = Bullet(game.bosses[i].x + 6,
									game.bosses[i].y + 8, 4);
							game.eBullets[j].status = SPAWN;
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < MAX_BEE; i++) {
			if (game.bees[i].status == ALIVE)
				game.bees[i].update();
			if (game.bees[i].isFire) {
				game.bees[i].isFire = false;
				for (int j = 0; j < MAX_EBULLET; j++) {
					if (game.eBullets[j].status == INACTIVE) {
						game.eBullets[j] = Bullet(game.bees[i].x + 6,
								game.bees[i].y + 8, 4);
						game.eBullets[j].status = SPAWN;
						break;
					}
				}
			}
		}
		for (int i = 0; i < MAX_BUTTERFLY; i++) {
			if (game.butterflys[i].status == ALIVE)
				game.butterflys[i].update();
			if (game.butterflys[i].isFire) {
				game.butterflys[i].isFire = false;
				for (int j = 0; j < MAX_EBULLET; j++) {
					if (game.eBullets[j].status == INACTIVE) {
						game.eBullets[j] = Bullet(game.butterflys[i].x + 6,
								game.butterflys[i].y + 8, 4);
						game.eBullets[j].status = SPAWN;
						break;
					}
				}
			}
		}
		for (int i = 0; i < MAX_EBULLET; i++) {
			if (game.eBullets[i].status == ACTIVE) {
				game.eBullets[i].update();
			}
		}
		osDelay(16);
	}
}

