#pragma once
#include <algorithm> 
#include <iterator>
#include <iostream> //TEMP?
#include <vector>
#include <type_traits>

#include "Node.h"

#pragma region GraphHeader

template <class T>
class Graph {
public:
	Graph(int size);
	~Graph();

	void PrintGraph();

	bool FindNode(int xPosition, int yPosition, Node*& returnNodeRef) const ;

	int GetMaxX() const;

	int GetMaxY() const;

	NodeOwner GetNodeOwner(int x, int y) const;

	bool SetNodeOwner(int x, int y, NodeOwner newOwner) const;

	//int CheckVictory()

protected: 
	std::vector<std::vector<Node*  > > nodes;

	void DeleteNodeData();
};

#pragma endregion


#pragma region GraphImplementation

template <class T>
Graph<T>::Graph(int size) {

	static_assert(std::is_base_of<Node, T>::value, "type parameter of this class must derive from Node");

	nodes.resize(size, std::vector<Node*>(size));

	int nodeIndex = 0;
	// Hex 0,0 will be the top left corner - while hex size-1,size-1 will be the bottom right corner.  
	for (int y = 0; y < size; y++) {		
		for (int x = 0; x < size; x++) {
			T *newNode = new T(nodeIndex, x, y); //we use i so that each Node possesses a unique index
			nodes[x][y] = newNode; // add the new node to the nodes vector
			nodeIndex++;
		}
	}

	std::vector< std::vector<Node*> >::iterator xIt = nodes.begin();
	std::vector< std::vector<Node*> >::iterator xItEnd = nodes.end();
	for (; xIt != xItEnd; ++xIt) {
		std::vector<Node*>::iterator yIt = xIt->begin();
		std::vector<Node*>::iterator yItEnd = xIt->end();
		for (; yIt != yItEnd; ++yIt) {
			(*yIt)->FindNeighbours(nodes);
		}
	}
}



template <class T>
Graph<T>::~Graph() {
	DeleteNodeData();
}

template<class T>
inline void Graph<T>::PrintGraph() {
	const int sizeX = nodes.size();
	const int sizeY = nodes[0].size();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			nodes[x][y]->PrintNode();
		}
	}
}

template<class T>
inline bool Graph<T>::FindNode(int xPosition, int yPosition, Node*& returnNodeRef) const {
	if (xPosition < nodes.size() && yPosition < nodes[xPosition].size()) { // check if positin is within range
		if (&returnNodeRef != nullptr) {
			returnNodeRef = nodes[xPosition][yPosition];
			return true;
		}
		else return false;
	}
	else return false;
}

// Returns the X value of the final node (bottom right corner) 
template<class T>
inline int Graph<T>::GetMaxX() const {
	return nodes.back().back()->GetCoordinates().X();
}

// Returns the Y value of the final node (bottom right corner) 
template<class T>
inline int Graph<T>::GetMaxY() const {
	return nodes.back().back()->GetCoordinates().Y();
}

template <class T>
void Graph<T>::DeleteNodeData() {
	std::vector< std::vector<Node*> >::iterator xIt = nodes.begin();
	std::vector< std::vector<Node*> >::iterator xItEnd = nodes.end();
	for (; xIt != xItEnd; ++xIt) {
		std::vector<Node*>::iterator yIt = xIt->begin();
		std::vector<Node*>::iterator yItEnd = xIt->end();
		for (; yIt != yItEnd; ++yIt) {
			delete (*yIt);
		}
	}
}


template <class T>
NodeOwner Graph<T>::GetNodeOwner(int x, int y) const {
	// TODO: Perform safety check
	return nodes[x][y]->GetOwner();
}


template <class T>
bool Graph<T>::SetNodeOwner(int x, int y, NodeOwner newOwner) const {
	return nodes[x][y]->ModifyOwner(newOwner);
}
#pragma endregion
