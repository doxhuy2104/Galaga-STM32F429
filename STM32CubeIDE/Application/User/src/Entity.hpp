#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <stdint.h>
class Entity {
public:
	Entity();
	~Entity();
	uint16_t x;
	uint16_t y;
	uint8_t w;
	uint8_t h;
	void update();
	void updateX();
	void updateY();
};
#endif
