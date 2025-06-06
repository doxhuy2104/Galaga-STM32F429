#ifndef BULLET_HPP
#define BULLET_HPP
#include "Entity.hpp"

const uint8_t MAX_BULLET = 20;
const uint8_t MAX_ACTIVETIME=60;
class Bullet: public Entity {
public:
	Bullet();
	Bullet(uint16_t x, uint16_t y);
	int activeTime;
	void update();
	void draw();
private:
	int speed;
};
#endif
