#ifndef __NODE_H__
#define __NODE_H__

//#include "Game.h"

#include <vector>

enum class State
{
	Dead = 0,
	Alive,
	Modified
};

//#pragma once
class Node
{
public:
	Node(/*Game* game,*/ int index);
	~Node();

	void Init(std::vector<Node*> neighbors);

	void SetState(State state);
	State GetState();

	std::vector<Node*> NewRoundStart(int round);
	void TouchNode(int round);

private:
	int mIndex;
	State mCurrentState;
	std::vector<Node*> mNeighbors;

	// This round
	int mCurrentRound = 0;
	int mTouches = 0;

	//Game* mGame;
};

#endif // __NODE_H__
