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
	AIMove GetBestMove(const Graph<T>& graph, int player, int alpha, int beta);





	template <typename T>
	AIMove NEWGetBestMove(const Graph<T>& graph, int player, int alpha, int beta);
	//https://stackoverflow.com/questions/18816088/conversion-of-minimax-with-alpha-beta-pruning-to-negamax


	int Minimax(const AIMove &moveState, int player, int depth, int alpha, int beta);


	//template <typename T>
	//Graph< T>* graph;

	int aiPlayer;
	int humanPlayer;


	Node* lastTestedNode;

};

