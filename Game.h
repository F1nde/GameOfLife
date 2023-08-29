
#ifndef __GAME_H__
#define __GAME_H__

#include "Nodemanager.h"

#include <string>

enum class PlayerInputType
{
	BoardSize,
	PreGame,
	GameGoing
};

enum class GameState
{
	Init,
	PreGame,
	GameGoing,
	Restarting
};

class Game
{
public:
	Game();
	~Game();

	void StartGame();

private:
	void InitBoard();
	void InitLivingCells();
	void RunTheGame();

	void GetPlayerInput(PlayerInputType type);

	void NextRound();
	void ShowBoard();
	void RestartTheGame();
	void ClearGame();

	// Board
	int mHeight = 0;
	int mWidth = 0;

	NodeManager* mNodeManager = NULL;

	// Other
	GameState mGameState = GameState::Init;
	bool mAutoPlay = false;
	//bool mGameGoing = false;
	//bool mRestaring = false;

	int mRound = 0;
	bool mDarkMode = false;
};

#endif // __GAME_H__
