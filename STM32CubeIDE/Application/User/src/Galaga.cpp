#include "Galaga.hpp"
#include <stdio.h>
Galaga::Galaga() {
	this->x = 50;
	this->y = 280;
	this->w = 16;
	this->h = 16;
//	this->bulletCount=0;
//	for (int i = 0; i < MAX_BULLET; i++) {
//	        bullets[i] = Bullet(0, 0);
//	        bullets[i].status = INACTIVE;
//	    }
}
Galaga::~Galaga() {

}
void Galaga::update() {
	for (int i = 0; i < MAX_BULLET; i++) {
	        if (bullets[i].status == ACTIVE) {
	            bullets[i].update();
	        }
	    }
}
void Galaga::moveL() {
	if (x > 2)
		this->x -= 3;
}
void Galaga::moveR() {
	if (x < 222)
		this->x += 3;
}
void Galaga::fire(){
	for (int i = 0; i < MAX_BULLET; i++) {
		        if (bullets[i].status == INACTIVE) {
		            bullets[i] = Bullet(this->x + 6, this->y + 8);
		            bullets[i].status = SPAWN;
		            return;
		        }
		    }
}

