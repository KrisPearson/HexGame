#include "Node.h"

#include <string>
#include <assert.h> 
#include <iostream>



//TODO: Consider how best to connect sprite object to Node. Could Sprite contain a reference to its Node and so retireve it's location and state for representation?

using namespace std;


Node::~Node() {

}

void Node::FindNeighbours( const std::vector<std::vector<Node*>>& graphNodes) {
	assert(false && "Node::FindNeighbours() has no defined functionality");
}

void Node::PrintNode() {
	assert(false  && "Node::PrintNode() has no defined functionality");
}

// Changes the owner of the node to the newOwner
bool Node::ModifyOwner(NodeOwner newOwner) { 
	if (newOwner != currentNodeOwner) {
		currentNodeOwner = newOwner;
		return true;
	}
	else return false;
}



void HexNode::FindNeighbours( const std::vector<std::vector<Node*>>& graphNodes) {

	// TODO: Find a better wat to share the "maxX/Y" coordinates (a static point/ integers perhaps?)

	//TODO: Developed a refiend approach to the following code, rather than "bute-force" it

	const int x = coordinates.X();
	const int y = coordinates.Y();

	// Get x and y size of the graph
	maxX = graphNodes.back().back()->GetCoordinates().X();
	maxY = graphNodes.back().back()->GetCoordinates().Y();

	if (x == 0) { // Left side
		if (y == 0) { //Top left corner
			neighbours.push_back(&graphNodes[x + 1][y]);
			neighbours.push_back(&graphNodes[x][y + 1]);
		}
		else if (y == maxY) { // Bottom Left Corner
			neighbours.push_back(&graphNodes[x][y - 1]);
			neighbours.push_back(&graphNodes[x + 1][y - 1]);
			neighbours.push_back(&graphNodes[x + 1][y]);
		}
		else { // Left Side
			neighbours.push_back(&graphNodes[x][y - 1]);
			neighbours.push_back(&graphNodes[x + 1][y - 1]);
			neighbours.push_back(&graphNodes[x + 1][y]);
			neighbours.push_back(&graphNodes[x][y + 1]);
		}
	}
	else if (x == maxX) { // Right Side
		if (y == 0) { //Top Right corner
			neighbours.push_back(&graphNodes[x][y +1]);
			neighbours.push_back(&graphNodes[x - 1][y + 1]);
			neighbours.push_back(&graphNodes[x - 1][y]);
		}
		else if (y == maxY) { // Bottom Right Corner
			neighbours.push_back(&graphNodes[x][y - 1]);
			neighbours.push_back(&graphNodes[x - 1][y]);
		}
		else { // Right Side		
			neighbours.push_back(&graphNodes[x][y - 1]);
			neighbours.push_back(&graphNodes[x][y + 1]);
			neighbours.push_back(&graphNodes[x - 1][y + 1]);
			neighbours.push_back(&graphNodes[x - 1][y]);
			
		}
	}
	else if (y == 0) { // Top Side	
		neighbours.push_back(&graphNodes[x +1 ][y]);
		neighbours.push_back(&graphNodes[x][y + 1]);
		neighbours.push_back(&graphNodes[x -1 ][y + 1]);
		neighbours.push_back(&graphNodes[x - 1][y]);	
	}
	else if (y == maxY) { //Bottom Side
		
		neighbours.push_back(&graphNodes[x + 1][y]);
		neighbours.push_back(&graphNodes[x - 1][y]);
		neighbours.push_back(&graphNodes[x][y - 1]);
		neighbours.push_back(&graphNodes[x + 1][y - 1]);
		
	}
	else { // Centre Node
		neighbours.push_back(&graphNodes[x][y - 1]);
		neighbours.push_back(&graphNodes[x + 1][y - 1]);
		neighbours.push_back(&graphNodes[x + 1][y]);
		neighbours.push_back(&graphNodes[x][y + 1]);
		neighbours.push_back(&graphNodes[x - 1][y + 1]);
		neighbours.push_back(&graphNodes[x - 1][y]);	
	}
}


void HexNode::PrintNode() {
	if (coordinates.xPosition == 0) { // Start of Row
		string stuff(coordinates.yPosition, ' ');
		cout << stuff << coordinates.yPosition << "-";
	}

	cout << nodeSymbols[(int)currentNodeOwner];

	if (coordinates.xPosition == maxX) { // Start a new row // TODO: GET XMAX
		cout << endl;
	}

}
