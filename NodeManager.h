
#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

//#include "Game.h"
#include "Node.h"

#include <string>
#include <vector>

//#pragma once
class NodeManager
{
public:
	NodeManager(int boardHeight, int boardWidth);
	~NodeManager();

	std::string GetNodeString();

	void ReviveNode(int x, int y);
	void AdvanceRound(int round);

	//void Init(std::vector<Node*> neighbors);

	//void SetState(State state);
	//State GetState();

	//std::vector<Node*> NewRoundStart(int round);
	//void TouchNode(int round);

private:
	//int mIndex;
	//State mCurrentState;
	//std::vector<Node*> mNeighbors;

	int mHeight;
	int mWidth;
	std::string mBoardString;

	// 2d vector
	//std::vector<std::vector<Node*>> mAllNodes;
	std::vector<Node*> mAllNodes;
	std::vector<Node*> mAliveNodes;
};

#endif // __NODEMANAGER_H__
