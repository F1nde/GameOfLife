
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

	InitBoard();

	if (mGameState != GameState::Restarting)
		InitLivingCells();

	if (mGameState != GameState::Restarting)
		RunTheGame();

	if (mGameState == GameState::Restarting)
		RestartTheGame();

	//ShowBoard();

	//int x = 0;
	//int y = 0;
	//int index = 0;

	//bool startGame = false;
	//while (!startGame)
	//{
	//	//cout << "Next type alive nodes (x.y)! Example: 3.1 || Or Start game typing: s"; // Type a number and press enter
	//	cin >> input; // Get user input from the keyboard

	//	if (input == "s" || input == "n" || input == "r")
	//		startGame = true;
	//	else
	//	{
	//		x = std::stoi(input.substr(0, input.find("x")));
	//		y = std::stoi(input.substr(input.find('x') + 1));

	//		mNodeManager->ReviveNode(x, y);

	//		system("cls");
	//		ShowBoard();
	//	}
	//}

	//bool restartGame = false;
	//bool playing = true;
	//while (playing)
	//{
	//	++mRound;

	//	mNodeManager->AdvanceRound(mRound);
	//	ShowBoard();
	//	if (input != "s")
	//	{
	//		cin >> input; // Get user input from the keyboard

	//		if (input == "r")
	//		{
	//			playing = false;
	//			restartGame = true;
	//		}
	//		else if (input == "d")
	//		{
	//			
	//			mDarkMode = true;
	//		}
	//	}
	//	else
	//	{
	//		sleep_for(nanoseconds(100000000));
	//		system("cls");
	//	}
	//}

	//if (restartGame)
	//{
	//	ClearGame();

	//	system("cls");
	//	StartGame();
	//}
}

void Game::InitBoard()
{
	cout << "------------------------------------------" << '\n';
	cout << "|              Game Of Life              |" << '\n';
	cout << "------------------------------------------" << '\n' << '\n';

	cout << "Inputs:" << '\n';
	cout << "- r => Restarts the game" << '\n' << '\n';

	cout << "Init Board Size" << '\n';
	cout << "- Input: Heigh x Width (Example: 3x5)" << '\n';
	cout << "- Both numbers need to be positive numbers" << '\n' << '\n';

	while (mGameState == GameState::Init)
	{
		cout << "Board Size: ";
		GetPlayerInput(PlayerInputType::BoardSize);
	}

	mNodeManager = new NodeManager(mHeight, mWidth);

	system("cls");
}

void Game::InitLivingCells()
{
	cout << "------------------------------------------" << '\n';
	cout << "|              Game Of Life              |" << '\n';
	cout << "------------------------------------------" << '\n' << '\n';

	cout << "Inputs:" << '\n';
	cout << "- r => Restarts the game" << '\n';
	cout << "- s => Starts the game" << '\n';
	cout << "- d => Hides dead cells" << '\n';

	cout << '\n' << "Init living cells" << '\n';
	cout << "- Input: posX x posY (Example: 3x5)" << '\n';
	cout << "- Both numbers need to be inside game board" << '\n';
	cout << "- NOTE: Top left corner is 0x0 and bottom right corner is " <<
		std::to_string(mHeight) << "x" << std::to_string(mWidth) << '\n';

	ShowBoard();

	while (mGameState == GameState::PreGame)
	{
		cout << "Cordinates for a living cell: ";
		GetPlayerInput(PlayerInputType::PreGame);
	}

	system("cls");
}

void Game::RunTheGame()
{
	cout << "------------------------------------------" << '\n';
	cout << "|              Game Of Life              |" << '\n';
	cout << "------------------------------------------" << '\n' << '\n';

	cout << "Inputs:" << '\n';
	cout << "- r => Restarts the game" << '\n';
	cout << "- d => Hides dead cells" << '\n';
	cout << "- a => Start automatic stage changing" << '\n';
	cout << "- n => Move to next stage" << '\n';

	ShowBoard();

	while (mGameState == GameState::GameGoing)
	{
		if (mAutoPlay)
		{
			sleep_for(nanoseconds(100000000));
			NextRound();
		}
		else
		{
			cout << "Input: ";
			GetPlayerInput(PlayerInputType::GameGoing);

			cout << "------------------------------------------" << '\n';
			cout << "|              Game Of Life              |" << '\n';
			cout << "------------------------------------------" << '\n' << '\n';

			cout << "Inputs:" << '\n';
			cout << "- r => Restarts the game" << '\n';
			cout << "- d => Hides dead cells" << '\n';
			cout << "- a => Start automatic stage changing" << '\n';
			cout << "- n => Move to next stage" << '\n';
		}
	}
}

void Game::GetPlayerInput(PlayerInputType type)
{
	std::string input;
	cin >> input;

	if (input == "d" && mGameState != GameState::Init)
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
	else
	{
		bool error = false;
		try
		{
			switch (type)
			{
				case PlayerInputType::BoardSize:
				{
					int height = std::stoi(input.substr(0, input.find("x")));
					int width = std::stoi(input.substr(input.find('x') + 1));

					if (height <= 0 || width <= 0)
						error = true;
					else
					{
						mHeight = height;
						mWidth = width;

						mGameState = GameState::PreGame;
					}

					break;
				}
				case PlayerInputType::PreGame:
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
				case PlayerInputType::GameGoing:
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
			if (type == PlayerInputType::BoardSize)
				std::cout << "Error: Invalid board size (both needs to be numbers over 0)." << '\n';
		}
	}
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
	delete(mNodeManager);
	mNodeManager = NULL;

	mDarkMode = false;
	mAutoPlay = false;

	mGameState = GameState::Init;
	system("cls");
}
