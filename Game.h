#ifndef __GAME_H__
#define __GAME_H__

#include "Node.h"

#include <string>

//#pragma once
class Game
{
public:
	Game();
	~Game();

	void StartGame();

	void NodeStateChange(Node* node, State state);

private:
	//void HandlePlayerInput(std::string input);

	void ChangeState();

	void ShowBoard();

	// Board
	int mHeight;
	int mWidth;
	std::string mBoardString;

	// Nodes
	std::vector<Node*> mAllNodes;
	std::vector<Node*> mAliveNodes;
	std::vector<Node*> mTouchedNodes;

	// Other
	int mRound = 0;
};

#endif // __GAME_H__
