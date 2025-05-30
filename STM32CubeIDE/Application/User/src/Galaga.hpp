
#ifndef GALAGA_HPP
#define GALAGA_HPP
#include "Bullet.hpp"
#include "Entity.hpp"
#include <stdio.h>
class Galaga:public Entity{
public:
	Galaga();
	~Galaga();
	void update();
	void moveL();
	void moveR();
	void shoot();
};
#endif
