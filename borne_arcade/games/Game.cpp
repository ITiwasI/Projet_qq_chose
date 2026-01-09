#include "game.h"

// Define the static member declared in game.h
int game::gameCount = 0;

game::game() {
    id = gameCount;
    gameCount++;
}



game::~game() {
    gameCount--;
}