#include "Game.h"
#include "NodeManager.h"

#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include <chrono>
#include <thread>

using namespace std;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

Game::Game()
{
}

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

	mBoardString = std::string(mHeight * mWidth, 'x');
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

			// TODO: Tsekkaa onko node jo elossa

			mNodeManager->ReviveNode(x, y);

			/*
			index = x + y * mHeight;
			mBoardString[index] = 'o';
			mAllNodes[index]->SetState(State::Alive);
			mAliveNodes.push_back(mAllNodes[index]);
			*/

			system("cls");
			ShowBoard();
		}
	}

	bool restartGame = false;
	bool playing = true;
	while (playing)
	{
		++mRound;

		//ChangeState();
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

//void Game::NodeStateChange(Node* node, State state)
//{
//	if (state == State::Dead)
//	{
//		if (std::find(mAliveNodes.begin(), mAliveNodes.end(), node) != mAliveNodes.end())
//		{
//			mAliveNodes.erase(std::find(mAliveNodes.begin(), mAliveNodes.end(), node));
//		}
//		else
//		{
//			// Error;
//		}
//	}
//	else
//		mAliveNodes.push_back(node);
//}

/*
void Game::HandlePlayerInput(std::string input)
{
}
*/

//void Game::ChangeState()
//{
//	mTouchedNodes.clear();
//	for (int i = 0; i < mAliveNodes.size(); ++i)
//	{
//		mAliveNodes[i]->NewRoundStart(mRound);
//	}
//
//	++mRound;
//}

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
