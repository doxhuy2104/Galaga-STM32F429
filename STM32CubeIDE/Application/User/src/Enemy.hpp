
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Bullet.hpp"
#include "Entity.hpp"
#include <stdio.h>

#define SPAWN 1
#define ALIVE 2
#define DIE 3
#define DEAD 4

const uint8_t MAX_EBULLET = 20;
const uint8_t MAX_ENEMY = 10;
const uint8_t MAX_CHANGE_DIR_TIME = 80;
const uint8_t MAX_CHANGE_SPR_TIME = 30;
//const uint8_t FIRE_PROBABILITY = 100;

class Enemy:public Entity{
public:
	Enemy();
	~Enemy();
	void update();
	void spawn();
	void checkCollision();
	void moveL();
	void moveR();
	void fire();
	bool isFire = false;
	uint8_t direction= 'R';
	uint8_t changeDirTime;
	uint8_t changeSprTime;
	uint8_t sprite;
	uint8_t count;
	int bulletCount;
	uint16_t score;
};
#endif
