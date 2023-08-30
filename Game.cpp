
#include "Game.h"
#include "NodeManager.h"

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

Game::Game(){}

Game::~Game()
{
	ClearGame();
}

void Game::StartGame()
{
	mHeight = 0;
	mWidth = 0;

	ShowRules();
	Update();
}

void Game::ShowRules()
{
	cout << "------------------------------------------" << '\n';
	cout << "|              Game Of Life              |" << '\n';
	cout << "------------------------------------------" << '\n' << '\n';

	cout << "Inputs:" << '\n';
	cout << "- r => Restarts the game" << '\n';
	cout << "- s => Starts the game" << '\n';
	cout << "- d => Hides dead cells" << '\n';
	cout << "- a => Start automatic stage changing" << '\n';
	cout << "- n => Move to next stage" << '\n';
	cout << "- e => End the game" << '\n' << '\n';

	cout << "Board Size" << '\n';
	cout << "- Input: Heigh x Width (Example: 3x5)" << '\n';
	cout << "- Both numbers need to be positive numbers" << '\n';

	cout << '\n' << "Living cells" << '\n';
	cout << "- Input: posX x posY (Example: 3x5)" << '\n';
	cout << "- Both numbers need to be inside game board" << '\n';
	cout << "- NOTE: Indexes starts from 0 so in 3x3 board top left corner is 0x0 and bottom right corner is 2x2" << '\n' << '\n';
	//	std::to_string(2) << "x" << std::to_string(mWidth) << '\n';
}

void Game::Update()
{
	bool playing = true;
	while (playing)
	{
		switch (mGameState)
		{
			case GameState::Init:
			{
				InitBoard();
				break;
			}
			case GameState::PreGame:
			{
				InitLivingCells();
				break;
			}
			case GameState::GameGoing:
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
				ClearGame();
				ShowRules();
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
	bool success = HandlePlayerInput();

	if (success)
	{
		mGameState = GameState::PreGame;
		mNodeManager = new NodeManager(mHeight, mWidth);
		//system("cls");
	}
}

void Game::InitLivingCells()
{
	ShowBoard();

	cout << "Cordinates for a living cell: ";
	bool success = HandlePlayerInput();

	//system("cls");
}

void Game::RunTheGame()
{
	ShowBoard();

	if (mAutoPlay)
	{
		sleep_for(nanoseconds(100000000));
		NextRound();
	}
	else
	{
		cout << "Input: ";
		HandlePlayerInput();
	}
}

bool Game::HandlePlayerInput()
{
	std::string input;
	cin >> input;

	bool inputIsValid = true;
	if (input == "d")
	{
		if(mDarkMode)
			cout << "Revealing empty board markers." << '\n';
		else
			cout << "Hiding empty board markers." << '\n';

		mDarkMode = !mDarkMode;

		ShowBoard();
	}
	else if (input == "r")
	{
		cout << "Restarting the game" << '\n';
		mGameState = GameState::Restarting;
	}
	else if (input == "e")
	{
		cout << "Ending the game" << '\n';
		mGameState = GameState::GameEnding;
	}
	else
	{
		bool error = false;
		try
		{
			switch (mGameState)
			{
				case GameState::Init:
				{
					int height = input.find('x') != std::string::npos ? std::stoi(input.substr(0, input.find("x"))) : -1;
					int width = input.find('x') != std::string::npos ? std::stoi(input.substr(input.find('x') + 1)) : -1;

					if (height <= 0 || width <= 0)
						error = true;
					else
					{
						mHeight = height;
						mWidth = width;
					}

					break;
				}
				case GameState::PreGame:
				{
					if (input == "s")
						mGameState = GameState::GameGoing;
					else
					{
						int x = std::stoi(input.substr(0, input.find("x")));
						int y = std::stoi(input.substr(input.find('x') + 1));

						mNodeManager->ReviveNode(x, y);

						ShowBoard();
					}

					break;
				}
				case GameState::GameGoing:
				{
					if (input == "a")
						mAutoPlay = true;
					else if (input == "n")
					{
						NextRound();
					}
				}
				default:
				{
					// code block
				}
			}
		}
		catch (std::invalid_argument const& ex)
		{
			error = true;
		}

		if (error)
		{
			if(mGameState == GameState::Init)
				std::cout << "Error: Invalid board size (both needs to be numbers over 0)." << '\n';

			inputIsValid = false;
		}
	}

	return inputIsValid;
}

void Game::NextRound()
{
	++mRound;
	mNodeManager->AdvanceRound(mRound);

	system("cls");
	ShowBoard();
}

void Game::ShowBoard()
{
	cout << '\n';

	std::string boardString = mNodeManager->GetNodeString();
	for (int i = 0; i < mHeight; ++i)
	{
		string sub = boardString.substr(i * mWidth, mWidth);
		if(mDarkMode)
			std::replace(sub.begin(), sub.end(), 'x', ' '); // replace all 'x' to ' '

		std::cout << "  " << sub << '\n';
	}

	cout << '\n';
}

void Game::RestartTheGame()
{
	ClearGame();

	system("cls");
	StartGame();
}

void Game::ClearGame()
{
	mHeight = 0;
	mWidth = 0;

	delete(mNodeManager);
	mNodeManager = NULL;

	mDarkMode = false;
	mAutoPlay = false;

	mGameState = GameState::Init;
	system("cls");
}
