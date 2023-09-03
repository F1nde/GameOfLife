
#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

#include "Node.h"

#include <string>
#include <vector>

class NodeManager
{
public:
	NodeManager(int boardHeight, int boardWidth);
	~NodeManager();

	/*!
	* \brief Rakentaja kortin, jossa on annettu kuva, linkkitietorakenne ja tieto kortin varista
	* \param pic Korttiin asetettava QPixmap kuva
	* \param links Kortin reiteista kertova linkkitietorakenne
	* \param col Korttiin asetettavan nappulan vari
	* \pre links.size() == 4
	**/
	std::string GetNodeString();

	void ReviveNode(int x, int y);
	void AdvanceRound(int round);

private:
	void CreateNodes();

	int mBoardHeight;
	int mBoardWidth;
	std::string mBoardString = "";

	std::vector<Node*> mAllNodes;
	std::vector<Node*> mAliveNodes;
};

#endif // __NODEMANAGER_H__
