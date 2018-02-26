#pragma once
#include <vector>
#include "GameConstants.h"

class Node;

class Pathfinder {
public:
	Pathfinder() {};
	~Pathfinder() {};

	// Searches for a path from one edge to the opposite edge itteratirng through neighbours 
	// of each linked node beginning from the given node using said node's owner.
	bool SearchForPath(class Node* startNode, int maxX, int maxY);

private:
	bool closedSet[MAX_NODE_COUNT] = { 0 }; //Determines whether the node has been visited or not
};

