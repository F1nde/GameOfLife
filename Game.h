
#ifndef __GAME_H__
#define __GAME_H__

#include "Nodemanager.h"

#include <string>
#include <vector>

enum class GameState
{
	Init,
	PreGame,
	GameGoing,
	GameEnding,
	Restarting
};

class Game
{
public:
	Game();
	~Game();

	void StartGame();

private:
	void ShowRules();
	void Update();

	void InitBoard();
	void InitLivingCells();
	void RunTheGame();

	std::string GetPlayerInput();
	bool HandlePlayerInput(std::string input);

	void NextRound();
	void ShowBoard();
	void RestartTheGame();
	void ClearGame();

	void ClearScreen();
	void RunTestCase(int id);

	// Board
	int mHeight = 0;
	int mWidth = 0;

	NodeManager* mNodeManager = NULL;

	// Other
	GameState mGameState = GameState::Init;
	bool mAutoPlay = false;

	int mRound = 0;
	bool mDarkMode = false;

	// Auto testing
	bool mTesting = false;
	std::vector<std::string>::iterator mInputItr;
	std::vector<std::string> mTestingInputs;
};

#endif // __GAME_H__
