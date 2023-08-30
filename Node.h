
#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

enum class State
{
	Dead = 0,
	Alive,
	WaitingForRevive,
	WillStayAlive,
	WillStayDead
};

class Node
{
public:
	Node(int index);
	~Node();

	void Init(std::vector<Node*> neighbors);

	void SetState(State state);
	State GetState();
	bool IsAlive();
	bool IsAlreadyCheckedThisRound(int round);

	std::vector<Node*> GetRevivableNeighbours(int round);
	bool IsAliveNextRound(int round);

	int GetNodeId();

private:
	int mNodeId = 0;
	State mCurrentState = State::Dead;
	std::vector<Node*> mNeighbors = std::vector<Node*>();

	// This round
	int mCurrentRound = 0;
	bool mIsAliveAfterThisRound = true;
};

#endif // __NODE_H__
