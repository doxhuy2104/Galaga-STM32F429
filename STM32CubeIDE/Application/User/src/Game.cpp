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

	spawnQueueSize = 0;
	spawnDelayCounter = 0;
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
	handleSpawnQueue();
}

void Game::queueSpawn(SpawnRequest::Type type, int x, int y) {
	if (spawnQueueSize < MAX_SPAWN_QUEUE) {
		spawnQueue[spawnQueueSize++] = {type, x, y};
	}
}

void Game::handleSpawnQueue() {
	if (spawnQueueSize == 0)
		return;

	if (spawnDelayCounter > 0) {
		spawnDelayCounter--;
		return;
	}

	SpawnRequest req = spawnQueue[0];

	// Dịch hàng đợi lên sau khi xử lý
	for (int i = 1; i < spawnQueueSize; i++) {
		spawnQueue[i - 1] = spawnQueue[i];
	}
	spawnQueueSize--;

	// Gọi spawn dựa vào loại
	if (req.type == SpawnRequest::BOSS) {
		for (int i = 0; i < MAX_BOSS; i++) {
			if (bosses[i].status == DEAD) {
				bosses[i].spawn(req.x, req.y);
				break;
			}
		}
	} else if (req.type == SpawnRequest::BEE) {
		for (int i = 0; i < MAX_BEE; i++) {
			if (bees[i].status == DEAD) {
				bees[i].spawn(req.x, req.y);
				break;
			}
		}
	} else if (req.type == SpawnRequest::BUTTERFLY) {
		for (int i = 0; i < MAX_BUTTERFLY; i++) {
			if (butterflys[i].status == DEAD) {
				butterflys[i].spawn(req.x, req.y);
				break;
			}
		}
	}

	spawnDelayCounter = 12;
}

int getXPosition(int index, int totalEnemies) {
    // Tính tổng chiều rộng tất cả quái (bao gồm khoảng cách)
    int maxSpacing = (SCREEN_WIDTH - ENEMY_WIDTH) / (totalEnemies > 1 ? totalEnemies - 1 : 1);

    // Đảm bảo spacing không quá nhỏ (tối thiểu 4px)
    int spacing = maxSpacing > ENEMY_WIDTH ? maxSpacing : ENEMY_WIDTH + 4;

    int totalWidth = (totalEnemies - 1) * spacing + ENEMY_WIDTH;
    int startX = (SCREEN_WIDTH - totalWidth) / 2;

    return startX + index * spacing;
}

void spawnStage(int stage) {
    int bossCount = stage;
    int beeCount = stage * 2;
    int butterflyCount = stage * 3;

    if (bossCount > MAX_BOSS) bossCount = MAX_BOSS;
    if (beeCount > MAX_BEE) beeCount = MAX_BEE;
    if (butterflyCount > MAX_BUTTERFLY) butterflyCount = MAX_BUTTERFLY;

    for (int i = 0; i < bossCount; i++) {
        int x = getXPosition(i, bossCount);
        game.bosses[i].spawn(x, 20);
    }

    for (int i = 0; i < beeCount; i++) {
        int x = getXPosition(i, beeCount);
        game.bees[i].spawn(x, 60);
    }

    for (int i = 0; i < butterflyCount; i++) {
        int x = getXPosition(i, butterflyCount);
        game.butterflys[i].spawn(x, 100);
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

