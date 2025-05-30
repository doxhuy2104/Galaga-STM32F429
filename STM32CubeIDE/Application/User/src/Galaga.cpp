#include "Galaga.hpp"

Galaga::Galaga(){
	this->x=50;
	this->y=280;
}
Galaga::~Galaga(){

}
void Galaga::update(){

}
void Galaga::moveL(){
	if(x>0) this->x--;
}
void Galaga::moveR(){
	if(x<208) this->x++;
}
