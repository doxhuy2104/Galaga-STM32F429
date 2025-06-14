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
private:
	int count;
};
extern Game game;
extern void GameThread(void *argument);
#endif
