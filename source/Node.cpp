
#include "Node.h"

#include <iostream>
#include <cstddef>

struct NodeProperties
{
	// Node Id in the boardString
	int mNodeId = 0;

	// Current Node state
	NodeState mCurrentState = NodeState::Dead;

	// Neighbor Nodes
	std::vector<Node*> mNeighbors = std::vector<Node*>();

	// Round checks
	int mLastCheckedRound = 0;
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
	if (neighbors.size() != 0)
	{
		for (int i = 0; i < neighbors.size(); ++i)
			mProperties->mNeighbors.push_back(neighbors[i]);
	}
	else
		std::cout << "Error: Neighbors are already defined." << '\n';
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
	if (mProperties->mLastCheckedRound != round)
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
	// If the round numbers match, we already have valid data.
	if (mProperties->mLastCheckedRound != round)
	{
		// NOTE: NodeStates WaitingForRevive and WillStayAlive are cleared by the NodeManager,
		// while WillStayDead is not cleared by the NodeManager, so let's clear it now.
		if (mProperties->mCurrentState == NodeState::WillStayDead)
			mProperties->mCurrentState = NodeState::Dead;

		mProperties->mLastCheckedRound = round;
		mProperties->mIsAliveAfterThisRound = false;

		// Goes trough neighbor Nodes and determines if Node will be
		// will be dead/alive after this round.
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
		}

		// Set the Node's current state to a temporary state that helps the NodeManager
		// determine whether it will stay in its current state or needs to be revived.
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
