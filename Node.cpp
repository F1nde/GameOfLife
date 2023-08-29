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

std::vector<Node*> Node::NewRoundStart(int round)
{
	std::vector<Node*> touchedAliveNodes;

	int aliveNeighbors = 0;
	for (int i = 0; i < mNeighbors.size(); ++i)
	{
		if(mNeighbors[i]->GetState() == State::Alive)
			++aliveNeighbors;

		mNeighbors[i]->TouchNode(round);
	}

	if (aliveNeighbors < 2 || aliveNeighbors > 3)
	{
		// TODO: merkkaa kuolevaksi
	}
}

void Node::TouchNode(int round)
{
	if (mCurrentRound != round)
	{
		mTouches = 0;
		mCurrentRound = round;
	}
	
	++mTouches;
}
