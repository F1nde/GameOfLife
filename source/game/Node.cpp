
#include "Node.h"

Node::Node(int id)
{
	mNodeId = id;
}

Node::~Node()
{
	for (int i = 0; i < mNeighbors.size(); ++i)
		mNeighbors[i] = NULL;
}

void Node::Init(std::vector<Node*> neighbors)
{
	for (int i = 0; i < neighbors.size(); ++i)
		mNeighbors.push_back(neighbors[i]);
}

void Node::SetState(State state)
{
	mCurrentState = state;
}

State Node::GetState()
{
	return mCurrentState;
}

bool Node::IsAlive()
{
	return (GetState() == State::Alive || GetState() == State::WillStayAlive);
}

bool Node::IsAlreadyCheckedThisRound(int round)
{
	if (mCurrentRound != round)
		return false;
	else
	{
		return (GetState() == State::WaitingForRevive
			|| GetState() == State::WillStayAlive
			|| GetState() == State::WillStayDead);
	}
}

// TODO: Rename this
std::vector<Node*> Node::GetRevivableNeighbours(int round)
{
	std::vector<Node*> revivableNodes;

	for (int i = 0; i < mNeighbors.size(); ++i)
	{
		if (!mNeighbors[i]->IsAlreadyCheckedThisRound(round))
		{
			bool alive = mNeighbors[i]->IsAliveNextRound(round);
			if (alive)
				revivableNodes.push_back(mNeighbors[i]);
		}
	}

	return revivableNodes;
}

bool Node::IsAliveNextRound(int round)
{
	// If round numbers match
	// -> current data is already valid
	if (mCurrentRound != round)
	{
		// NOTE: This state is not cleared by the Nodemanager
		if (mCurrentState == State::WillStayDead)
			mCurrentState = State::Dead;

		mCurrentRound = round;
		mIsAliveAfterThisRound = false;

		int aliveNeighbors = 0;
		for (int i = 0; i < mNeighbors.size(); ++i)
		{
			if (mNeighbors[i]->IsAlive())
				++aliveNeighbors;

			if (mCurrentState == State::Dead)
			{
				if(aliveNeighbors == 3)
					mIsAliveAfterThisRound = true;
				else if (aliveNeighbors > 3)
				{
					mIsAliveAfterThisRound = false;
					break;
				}
			}
			else if (mCurrentState == State::Alive)
			{
				if (aliveNeighbors >= 2 && aliveNeighbors <= 3)
					mIsAliveAfterThisRound = true;
				else if (aliveNeighbors > 3)
				{
					mIsAliveAfterThisRound = false;
					break;
				}
			}
			else
			{
				// Error
			}
		}

		if (mCurrentState == State::Dead && mIsAliveAfterThisRound)
			mCurrentState = State::WaitingForRevive;
		else if (mCurrentState == State::Dead && !mIsAliveAfterThisRound)
			mCurrentState = State::WillStayDead;
		else if (mCurrentState == State::Alive && mIsAliveAfterThisRound)
			mCurrentState = State::WillStayAlive;
	}

	return mIsAliveAfterThisRound;
}

int Node::GetNodeId()
{
	return mNodeId;
}
