#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Bee.hpp"
#include "Butterfly.hpp"
#include "Boss.hpp"

#include "Bullet.hpp"
#include "Entity.hpp"
#include <cmsis_os.h>
#include <Ship.hpp>

struct SpawnRequest {
    enum Type { BOSS, BEE, BUTTERFLY } type;
    int x, y;
};
#define MAX_SPAWN_QUEUE 32
#define SCREEN_WIDTH 240
#define ENEMY_WIDTH 16
class Game {
public:
	Game();
	~Game();
	void update();
	Ship ship;
	Boss bosses[MAX_BOSS];
	Bee bees[MAX_BEE];
	Butterfly butterflys[MAX_BUTTERFLY];
	Bullet eBullets[MAX_EBULLET];
	uint32_t score;
	uint32_t stage;
	void queueSpawn(SpawnRequest::Type type, int x, int y);
	void handleSpawnQueue();
private:
	int count;
	SpawnRequest spawnQueue[MAX_SPAWN_QUEUE];
	int spawnQueueSize = 0;
	int spawnDelayCounter = 0;
};
extern Game game;
extern void spawnStage(int stage);
extern void GameThread(void *argument);
#endif
