
#ifndef __GAME_H__
#define __GAME_H__

#include "Nodemanager.h"

#include <string>

class Game
{
public:
	Game();
	~Game();

	void StartGame();

private:
	//void HandlePlayerInput(std::string input);

	void ShowBoard();
	void ClearGame();

	// Board
	int mHeight = 0;
	int mWidth = 0;

	NodeManager* mNodeManager = NULL;

	// Other
	int mRound = 0;
	bool mDarkMode = false;
};

#endif // __GAME_H__
