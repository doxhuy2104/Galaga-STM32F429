
#ifndef SHIP_HPP
#define SHIP_HPP
#include "Bullet.hpp"
#include "Entity.hpp"
#include <stdio.h>
#include <vector>

#define MAX_LIVE 10
#define SPAWN 1
#define ALIVE 2
#define DIE 3
#define DEAD 4


class Ship:public Entity{
public:
	Ship();
	~Ship();
	void update();
	void moveL();
	void moveR();
	void fire();
	bool isFire = false;
//	std::vector<Bullet> bullets;
	Bullet bullets[MAX_BULLET];
	int bulletCount;
	uint8_t live;
};
#endif
