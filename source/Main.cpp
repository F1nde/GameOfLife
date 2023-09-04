
// Game Of Life
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

/*!
* This program consists of three classes: Game, NodeManager, and Node.
* - Game represents the actual game that is being played.
* - Node represents cells in the game's rules.
* - NodeManager serves as a controller between Game and Nodes.
*
* NOTE: TestingInput.h can be used to predetermine user inputs for faster testing of the game.
**/

#include "Game.h"

int main()
{
    Game* game = new Game();
    game->StartGame();
}
