#pragma once

#include <vector>
#include "GameConstants.h"

struct Point {
	Point() {};
	Point(int xPos, int yPos) : xPosition(xPos), yPosition(yPos) {}

	inline int X() const { return xPosition;  }
	inline int Y() const  { return yPosition; }

	int xPosition;
	int yPosition;
};





class Node {
public:
	Node(int index, int xPos, int yPos) : index(index), coordinates(Point(xPos, yPos) ) {}
	~Node();

	// Returns the index assigned to the node on instantiation
	inline int GetNodeIndex() const { return index; }

	inline Point GetCoordinates() const { return coordinates; }

	NodeOwner GetOwner() { return currentNodeOwner;  }

#pragma region Public  Virtual Methods

	// Uses multiple indirection (aka 'double' pointer) to assign neighbour before the neighbour has actually been instantiated. 
	virtual inline void AddNeighbour(Node** const newNeighbour) {
		neighbours.push_back(newNeighbour);
	}

	// TODO: Could be made abstract?
	virtual void FindNeighbours(const std::vector<std::vector<Node*> >& graphNodes);

	virtual void PrintNode();

	virtual bool ModifyOwner(NodeOwner newOwner); // TODO: Consider - Could make private/friend of Graph???

	virtual std::vector<Node*const*>  GetAllNeighbours() { return neighbours;  }

#pragma endregion

protected:
	const int index;
	
	const Point coordinates;

	// Stores a list of pointers to node pointers comtained in the owning Graph
	std::vector<Node*const*> neighbours;

	// Stores the current owner(or lack of) of the Node
	NodeOwner currentNodeOwner = NodeOwner::None;

	// Stores the highest x coordinate
	int maxX;
	// Stores the highest y coordinate
	int maxY;
};




class HexNode : public Node {
public:
	HexNode(int index, int xPos, int yPos) : Node(index, xPos, yPos) {}
	~HexNode() {}
	
	// Uses multiple indirection (aka 'double' pointer) to assign neighbour before the neighbour has actually been instantiated. Currently depricated/unused
	virtual inline void AddNeighbour( Node** const newNeighbour) override {
		neighbours.push_back(newNeighbour);
	}

	// Locates all adjacent HexNodes and stores them as neighbours
	using Node::FindNeighbours;
	virtual void FindNeighbours( const std::vector<std::vector<Node*> >& graphNodes) override;

	//Prints the node's character representing it's current owner. Also attempts to emulate the shape of a Hex Board
	virtual void PrintNode() override;


protected: 




};

