#include <stdio.h>
#include <Ship.hpp>
Ship::Ship() {
	this->x = 50;
	this->y = 280;
	this->w = 16;
	this->h = 16;
}
Ship::~Ship() {

}
void Ship::update() {
	for (int i = 0; i < MAX_BULLET; i++) {
	        if (bullets[i].status == ACTIVE) {
	            bullets[i].update();
	        }
	    }
}
void Ship::moveL() {
	if (x > 2)
		this->x -= 2;
}
void Ship::moveR() {
	if (x < 222)
		this->x += 2;
}
void Ship::fire(){
	for (int i = 0; i < MAX_BULLET; i++) {
		        if (bullets[i].status == INACTIVE) {
		            bullets[i] = Bullet(this->x + 6, this->y + 8);
		            bullets[i].status = SPAWN;
		            return;
		        }
		    }
}

