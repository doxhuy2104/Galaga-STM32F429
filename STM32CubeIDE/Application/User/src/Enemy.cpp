#include "Enemy.hpp"
#include <stdio.h>
Enemy::Enemy() {
	this->w = 16;
	this->h = 16;
	changeDirTime=MAX_CHANGE_DIR_TIME;
	changeSprTime=MAX_CHANGE_SPR_TIME;
	sprite =1;
}
Enemy::~Enemy() {

}
void Enemy::update() {
	changeDirTime--;
	if(changeDirTime==0){
		changeDirTime=MAX_CHANGE_DIR_TIME;
		if(direction=='R'){
			direction='L';
		}else{
			direction='R';
		}
	}
	changeSprTime--;
	if(changeSprTime==0){
		changeSprTime=MAX_CHANGE_SPR_TIME;
		sprite=!sprite;
	}
}

void Enemy::fire(){
//	for (int i = 0; i < MAX_BULLET; i++) {
//		        if (bullets[i].status == INACTIVE) {
//		            bullets[i] = Bullet(this->x + 6, this->y + 8);
//		            bullets[i].status = SPAWN;
//		            return;
//		        }
//		    }
}
void Enemy::moveL(){
	this->x--;
}
void Enemy::moveR(){
	this->x++;
}
