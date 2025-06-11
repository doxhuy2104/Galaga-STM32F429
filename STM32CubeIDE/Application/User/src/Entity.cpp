#include "Entity.hpp"

Entity::Entity() {

}
Entity::~Entity() {

}
void Entity::update() {

}
void Entity::updateX() {

}
void Entity::updateY() {

}
void Entity::updateStatus(uint8_t status) {
	this->status = status;
}
bool Entity::checkCollision(Entity e1, Entity e2) {
	if (e1.x + e1.w <= e2.x ||
		e1.x >= e2.x + e2.w ||
		e1.y + e1.h <= e2.y ||
		e1.y >= e2.y + e2.h) {
		return false;
	}

	return true;
}
