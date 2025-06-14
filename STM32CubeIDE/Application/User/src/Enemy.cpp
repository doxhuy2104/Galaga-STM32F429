#include "Enemy.hpp"
#include <stdio.h>
#include <stm32f4xx_hal.h>
extern RNG_HandleTypeDef hrng;

Enemy::Enemy() {
	this->w = 16;
	this->h = 16;
	changeDirTime = MAX_CHANGE_DIR_TIME;
	changeSprTime = MAX_CHANGE_SPR_TIME;
	sprite = 1;
}
Enemy::~Enemy() {

}
void Enemy::update() {
	changeDirTime--;
	if (changeDirTime == 0) {
		changeDirTime = MAX_CHANGE_DIR_TIME;
		if (direction == 'R') {
			direction = 'L';
		} else {
			direction = 'R';
		}
	}
	changeSprTime--;
	if (changeSprTime == 0) {
		changeSprTime = MAX_CHANGE_SPR_TIME;
		sprite = !sprite;
	}
	count++;
	if(count>=20){
		count = 0;
		uint32_t random = HAL_RNG_GetRandomNumber(&hrng);
			if ((random % 30) == 0) {
				isFire = true;
			} else {
				isFire = false;
			}
	}

}

void Enemy::fire() {

}
void Enemy::moveL() {
	this->x--;
}
void Enemy::moveR() {
	this->x++;
}
