#include "Game.h"
#include "Node.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

Game::Game()
{
}

Game::~Game()
{
	// TODO
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

	for (int i = 0; i < mHeight * mWidth; ++i)
	{
		auto node = new Node(i);
		mAllNodes.push_back(node);
	}

	mBoardString = std::string(mHeight * mWidth, 'x');
	ShowBoard();

	int x = 0;
	int y = 0;
	int index = 0;

	bool startGame = false;
	while (!startGame)
	{
		cout << "Next type alive nodes (x.y)! Example: 3.1 || Or Start game typing: s"; // Type a number and press enter
		cin >> input; // Get user input from the keyboard

		if (input == "s")
			startGame = true;
		else
		{
			x = std::stoi(input.substr(0, input.find("x")));
			y = std::stoi(input.substr(input.find('x') + 1));

			// TODO: Tsekkaa onko node jo elossa

			index = x + y * mHeight;
			mBoardString[index] = 'o';
			mAllNodes[index]->SetState(State::Alive);
			mAliveNodes.push_back(mAllNodes[index]);

			system("cls");
			ShowBoard();
		}
	}

	bool playing = true;
	while (playing)
	{
		ChangeState();
		ShowBoard();
		cin >> input; // Get user input from the keyboard
	}
}

void Game::NodeStateChange(Node* node, State state)
{
	if (state == State::Dead)
	{
		if (std::find(mAliveNodes.begin(), mAliveNodes.end(), node) != mAliveNodes.end())
		{
			mAliveNodes.erase(std::find(mAliveNodes.begin(), mAliveNodes.end(), node));
		}
		else
		{
			// Error;
		}
	}
	else
		mAliveNodes.push_back(node);
}

/*
void Game::HandlePlayerInput(std::string input)
{
}
*/

void Game::ChangeState()
{
	mTouchedNodes.clear();
	for (int i = 0; i < mAliveNodes.size(); ++i)
	{
		mAliveNodes[i]->NewRoundStart(mRound);
	}

	++mRound;
}

void Game::ShowBoard()
{
	for(int i = 0; i < mHeight; ++i)
		std::cout << "  " << mBoardString.substr(i * mWidth, mWidth) << '\n';
}
