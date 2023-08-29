#include "NodeManager.h"

NodeManager::NodeManager(int boardHeight, int boardWidth)
{
	/*
	for (int i = 0; i < boardHeight; ++i)
	{
		std::vector<Node*> row(boardWidth);
		mAllNodes.push_back(row);
	}

	// Create Nodes
	int lastIndex = boardHeight * boardWidth;
	int index = 0;
	for (int y = 0; y < boardHeight; ++y)
	{
		for (int x = 0; x < boardWidth; ++x)
		{
			auto node = new Node(index);
			mAllNodes[y][x] = node;
			++index;
		}
		//auto node = new Node(i);
		//mAllNodes.push_back(node);
	}
	*/

	// Create Nodes
	int lastIndex = boardHeight * boardWidth;
	for (int i = 0; i < lastIndex; ++i)
	{
		auto node = new Node(i);
		mAllNodes.push_back(node);
	}

	for (int i = 0; i < mAllNodes.size(); ++i)
	{
		std::vector<Node*> neighbors;
		for (int y = -1; y <= 1; ++y)
		{
			int row = i / boardWidth;

			int rowMin = (row + y) * boardWidth;
			int rowMax = (row + y) * boardWidth + (boardWidth - 1);
			for (int x = -1; x <= 1; ++x)
			{
				//int index = x + y * mHeight;

				int index = i + (y * boardWidth) + x;
				if ((index >= 0 && index < lastIndex)
					&& (index >= rowMin && index <= rowMax)
					&& mAllNodes[index]->GetIndex() != mAllNodes[i]->GetIndex())
				{
					neighbors.push_back(mAllNodes[index]);
				}

				//// int index = x + y * mHeight;
				//int index = i + (y * std::max(3, boardWidth)) + x;
				//lastIndex = (mAllNodes.size() / boardWidth)

				//if (index >= 0 && index < lastIndex &&
				//	mAllNodes[index]->GetIndex() != mAllNodes[i]->GetIndex())
				//{
				//	neighbors.push_back(mAllNodes[index]);
				//}
			}
		}

		mAllNodes[i]->Init(neighbors);
	}

	// Init neighbors
	//for (int i = 0; i < mAllNodes.size(); ++i)
	//{
	//	std::vector<Node*> neighbors;
	//	for (int y = -1; y <= 1; ++y)
	//	{
	//		for (int x = -1; x <= 1; ++x)
	//		{
	//			int index = i + (y * std::max(3, boardWidth)) + x;
	//			if (index >= 0 && index < lastIndex &&
	//				mAllNodes[index]->GetIndex() != mAllNodes[i]->GetIndex())
	//			{
	//				neighbors.push_back(mAllNodes[index]);
	//			}
	//		}
	//	}

	//	mAllNodes[i]->Init(neighbors);
	//}

	mHeight = boardHeight;
	mWidth = boardWidth;

	mBoardString = std::string(mHeight * mWidth, 'x');
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
	int index = x + y * mWidth;
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
		auto nodes = mAliveNodes[i]->GetRevivableNeighbours(round);
		aliveNodesNextRound.insert(aliveNodesNextRound.end(), nodes.begin(), nodes.end());

		if (mAliveNodes[i]->IsAliveNextRound(round))
			aliveNodesNextRound.push_back(mAliveNodes[i]);
		else
		{
			mAliveNodes[i]->SetState(State::Dead);
			mBoardString[mAliveNodes[i]->GetIndex()] = 'x';
		}
	}

	for (int i = 0; i < aliveNodesNextRound.size(); ++i)
	{
		aliveNodesNextRound[i]->SetState(State::Alive);
		mBoardString[aliveNodesNextRound[i]->GetIndex()] = 'o';
	}

	mAliveNodes = aliveNodesNextRound;
}
