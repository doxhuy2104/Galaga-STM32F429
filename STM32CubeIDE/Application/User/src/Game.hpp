#ifndef GAME_HPP
#define GAME_HPP

#include "Galaga.hpp"
#include "Enemy.hpp"

class Game{
public:
	Game();
		~Game();
		void update();
		Galaga galaga;
};
extern Game game;
extern void GameThread(void* argument);
#endif
