
// Game Of Life

// Game rules and more info
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

/*!
* This program composes of 3 classes: Game, NodeManager, Node
* - Game presents the actual game that is being played.
* - Node presents cells in the game rules.
* - NodeManger presents a controller between Game and Nodes.
*
* NOTE: TestingInput.h can be used to predetermine user inputs to the game for faster testing.
**/

// Code by Marko Tuominen
// https://github.com/F1nde/GameOfLife

#include "Game.h"

int main()
{
    Game* game = new Game();
    game->StartGame();
}
