#include "Node.h"

Node::Node(/*Game* game,*/ int index)
{
	mIndex = index;
	mCurrentState = State::Dead;
	mNeighbors = std::vector<Node*>();

	mTouches = 0;
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

// TODO:
// Koskettele naapureita ja palauta lista henkiin her‰‰vist‰
// Kun tehty kaikille -> Tarkasta viel‰ onko mik‰‰n nykyisist‰ kuollut

//std::vector<Node*> Node::NewRoundStart(int round)
//{
//	std::vector<Node*> touchedAliveNodes;
//
//	int aliveNeighbors = 0;
//	for (int i = 0; i < mNeighbors.size(); ++i)
//	{
//		if(mNeighbors[i]->GetState() == State::Alive)
//			++aliveNeighbors;
//
//		mNeighbors[i]->TouchNode(round);
//	}
//
//	if (aliveNeighbors < 2 || aliveNeighbors > 3)
//	{
//		// TODO: merkkaa kuolevaksi
//	}
//}

void Node::TouchNode(int round)
{
	if (mCurrentRound != round)
	{
		mTouches = 0;
		mCurrentRound = round;
	}
	
	++mTouches;
}

std::vector<Node*> Node::GetRevivableNeighbours(int round)
{
	std::vector<Node*> touchedAliveNodes;

	//int aliveNeighbors = 0;
	for (int i = 0; i < mNeighbors.size(); ++i)
	{
		if (mNeighbors[i]->GetState() != State::WaitingForRevive)
		{
			bool alive = mNeighbors[i]->IsAliveNextRound(round);
			if (alive)
				touchedAliveNodes.push_back(mNeighbors[i]);

			//++aliveNeighbors;
			//mNeighbors[i]->TouchNode(round);
		}
	}

	return touchedAliveNodes;

	//if (aliveNeighbors < 2 || aliveNeighbors > 3)
	//{
	//	// TODO: merkkaa kuolevaksi
	//}
}

bool Node::IsAliveNextRound(int round)
{
	if (mCurrentRound != round)
	{
		//mTouches = 0;
		mCurrentRound = round;
		mIsAliveAfterThisRound = false;

		int aliveNeighbors = 0;
		for (int i = 0; i < mNeighbors.size(); ++i)
		{
			if (mNeighbors[i]->GetState() == State::Alive)
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
	}

	return mIsAliveAfterThisRound;
}

int Node::GetIndex()
{
	return mIndex;
}
