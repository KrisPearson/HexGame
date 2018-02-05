#pragma once
#include "InputComponent.h"



class Node;

template <typename T>
class Graph;


struct AIMove {
	AIMove() {};

	AIMove(int score) : score(score) {}

	AIMove(int x, int y) : x(x), y(y) {}

	AIMove(int x, int y, int score) : x(x), y(y), score(score) {}

	int x, y, score;
};

class ComputerInputComponent :
	public InputComponent {
public:

	//template <typename T>
	//ComputerInputComponent(Graph< T>* graph) : graph(graph) {}; 
	ComputerInputComponent() { isHuman = false;  };


	~ComputerInputComponent();

	void Update(Player& player);

	//void MinMax(const class Graph<class Node>& graph);


	void MakeMove(class Player& player);


private:

	template <typename T>
	AIMove GetBestMove(const Graph<T>& graph, int player);


	//template <typename T>
	//Graph< T>* graph;

	int aiPlayer;
	int humanPlayer;


	Node* lastTestedNode;
};

