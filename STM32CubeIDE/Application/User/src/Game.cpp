#include "Game.hpp"
Game game;
Game::Game(){

}
Game::~Game(){

}

void Game::update(){
	for(;;){
		galaga.update();
	}
}

void GameThread(void* argument) {
    game.update();
}
