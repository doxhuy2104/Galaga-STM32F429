#ifndef GAME_HPP
#define GAME_HPP

#include "Galaga.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include <cmsis_os.h>
class Game {
public:
	Game();
	~Game();
	void update();
	Galaga galaga;
private:
	int count;
};
extern Game game;
extern void GameThread(void *argument);
#endif
