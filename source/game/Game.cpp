
#include "Game.h"
#include "NodeManager.h"
#include "../Testing/TestInputs.h"

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

Game::Game()
{
	mGameProperties = new GameProperties();
}

Game::~Game()
{
	delete(mNodeManager);
	mNodeManager = NULL;
}

void Game::StartGame()
{
	mHeight = 0;
	mWidth = 0;

	Update();
}

void Game::ShowRules()
{
	switch (mGameState)
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
			//cout << "- d => Hides dead cells" << '\n' << '\n';

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
			//cout << "- d => Hides dead cells" << '\n';
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
		switch (mGameState)
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
				if (!pregameRulesShown && !mTestingMode)
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

	if (success && mGameState == GameState::Init)
	{
		mGameState = GameState::PreGame;
		mNodeManager = new NodeManager(mHeight, mWidth);
	}
}

void Game::InitLivingCells()
{
	if (!mTestingMode)
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

	if (mAutoPlay)
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

	if (mTestingMode)
	{
		if (mInputItr != mTestingInputs.end())
		{
			input = *mInputItr;
			++mInputItr;
		}
		else
			mTestingMode = false;
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
		mGameState = GameState::Restarting;
	}
	else if (input == "e")
	{
		cout << "Ending the game" << '\n';
		mGameState = GameState::GameEnding;
	}
	//else if (input == "d")
	//{
	//	if (mGameState != GameState::Init)
	//	{
	//		if (mDarkMode)
	//			cout << "Revealing empty board markers." << '\n';
	//		else
	//			cout << "Hiding empty board markers." << '\n';

	//		mDarkMode = !mDarkMode;
	//	}
	//	else
	//		inputIsValid = false;
	//}
	else if (input == "s")
	{
		if(mGameState == GameState::PreGame)
			mGameState = GameState::GameRunning;
		else
			inputIsValid = false;
	}
	else if (input == "a")
	{
		if (mGameState == GameState::GameRunning)
			mAutoPlay = true;
		else
			inputIsValid = false;
	}
	else if(input == "n")
	{
		if (mGameState == GameState::GameRunning)
			NextRound();
		else
			inputIsValid = false;
	}
	else // Cordinates input
	{
		try
		{
			switch (mGameState)
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
							mHeight = height;
							mWidth = width;
						}
					}

					break;
				}
				case GameState::PreGame:
				{
					int x = input.find('x') != std::string::npos ? std::stoi(input.substr(0, input.find("x"))) : -1;
					int y = input.find('x') != std::string::npos ? std::stoi(input.substr(input.find('x') + 1)) : -1;

					if (x < 0 || y < 0 || x > mWidth - 1 || y > mHeight - 1)
						inputIsValid = false;
					else
						mNodeManager->ReviveNode(x, y);

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
		if (mGameState == GameState::Init)
			std::cout << "Error: Invalid board size (both needs to be numbers over 0)." << '\n';
		else if (mGameState == GameState::PreGame)
			std::cout << "Error: Invalid cordinates (cordinates are not inside the game board)." << '\n';
	}

	return inputIsValid;
}

void Game::NextRound()
{
	++mRound;
	mNodeManager->AdvanceRound(mRound);

	ClearScreen();
	ShowBoard();
}

void Game::ShowBoard()
{
	cout << '\n';

	std::string boardString = mNodeManager->GetNodeString();
	for (int i = 0; i < mHeight; ++i)
	{
		std::string line = std::string(mWidth * 2 + 1, '-');
		std::cout << "  " << line << '\n';

		string sub = boardString.substr(i * mWidth, mWidth);

		int characters = sub.length();
		for (int j = 0; j < characters; ++j)
		{
			sub.insert(j*2, "|");
		}

		sub.append("|");

		//if (mDarkMode)
			std::replace(sub.begin(), sub.end(), 'x', ' '); // replace all 'x' to ' '

		std::cout << "  " << sub << '\n';
	}

	std::string lastLine = std::string(mWidth * 2 + 1, '-');
	std::cout << "  " << lastLine << '\n';

	cout << '\n';
}

void Game::ResetGame()
{
	mHeight = 0;
	mWidth = 0;

	delete(mNodeManager);
	mNodeManager = NULL;

	//mDarkMode = false;
	mAutoPlay = false;

	mGameState = GameState::Init;
	mRound = 0;
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

void Game::RunTestCase(int id)
{
	std::vector<std::string> inputs = GetTestInputs(id);

	if (inputs.size() != 0)
	{
		mTestingMode = true;
		mTestingInputs = inputs;
		mInputItr = mTestingInputs.begin();
	}
}
