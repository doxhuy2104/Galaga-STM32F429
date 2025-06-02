
#ifndef GALAGA_HPP
#define GALAGA_HPP
#include "Bullet.hpp"
#include "Entity.hpp"
#include <stdio.h>
#include <vector>
class Galaga:public Entity{
public:
	Galaga();
	~Galaga();
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
