
#ifndef __GAME_H__
#define __GAME_H__

#include "DisableCopy.h"

#include <string>

struct GameProperties;

enum class GameState
{
	Init,
	PreGame,
	GameRunning,
	GameEnding,
	Restarting
};

/*!
* @brief Game class that manages the game.
* 
* This class is responsible for:
* - Creating the necessary game components.
* - Collecting user input and reacting to it.
* - Managing the game flow using GameStates.
* 
* The game flow starts when the StartGame() function is called.
* 
* GameState Init:
* - The initial state after the game starts. In this state, the user can:
* -- Restart the game: This will set the game to the Restarting state.
* -- End the game: This will set the game to the GameEnding state.
* -- Define board size: This will create a NodeManager with nodes according to the size of the board and
	 advance the game to the PreGame state.
* -- Run test inputs: This will start feeding inputs defined in TestInputs.h to the game until all defined
	 inputs run out.
* 
* GameState PreGame:
* - The game is ready to be played. In this state, the user can:
* -- Restart the game: This will set the game to the Restarting state.
* -- End the game: This will set the game to the GameEnding state.
* -- Define living nodes: This will inform NodeManager to set a node at the given coordinates to a living state.
* -- Start the game: This will advance the game to the GameRunning state.
*
* GameState GameRunning:
* - The game is running. The game consists of rounds that can be advanced by the user or set to automatic.
*   When the round changes, it will be informed to NodeManager. In this state, the user can:
* -- Restart the game: This will set the game to the Restarting state.
* -- End the game: This will set the game to the GameEnding state.
* -- Set the game to automatic: This will advance the game rounds at time intervals.
* -- Move to the next round: This will advance the game by one round.
* 
* GameState GameEnding:
* - This stage will end the game loop, returning code execution to where StartGame() was called.
*
* GameState Restarting:
* - This stage will set the game back to its initial state and set the GameState to Init.
**/

class Game : DisableCopy
{
public:
	/*!
	* @brief Default constructor.
	**/
	Game();

	/*!
	* @brief Default destructor.
	**/
	~Game();

	/*!
	* @brief Starts the game loop.
	**/
	void StartGame();

private:
	/*!
	* @brief Outputs instructions for the player.
	**/
	void ShowRules();

	/*!
	* @brief Game update loop (state machine).
	**/
	void Update();

	/*!
	* @brief Implements GameState Init functionality.
	**/
	void InitBoard();

	/*!
	* @brief Implements GameState PreGame functionality.
	**/
	void InitLivingCells();

	/*!
	* @brief Implements GameState GameRunning functionality.
	**/
	void RunTheGame();

	/*!
	* @brief Requests input from the user.
	* @return User's input as a string.
	**/
	std::string GetPlayerInput();

	/*!
	* @brief Handles user input.
	* @param input Input to be parsed and reacted to.
	* @return True if input was valid and caused any changes, otherwise false.
	**/
	bool HandlePlayerInput(std::string input);

	/*!
	* @brief Advances the game by one round.
	**/
	void NextRound();

	/*!
	* @brief Outputs the game board.
	**/
	void ShowBoard();

	/*!
	* @brief Resets the game to its initial state.
	**/
	void ResetGame();

	/*!
	* @brief Calls the system to clear the user's console.
	**/
	void ClearScreen();

	/*!
	* @brief Gets test case inputs from TestInputs.h and sets the game to testing mode.
	* @param testCaseId Identifier of the test case to run.
	**/
	void RunTestCase(int testCaseId);

	// Game properties
	GameProperties* mGameProperties;
};

#endif // __GAME_H__
