
#include "NodeManager.h"

NodeManager::NodeManager(int boardHeight, int boardWidth)
{
	mBoardHeight = boardHeight;
	mBoardWidth = boardWidth;

	mBoardString = std::string(mBoardHeight * mBoardWidth, 'x');

	CreateNodes();
}

NodeManager::~NodeManager()
{
	for (int i = 0; i < mAliveNodes.size(); ++i)
		mAliveNodes[i] = NULL;

	for (int i = 0; i < mAllNodes.size(); ++i)
	{
		delete(mAllNodes[i]);
		mAllNodes[i] = NULL;
	}
}

std::string NodeManager::GetNodeString()
{
	return mBoardString;
}

void NodeManager::ReviveNode(int x, int y)
{
	int index = x + y * mBoardWidth;
	if (index >= 0 && index < mAllNodes.size() && mAllNodes[index]->GetState() != State::Alive)
	{
		mAllNodes[index]->SetState(State::Alive);
		mAliveNodes.push_back(mAllNodes[index]);
		mBoardString[index] = 'o';
	}
}

void NodeManager::AdvanceRound(int round)
{
	std::vector<Node*> aliveNodesNextRound;
	for (int i = 0; i < mAliveNodes.size(); ++i)
	{
		// Get revivable neighbors from the node
		auto nodes = mAliveNodes[i]->GetRevivableNeighbours(round);
		aliveNodesNextRound.insert(aliveNodesNextRound.end(), nodes.begin(), nodes.end());

		// Then check if the node itself will be alive
		if (mAliveNodes[i]->IsAliveNextRound(round))
			aliveNodesNextRound.push_back(mAliveNodes[i]);
		else
		{
			mAliveNodes[i]->SetState(State::Dead);
			mBoardString[mAliveNodes[i]->GetNodeId()] = 'x';
		}
	}

	for (int i = 0; i < aliveNodesNextRound.size(); ++i)
	{
		aliveNodesNextRound[i]->SetState(State::Alive);
		mBoardString[aliveNodesNextRound[i]->GetNodeId()] = 'o';
	}

	mAliveNodes.clear();
	mAliveNodes = aliveNodesNextRound;
}

// Private
//--------------------------------------

void NodeManager::CreateNodes()
{
	// Init Nodes
	int lastIndex = mBoardHeight * mBoardWidth;
	for (int i = 0; i < lastIndex; ++i)
	{
		auto node = new Node(i);
		mAllNodes.push_back(node);
	}

	// Init neighbours for Nodes
	for (int i = 0; i < mAllNodes.size(); ++i)
	{
		std::vector<Node*> neighbors;
		for (int y = -1; y <= 1; ++y)
		{
			int row = i / mBoardWidth;

			int rowMin = (row + y) * mBoardWidth;
			int rowMax = (row + y) * mBoardWidth + (mBoardWidth - 1);
			for (int x = -1; x <= 1; ++x)
			{
				// Vector index
				int index = i + (y * mBoardWidth) + x;

				// Validity checks for neighbours
				bool indexIsInsideBoard = (index >= 0 && index < lastIndex);
				bool indexIsOnRightRow = (index >= rowMin && index <= rowMax);

				if (indexIsInsideBoard && indexIsOnRightRow)
				{
					bool indexIsNotNodeItself = mAllNodes[index]->GetNodeId() != mAllNodes[i]->GetNodeId();
					if (indexIsNotNodeItself)
						neighbors.push_back(mAllNodes[index]);
				}
			}
		}

		mAllNodes[i]->Init(neighbors);
	}
}