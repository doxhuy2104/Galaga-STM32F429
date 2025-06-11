
#ifndef SHIP_HPP
#define SHIP_HPP
#include "Bullet.hpp"
#include "Entity.hpp"
#include <stdio.h>
#include <vector>
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

};
#endif
