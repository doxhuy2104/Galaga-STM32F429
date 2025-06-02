#include "bullet.hpp"
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
Bullet::Bullet() {
    this->w = 3;
    this->h = 8;
    this->x = 0;
    this->y = 0;
    status = INACTIVE;
    activeTime=MAX_ACTIVETIME;
}

// Constructor with parameters
Bullet::Bullet(uint16_t x, uint16_t y) {
    this->w = 3;
    this->h = 8;
    this->x = x;
    this->y = y;
    status = SPAWN;
    activeTime=MAX_ACTIVETIME;
}
void Bullet::update() {
	if(y>-8) y-=5;
	if(activeTime>0) activeTime--;
	if(activeTime<=0) updateStatus(INACTIVE);
//	if (status == ACTIVE) {
//		if (y < -8) {
//			updateStatus(INACTIVE);
//		}
//	}
}
