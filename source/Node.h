
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

/*!
* @brief Node class represents cells in the game.
*
* This class is responsible for:
* - Keeping track of its own cell's alive status.
* - Knowing which cells are its neighbors.
* - Requesting which of its neighbors will be alive after a given round.
* - Keeping track of whether its alive status is already checked in a given round.
*
* NodeState Dead/Alive
* - Basic states that determine if the Node is dead/alive by the game rules.
*
* NodeState WaitingForRevive
* - State that is assigned to a Node when it is asked, "IsAliveNextRound()," by its neighbors,
*   and its current state is Dead, but the game rules determine that it should be alive next round.
*
* NodeState WillStayAlive
* - State that is assigned to a Node when it is asked, "IsAliveNextRound()," by its neighbors,
*   and its current state is Alive, and the game rules determine that it should remain alive next round.
*
* NodeState WillStayDead
* - State that is assigned to a Node when it is asked, "IsAliveNextRound()," by its neighbors,
*   and its current state is Dead, and the game rules determine that it should remain dead next round.
*/

class Node : DisableCopy
{
public:
	/*!
	* @brief Default constructor.
	* @param index Unique ID for the Node.
	**/
	Node(int index);

	/*!
	* @brief Default destructor.
	**/
	~Node();

	/*!
	* @brief Initializes Node neighbors.
	* @param neighbors Contains all neighbors for the Node.
	**/
	void Init(std::vector<Node*> neighbors);

	/*!
	* @brief Changes Node's state to the given state.
	* @param state Node's new state.
	**/
	void SetState(NodeState state);

	/*!
	* @brief Gets Node's current state.
	* @return Node's current state.
	**/
	NodeState GetState();

	/*!
	* @brief Determines if Node is alive.
	* @return True/false if Node is alive.
	**/
	bool IsAlive();

	/*!
	* @brief Determines if Node's alive status is already determined in the given round.
	* @param round Determines which round the check is being done against.
	* @return True/false if Node's alive status is already checked.
	**/
	bool IsAlreadyCheckedThisRound(int round);

	/*!
	* @brief Checks which Node's neighbors will be alive in the next round.
	* @param round Determines which round the check is being done against.
	* @return Neighboring Nodes which have not already been checked in the given round and will be alive in the next round.
	**/
	std::vector<Node*> GetAliveNotCheckedNeighboursAfterGivenRound(int round);

	/*!
	* @brief Determines if Node will be alive after the given round and stores that information for future checks.
	* @param round Determines which round the check is being done against.
	* @return True/false if Node will be alive in the next round.
	**/
	bool IsAliveNextRound(int round);

	/*!
	* @brief Returns Node's ID.
	**/
	int GetNodeId();

private:
	NodeProperties* mProperties;
};

#endif // __NODE_H__
