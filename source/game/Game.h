
#ifndef __GAME_H__
#define __GAME_H__

#include "Nodemanager.h"

#include <string>
#include <vector>

enum class GameState
{
	Init,
	PreGame,
	GameRunning,
	GameEnding,
	Restarting
};

/*!
* \brief Game class that presents the game
* 
* Class is responsible for
* - Creating necessary game components
* - Collecting user input and reacting to it
* - Managing game flow using GameStates
* 
* Game flow starts when StartGame() function is called.
* 
* GameState Init:
* - Initial state after game starts. In this state the user can:
* -- 1. Restart the game: this will set the game to Restarting state.
* -- 2. End the game: this will set game to GameEnding state.
* -- 3. Define board size: this will create NodeManager with Nodes acording to the size of a board and advance game to PreGame state.
* -- 4. Run test inputs: this will start feeding inputs defined in TestInputs.h to the game until all defined inputs run out.
* 
* GameState PreGame:
* - Game is ready to be played. In this state the user can:
* -- 1. Restart the game: this will set the game to Restarting state.
* -- 2. End the game: this will set game to GameEnding state.
* -- 3. Define living nodes: this will inform NodeManager to set Node in given cordinates to living state.
* -- 4. Start the game: this will advance game to GameRunning state.
* 
* GameState GameRunning:
* - Game is running. Game consists of rounds which that can be advanced by the user or set to automatic.
*   When round changes it will be informed to NodeManager. In this state the user can:
* -- 1. Restart the game: this will set the game to Restarting state.
* -- 2. End the game: this will set game to GameEnding state.
* -- 3. Set game to automatic: this will advance game round in time intervals.
* -- 4. Move to next round: this will advance game by one round.
* 
* GameState GameEnding:
* - This stage will end the game loop of the game, returning code execution to where StartGame() was called.
* 
* GameState Restarting:
* - This stage will set game back to initial stage and set GameState to Init. 
**/

class Game
{
public:
	Game();
	~Game();

	/*!
	* \brief Starts the game
	**/
	void StartGame();

private:
	/*!
* \brief Starts the game
* \param pic Korttiin asetettava QPixmap kuva
* \param links Kortin reiteista kertova linkkitietorakenne
* \param col Korttiin asetettavan nappulan vari
* \pre links.size() == 4
**/

	/*!
	* \brief Couts instructions for the player.
	**/
	void ShowRules();

	/*!
	* \brief Game update loop (state machine).
	**/
	void Update();

	/*!
	* \brief TODO
	**/
	void InitBoard();

	/*!
	* \brief TODO
	**/
	void InitLivingCells();

	/*!
	* \brief TODO
	**/
	void RunTheGame();

	/*!
	* \brief TODO
	**/
	std::string GetPlayerInput();

	/*!
	* \brief TODO
	**/
	bool HandlePlayerInput(std::string input);

	/*!
	* \brief Advances game by one round.
	**/
	void NextRound();

	/*!
	* \brief Couts the game board
	**/
	void ShowBoard();

	/*!
	* \brief Resets game to initial state
	**/
	void ResetGame();

	/*!
	* \brief Calls system to clear the user's console
	**/
	void ClearScreen();

	/*!
	* \brief Gets test case inputs from TestInputs and sets
	*		 game to testing mode.
	**/
	void RunTestCase(int id);

	// N‰‰ voi laittaa structiin
	GameProperties* mGameProperties;

	// Board size
	int mHeight = 0;
	int mWidth = 0;

	// Node Management
	NodeManager* mNodeManager = NULL;

	// Game properties
	GameState mGameState = GameState::Init;
	bool mAutoPlay = false;
	int mRound = 0;
	//bool mDarkMode = false;

	// Auto testing
	bool mTestingMode = false;
	std::vector<std::string>::iterator mInputItr;
	std::vector<std::string> mTestingInputs;
};

#endif // __GAME_H__
