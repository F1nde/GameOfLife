
#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

#include "DisableCopy.h"

#include <string>

struct NodeManagerProperties;

class NodeManager : DisableCopy
{
public:
	/*!
	* @brief NodeManager constructor
	* @param boardWidth board size in x direction
	* @param boardHeight board size in y direction
	**/
	NodeManager(int boardWidth, int boardHeight);

	/*!
	* @brief NodeManager destructor
	**/
	~NodeManager();

	/*!
	* @brief Gets string that reflects current node statuses
	* @return current board status as a string
	**/
	std::string GetNodeString();

	/*!
	* @brief Tries to set Node alive using given cordinates. If invalid cordinates -> nothing happens
	* @param x x-cordinate for the Node.
	* @param y y-cordinate for the Node.
	**/
	void ReviveNode(int x, int y);

	/*!
	* @brief Reacts to game round advancement.
	* @param round new round number.
	**/
	void AdvanceRound(int round);

private:
	/*!
	* @brief Creates Nodes and inits their neighbours
	**/
	void CreateNodes();

	NodeManagerProperties* mProperties;
};

#endif // __NODEMANAGER_H__
