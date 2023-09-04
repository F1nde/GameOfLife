
#include "Game.h"
#include "NodeManager.h"
#include "TestInputs.h"

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::cin;
using std::string;

using namespace std::this_thread;
using namespace std::chrono;

struct GameProperties
{
	// Board size
	int mHeight = 0;
	int mWidth = 0;

	// Node Management
	NodeManager* mNodeManager = NULL;

	// Current game state
	GameState mGameState = GameState::Init;

	// Determines if game waits for player input when advancing game rounds.
	bool mAutoPlay = false;

	// Current round number.
	int mRound = 0;

	// Auto testing mode + inputs
	bool mTestingMode = false;
	std::vector<std::string>::iterator mInputItr;
	std::vector<std::string> mTestingInputs;
};

Game::Game()
{
	mGameProperties = NULL;
}

Game::~Game()
{
	delete(mGameProperties->mNodeManager);
	mGameProperties->mNodeManager = NULL;

	delete(mGameProperties);
	mGameProperties = NULL;
}

void Game::StartGame()
{
	mGameProperties = new GameProperties();
	Update();
}

void Game::ShowRules()
{
	switch (mGameProperties->mGameState)
	{
		case GameState::Init:
		{
			cout << "------------------------------------------" << '\n';
			cout << "|              Game Of Life              |" << '\n';
			cout << "------------------------------------------" << '\n' << '\n';

			cout << "Test patterns" << '\n';
			cout << "- 1 => Block" << '\n';
			cout << "- 2 => Bee-hive" << '\n';
			cout << "- 3 => Loaf" << '\n';
			cout << "- 4 => Boat" << '\n';
			cout << "- 5 => Tub" << '\n';
			cout << "- 6 => Blinker" << '\n';
			cout << "- 7 => Toad" << '\n';
			cout << "- 8 => Beacon" << '\n';
			cout << "- 9 => Pulsar" << '\n';
			cout << "- 10 => Penta-decathlon" << '\n';
			cout << "- 11 => Glider" << '\n';
			cout << "- 12 => Light-weight spaceship" << '\n';
			cout << "- 13 => Middle-weight spaceship" << '\n';
			cout << "- 14 => Heavy-weight spaceship" << '\n' << '\n';

			cout << "Inputs:" << '\n';
			cout << "- r => Restarts the game" << '\n';
			cout << "- e => Exit the program" << '\n' << '\n';

			cout << "Board Size" << '\n';
			cout << "- Input: Width x Heigh (Example: 3x5)" << '\n';
			cout << "- Both numbers need to be positive numbers" << '\n' << '\n';
			break;
		}
		case GameState::PreGame:
		{
			cout << "------------------------------------------" << '\n';
			cout << "|              Game Of Life              |" << '\n';
			cout << "------------------------------------------" << '\n' << '\n';

			cout << "Inputs:" << '\n';
			cout << "- r => Restarts the game" << '\n';
			cout << "- e => Exit the program" << '\n';
			cout << "- s => Starts the game" << '\n';

			cout << "Living cells" << '\n';
			cout << "- Input: posX x posY (Example: 3x5)" << '\n';
			cout << "- Both numbers need to be inside game board" << '\n';
			cout << "- NOTE: Indexes starts from 0 so in 3x3 board top left corner is 0x0 and bottom right corner is 2x2" << '\n';

			break;
		}
		case GameState::GameRunning:
		{
			cout << "Inputs:" << '\n';
			cout << "- r => Restarts the game" << '\n';
			cout << "- e => Exit the program" << '\n';
			cout << "- a => Start automatic stage changing" << '\n';
			cout << "- n => Move to next stage" << '\n' << '\n';

			break;
		}
		case GameState::GameEnding:
			break;
		case GameState::Restarting:
			break;
		default:
			break;
	}
}

void Game::Update()
{
	bool initRulesShown = false;
	bool pregameRulesShown = false;
	bool playing = true;
	while (playing)
	{
		switch (mGameProperties->mGameState)
		{
			case GameState::Init:
			{
				if (!initRulesShown)
				{
					ClearScreen();
					ShowRules();
					initRulesShown = true;
				}

				InitBoard();
				break;
			}
			case GameState::PreGame:
			{
				if (!pregameRulesShown && !mGameProperties->mTestingMode)
				{
					ClearScreen();
					ShowRules();
					pregameRulesShown = true;
				}

				InitLivingCells();
				break;
			}
			case GameState::GameRunning:
			{
				RunTheGame();
				break;
			}
			case GameState::GameEnding:
			{
				playing = false;
				break;
			}
			case GameState::Restarting:
			{
				ResetGame();
				ShowRules();

				initRulesShown = false;
				pregameRulesShown = false;

				break;
			}
			default:
				break;
		}
	}
}

void Game::InitBoard()
{
	cout << "Board Size: ";

	std::string input = GetPlayerInput();
	bool success = HandlePlayerInput(input);

	if (success && mGameProperties->mGameState == GameState::Init)
	{
		mGameProperties->mGameState = GameState::PreGame;
		mGameProperties->mNodeManager = new NodeManager(mGameProperties->mWidth, mGameProperties->mHeight);
	}
}

