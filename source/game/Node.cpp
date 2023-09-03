
#include "Node.h"

struct NodeProperties
{
	int mNodeId;
	NodeState mCurrentState = NodeState::Dead;
	std::vector<Node*> mNeighbors = std::vector<Node*>();

	// This round
	int mCurrentRound = 0;
	bool mIsAliveAfterThisRound = true;
};

Node::Node(int id)
{
	mProperties = new NodeProperties;
	mProperties->mNodeId = id;
}

Node::~Node()
{
	for (int i = 0; i < mProperties->mNeighbors.size(); ++i)
		mProperties->mNeighbors[i] = NULL;
}

void Node::Init(std::vector<Node*> neighbors)
{
	if (neighbors.size() == 0)
	{
		for (int i = 0; i < neighbors.size(); ++i)
			mProperties->mNeighbors.push_back(neighbors[i]);
	}
	else
	{
		// Error
	}
}

void Node::SetState(NodeState state)
{
	mProperties->mCurrentState = state;
}

NodeState Node::GetState()
{
	return mProperties->mCurrentState;
}

bool Node::IsAlive()
{
	return (GetState() == NodeState::Alive || GetState() == NodeState::WillStayAlive);
}

bool Node::IsAlreadyCheckedThisRound(int round)
{
	if (mProperties->mCurrentRound != round)
		return false;
	else
	{
		return (GetState() == NodeState::WaitingForRevive
			|| GetState() == NodeState::WillStayAlive
			|| GetState() == NodeState::WillStayDead);
	}
}

std::vector<Node*> Node::GetAliveNotCheckedNeighboursAfterGivenRound(int round)
{
	std::vector<Node*> revivableNodes;

	for (int i = 0; i < mProperties->mNeighbors.size(); ++i)
	{
		if (!mProperties->mNeighbors[i]->IsAlreadyCheckedThisRound(round))
		{
			bool alive = mProperties->mNeighbors[i]->IsAliveNextRound(round);
			if (alive)
				revivableNodes.push_back(mProperties->mNeighbors[i]);
		}
	}

	return revivableNodes;
}

bool Node::IsAliveNextRound(int round)
{
	// If round numbers match
	// -> current data is already valid
	if (mProperties->mCurrentRound != round)
	{
		// NOTE: This state is not cleared by the Nodemanager
		if (mProperties->mCurrentState == NodeState::WillStayDead)
			mProperties->mCurrentState = NodeState::Dead;

		mProperties->mCurrentRound = round;
		mProperties->mIsAliveAfterThisRound = false;

		int aliveNeighbors = 0;
		for (int i = 0; i < mProperties->mNeighbors.size(); ++i)
		{
			if (mProperties->mNeighbors[i]->IsAlive())
				++aliveNeighbors;

			if (mProperties->mCurrentState == NodeState::Dead)
			{
				if(aliveNeighbors == 3)
					mProperties->mIsAliveAfterThisRound = true;
				else if (aliveNeighbors > 3)
				{
					mProperties->mIsAliveAfterThisRound = false;
					break;
				}
			}
			else if (mProperties->mCurrentState == NodeState::Alive)
			{
				if (aliveNeighbors >= 2 && aliveNeighbors <= 3)
					mProperties->mIsAliveAfterThisRound = true;
				else if (aliveNeighbors > 3)
				{
					mProperties->mIsAliveAfterThisRound = false;
					break;
				}
			}
			else
			{
				// Error
			}
		}

		if (mProperties->mCurrentState == NodeState::Dead && mProperties->mIsAliveAfterThisRound)
			mProperties->mCurrentState = NodeState::WaitingForRevive;
		else if (mProperties->mCurrentState == NodeState::Dead && !mProperties->mIsAliveAfterThisRound)
			mProperties->mCurrentState = NodeState::WillStayDead;
		else if (mProperties->mCurrentState == NodeState::Alive && mProperties->mIsAliveAfterThisRound)
			mProperties->mCurrentState = NodeState::WillStayAlive;
	}

	return mProperties->mIsAliveAfterThisRound;
}

int Node::GetNodeId()
{
	return mProperties->mNodeId;
}
