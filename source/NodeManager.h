
#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

#include "DisableCopy.h"

#include <string>

struct NodeManagerProperties;

/*!
* @brief NodeManager class works as an intermediate between the Game and Nodes.
* 
* This class is responsible for:
* - Creating and initializing Nodes.
* - Keeping track of which Nodes are currently alive.
* - Maintaining a BoardString that contains information about the current Node statuses.
* - Forwarding information from the Game to Nodes.
*/

class NodeManager : DisableCopy
{
public:
	/*!
	* @brief Default constructor.
	* @param boardWidth Board size in the x direction.
	* @param boardHeight Board size in the y direction.
	**/
	NodeManager(int boardWidth, int boardHeight);

	/*!
	* @brief Default destructor.
	**/
	~NodeManager();

	/*!
	* @brief Gets a string that reflects the current node statuses.
	* @return Current board status as a string.
	**/
	std::string GetNodeString();

	/*!
	* @brief Tries to set a Node alive using given coordinates. If invalid coordinates, nothing happens.
	* @param x X-coordinate for the Node.
	* @param y Y-coordinate for the Node.
	**/
	void ReviveNode(int x, int y);

	/*!
	* @brief Reacts to the advancement of a game round.
	* @param round New round number.
	**/
	void AdvanceRound(int round);

private:
	/*!
	* @brief Creates Nodes and initializes their neighbors.
	**/
	void CreateNodes();

	NodeManagerProperties* mProperties;
};

#endif // __NODEMANAGER_H__