void Game::InitLivingCells()
{
	if (!mGameProperties->mTestingMode)
	{
		ShowBoard();
		cout << "Cordinates for a living cell: ";
	}

	std::string input = GetPlayerInput();
	bool success = HandlePlayerInput(input);
}

void Game::RunTheGame()
{
	ClearScreen();
	ShowBoard();

	if (mGameProperties->mAutoPlay)
	{
		NextRound();
		sleep_for(nanoseconds(100000000));
	}
	else
	{
		ShowRules();
		cout << "Input: ";
		std::string input = GetPlayerInput();
		HandlePlayerInput(input);
	}
}

std::string Game::GetPlayerInput()
{
	std::string input = "";

	if (mGameProperties->mTestingMode)
	{
		if (mGameProperties->mInputItr != mGameProperties->mTestingInputs.end())
		{
			input = *mGameProperties->mInputItr;
			++mGameProperties->mInputItr;
		}
		else
			mGameProperties->mTestingMode = false;
	}

	if(input == "")
		cin >> input;

	return input;
}

bool Game::HandlePlayerInput(std::string input)
{
	bool inputIsValid = true;
	if (input == "r")
	{
		cout << "Restarting the game" << '\n';
		mGameProperties->mGameState = GameState::Restarting;
	}
	else if (input == "e")
	{
		cout << "Ending the game" << '\n';
		mGameProperties->mGameState = GameState::GameEnding;
	}
	else if (input == "s")
	{
		if(mGameProperties->mGameState == GameState::PreGame)
			mGameProperties->mGameState = GameState::GameRunning;
		else
			inputIsValid = false;
	}
	else if (input == "a")
	{
		if (mGameProperties->mGameState == GameState::GameRunning)
			mGameProperties->mAutoPlay = true;
		else
			inputIsValid = false;
	}
	else if(input == "n")
	{
		if (mGameProperties->mGameState == GameState::GameRunning)
			NextRound();
		else
			inputIsValid = false;
	}
	else // Cordinates input
	{
		try
		{
			switch (mGameProperties->mGameState)
			{
				case GameState::Init:
				{
					// Auto test cases
					if (input.find('x') == std::string::npos)
					{
						int id = std::stoi(input);
						RunTestCase(id);
						inputIsValid = false;
					}
					else
					{
						int width = std::stoi(input.substr(0, input.find("x")));
						int height = std::stoi(input.substr(input.find('x') + 1));

						if (height <= 0 || width <= 0)
							inputIsValid = false;
						else
						{
							mGameProperties->mHeight = height;
							mGameProperties->mWidth = width;
						}
					}

					break;
				}
				case GameState::PreGame:
				{
					int x = input.find('x') != std::string::npos ? std::stoi(input.substr(0, input.find("x"))) : -1;
					int y = input.find('x') != std::string::npos ? std::stoi(input.substr(input.find('x') + 1)) : -1;

					if (x < 0 || y < 0 || x > mGameProperties->mWidth - 1 || y > mGameProperties->mHeight - 1)
						inputIsValid = false;
					else
						mGameProperties->mNodeManager->ReviveNode(x, y);

					break;
				}
				default:
					break;
			}
		}
		catch (std::invalid_argument const& ex)
		{
			inputIsValid = false;
		}
	}

	if (!inputIsValid)
	{
		if (mGameProperties->mGameState == GameState::Init)
			std::cout << "Error: Invalid board size (both needs to be numbers over 0)." << '\n';
		else if (mGameProperties->mGameState == GameState::PreGame)
			std::cout << "Error: Invalid cordinates (cordinates are not inside the game board)." << '\n';
	}

	return inputIsValid;
}

void Game::NextRound()
{
	++mGameProperties->mRound;
	mGameProperties->mNodeManager->AdvanceRound(mGameProperties->mRound);

	ClearScreen();
	ShowBoard();
}

// TODO: Selkeytä
void Game::ShowBoard()
{
	cout << '\n';

	std::string boardString = mGameProperties->mNodeManager->GetNodeString();
	for (int i = 0; i < mGameProperties->mHeight; ++i)
	{
		std::string line = std::string(mGameProperties->mWidth * 2 + 1, '-');
		std::cout << "  " << line << '\n';

		string sub = boardString.substr(i * mGameProperties->mWidth, mGameProperties->mWidth);

		int characters = sub.length();
		for (int j = 0; j < characters; ++j)
		{
			sub.insert(j*2, "|");
		}

		sub.append("|");
		std::replace(sub.begin(), sub.end(), 'x', ' '); // replace all 'x' to ' '

		std::cout << "  " << sub << '\n';
	}

	std::string lastLine = std::string(mGameProperties->mWidth * 2 + 1, '-');
	std::cout << "  " << lastLine << '\n';

	cout << '\n';
}

void Game::ResetGame()
{
	delete(mGameProperties->mNodeManager);
	mGameProperties->mNodeManager = NULL;

	delete(mGameProperties);
	mGameProperties = NULL;

	ClearScreen();
}

void Game::ClearScreen()
{
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif
}

void Game::RunTestCase(int testCaseId)
{
	std::vector<std::string> inputs = GetTestInputs(testCaseId);

	if (inputs.size() != 0)
	{
		mGameProperties->mTestingMode = true;
		mGameProperties->mTestingInputs = inputs;
		mGameProperties->mInputItr = mGameProperties->mTestingInputs.begin();
	}
}
