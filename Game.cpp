
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

	std::string input;

	while (mHeight <= 0)
	{
		cout << "Type board heigh: "; // Type a number and press enter
		cin >> input; // Get user input from the keyboard

		mHeight = std::stoi(input);
	}

	while (mWidth <= 0)
	{
		cout << "Type board width: "; // Type a number and press enter
		cin >> input; // Get user input from the keyboard

		mWidth = std::stoi(input);
	}

	mNodeManager = new NodeManager(mHeight, mWidth);

	ShowBoard();

	int x = 0;
	int y = 0;
	int index = 0;

	bool startGame = false;
	while (!startGame)
	{
		//cout << "Next type alive nodes (x.y)! Example: 3.1 || Or Start game typing: s"; // Type a number and press enter
		cin >> input; // Get user input from the keyboard

		if (input == "s" || input == "n" || input == "r")
			startGame = true;
		else
		{
			x = std::stoi(input.substr(0, input.find("x")));
			y = std::stoi(input.substr(input.find('x') + 1));

			mNodeManager->ReviveNode(x, y);

			system("cls");
			ShowBoard();
		}
	}

	bool restartGame = false;
	bool playing = true;
	while (playing)
	{
		++mRound;

		mNodeManager->AdvanceRound(mRound);
		ShowBoard();
		if (input != "s")
		{
			cin >> input; // Get user input from the keyboard

			if (input == "r")
			{
				playing = false;
				restartGame = true;
			}
			else if (input == "d")
			{
				
				mDarkMode = true;
			}
		}
		else
		{
			sleep_for(nanoseconds(100000000));
			system("cls");
		}
	}

	if (restartGame)
	{
		ClearGame();

		system("cls");
		StartGame();
	}
}

void Game::ClearGame()
{
	delete(mNodeManager);
	mNodeManager = NULL;

	mDarkMode = false;
}

void Game::ShowBoard()
{
	std::string boardString = mNodeManager->GetNodeString();
	for (int i = 0; i < mHeight; ++i)
	{
		string sub = boardString.substr(i * mWidth, mWidth);
		if(mDarkMode)
			std::replace(sub.begin(), sub.end(), 'x', ' '); // replace all 'x' to ' '

		std::cout << "  " << sub << '\n';
	}
}
