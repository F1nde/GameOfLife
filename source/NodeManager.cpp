
#include "NodeManager.h"
#include "Node.h"

struct NodeManagerProperties
{
	int mBoardHeight = 0;
	int mBoardWidth = 0;
	std::string mBoardString = "";

	std::vector<Node*> mAllNodes;
	std::vector<Node*> mAliveNodes;
};

NodeManager::NodeManager(int boardWidth, int boardHeight)
{
	mProperties = new NodeManagerProperties;

	mProperties->mBoardHeight = boardHeight;
	mProperties->mBoardWidth = boardWidth;

	int boardStringLenght = mProperties->mBoardHeight * mProperties->mBoardWidth;
	mProperties->mBoardString = std::string(boardStringLenght, 'x');

	CreateNodes();
}

NodeManager::~NodeManager()
{
	for (int i = 0; i < mProperties->mAliveNodes.size(); ++i)
		mProperties->mAliveNodes[i] = NULL;

	for (int i = 0; i < mProperties->mAllNodes.size(); ++i)
	{
		delete(mProperties->mAllNodes[i]);
		mProperties->mAllNodes[i] = NULL;
	}

	delete(mProperties);
	mProperties = NULL;
}

std::string NodeManager::GetNodeString()
{
	return mProperties->mBoardString;
}

void NodeManager::ReviveNode(int x, int y)
{
	int index = x + y * mProperties->mBoardWidth;
	if (index >= 0 && index < mProperties->mAllNodes.size() && mProperties->mAllNodes[index]->GetState() != NodeState::Alive)
	{
		mProperties->mAllNodes[index]->SetState(NodeState::Alive);
		mProperties->mAliveNodes.push_back(mProperties->mAllNodes[index]);
		mProperties->mBoardString[index] = 'o';
	}
}

void NodeManager::AdvanceRound(int round)
{
	std::vector<Node*> aliveNodesNextRound;
	for (int i = 0; i < mProperties->mAliveNodes.size(); ++i)
	{
		// Get revivable neighbors from the node
		auto nodes = mProperties->mAliveNodes[i]->GetAliveNotCheckedNeighboursAfterGivenRound(round);
		aliveNodesNextRound.insert(aliveNodesNextRound.end(), nodes.begin(), nodes.end());

		// Then check if the node itself will be alive
		if (mProperties->mAliveNodes[i]->IsAliveNextRound(round))
			aliveNodesNextRound.push_back(mProperties->mAliveNodes[i]);
		else
		{
			mProperties->mAliveNodes[i]->SetState(NodeState::Dead);
			mProperties->mBoardString[mProperties->mAliveNodes[i]->GetNodeId()] = 'x';
		}
	}

	for (int i = 0; i < aliveNodesNextRound.size(); ++i)
	{
		aliveNodesNextRound[i]->SetState(NodeState::Alive);
		mProperties->mBoardString[aliveNodesNextRound[i]->GetNodeId()] = 'o';
	}

	mProperties->mAliveNodes.clear();
	mProperties->mAliveNodes = aliveNodesNextRound;
}

// Private
//--------------------------------------

void NodeManager::CreateNodes()
{
	// Init Nodes
	int lastIndex = mProperties->mBoardHeight * mProperties->mBoardWidth;
	for (int i = 0; i < lastIndex; ++i)
	{
		auto node = new Node(i);
		mProperties->mAllNodes.push_back(node);
	}

	// Init neighbours for Nodes
	for (int i = 0; i < mProperties->mAllNodes.size(); ++i)
	{
		std::vector<Node*> neighbors;
		for (int y = -1; y <= 1; ++y)
		{
			int row = i / mProperties->mBoardWidth;

			int rowMin = (row + y) * mProperties->mBoardWidth;
			int rowMax = (row + y) * mProperties->mBoardWidth + (mProperties->mBoardWidth - 1);
			for (int x = -1; x <= 1; ++x)
			{
				// Vector index
				int index = i + (y * mProperties->mBoardWidth) + x;

				// Validity checks for neighbours
				bool indexIsInsideBoard = (index >= 0 && index < lastIndex);
				bool indexIsOnRightRow = (index >= rowMin && index <= rowMax);

				if (indexIsInsideBoard && indexIsOnRightRow)
				{
					bool indexIsNotNodeItself = mProperties->mAllNodes[index]->GetNodeId() != mProperties->mAllNodes[i]->GetNodeId();
					if (indexIsNotNodeItself)
						neighbors.push_back(mProperties->mAllNodes[index]);
				}
			}
		}

		mProperties->mAllNodes[i]->Init(neighbors);
	}
}