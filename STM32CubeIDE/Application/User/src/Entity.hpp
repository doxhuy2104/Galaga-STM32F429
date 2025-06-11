#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <stdint.h>

const uint8_t SPAWN = 1;
const uint8_t ACTIVE = 2;
const uint8_t INACTIVE = 3;

class Entity {
public:
	Entity();
	~Entity();
	uint16_t x;
	uint16_t y;
	uint8_t w;
	uint8_t h;
	uint8_t status;
	void update();
	void updateStatus(uint8_t status);
	void updateX();
	void updateY();
	static bool checkCollision(Entity e1,Entity e2);
};
#endif
