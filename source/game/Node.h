
#ifndef __NODE_H__
#define __NODE_H__

#include "DisableCopy.h"

#include <vector>

struct NodeProperties;

enum class NodeState
{
	Dead = 0,
	Alive,
	WaitingForRevive,
	WillStayAlive,
	WillStayDead
};

class Node : DisableCopy
{
public:
	/*!
	* @brief Node constructor
	* @param index Unique id for the Node
	**/
	Node(int index);

	/*!
	* @brief Node destructor
	**/
	~Node();

	/*!
	* @brief Initializes Node neighbors
	* @param neighbors contains all neigbors for the Node
	**/
	void Init(std::vector<Node*> neighbors);

	/*!
	* @brief Changes Node's state to given state
	* @param state Node's new state
	**/
	void SetState(NodeState state);

	/*!
	* @brief Gets Node's current state
	* @return Node's current state
	**/
	NodeState GetState();

	/*!
	* @brief Determines if Node is alive
	* @return true/false if Node is alive
	**/
	bool IsAlive();

	/*!
	* @brief Determines if Node's alive status is already determined in given round
	* @param round determines which round against the check is being done
	* @return true/false if Node's alive status is already checked
	**/
	bool IsAlreadyCheckedThisRound(int round);

	/*!
	* @brief Checks which Node's neighbors will be alive next round
	* @param round determines which round against the check is being done
	* @return returns neighbour Nodes which has not already been checked given round and will be alive next round
	**/
	std::vector<Node*> GetAliveNotCheckedNeighboursAfterGivenRound(int round);

	/*!
	* @brief Determines if Node will be alive after given round and stores that information for future checks
	* @param round determines which round against the check is being done
	* @return true/false if Node will be alive next round
	**/
	bool IsAliveNextRound(int round);

	/*!
	* @brief Returns Node's id
	**/
	int GetNodeId();

private:
	NodeProperties* mProperties;
};

#endif // __NODE_H__
