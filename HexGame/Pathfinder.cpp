#include "Pathfinder.h"
#include "Node.h"
#include <queue>







using namespace std;

// Searches for a path from one edge to the opposite edge itteratirng through neighbours 
// of each linked node beginning from the given node using said node's owner.
bool Pathfinder::SearchForPath(Node * startNode, int maxX, int maxY ) {



	const NodeOwner ownerToFind = startNode->GetOwner();

	// Contains the nodes that require checking
	priority_queue<Node*> openSet;

	// Stores visited nodes foe final check to see whether a path has been found 
	vector<Node*> visistedNodes;

	openSet.push(startNode); // At the start Node to the openSet as the first Node to visit

	while (!openSet.empty()) {
		Node* currentNode = openSet.top();
		openSet.pop();

		const int currentNodeIndex = currentNode->GetNodeIndex();

		if (closedSet[currentNodeIndex]) continue; // If the Node is already in the closedSet then skip it		
		else {
			visistedNodes.push_back(currentNode); // Add the node to the visitedNodes set 
			closedSet[currentNodeIndex] = true; // Add the Node to the closedSet
		}

		// Get all neighbours owned by the ownerToFind
		vector<Node*const*> neighbours = currentNode->GetAllNeighbours();
		for (Node*const* n : neighbours) {
			if ((*n)->GetOwner() == ownerToFind) {
				openSet.push(*n);
			}
		}
	}

	// Check to see whether both edges have been reached  by itterating through all visited nodes and checking their location
	bool startNodeReached = false, endNodeReached = false;
	for (Node* n : visistedNodes) {
		if ((int)ownerToFind == (int)NodeOwner::Blue) {
			if (n->GetCoordinates().X() == 0) {
				startNodeReached = true;
			}
			else if (n->GetCoordinates().X() == maxX) {
				endNodeReached = true;
			}

		}
		else if (ownerToFind == NodeOwner::Red) {
			if (n->GetCoordinates().Y() == 0) {
				startNodeReached = true;
			}
			else if (n->GetCoordinates().Y() == maxY) {
				endNodeReached = true;
			}
		}

		// Escape loop early if both start and end have been found
		if (startNodeReached && endNodeReached) return startNodeReached && endNodeReached;
	}



	return startNodeReached && endNodeReached;
}
