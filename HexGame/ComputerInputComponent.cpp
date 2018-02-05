#include "ComputerInputComponent.h"

#include "Graph.h" 
#include "Player.h"

#include "GameConstants.h"
#include "Pathfinder.h"
#include "HexGameCore.h"

#include <vector>
#include <iostream>

//https://www.youtube.com/watch?v=CwziaVrM_vc



ComputerInputComponent::~ComputerInputComponent() {
}

void ComputerInputComponent::Update(Player & player) {
	//if is turn
	MakeMove(player);
}

void ComputerInputComponent::MakeMove(Player& player) {
	aiPlayer = (int)player.GetColour();

	//TODO: Find a better solution to this. (look at swap player method)
	switch (aiPlayer) {
	case 1:
		humanPlayer = 2;
		break;
	case 2:
		humanPlayer = 1;
		break;
	default:
		break;
	}


	//Graph<T>* graph = player.GetGame()->GetGraph();

	const Graph<HexNode>* graph = HexgameCore::GetInstance().GetGraph();
	//AIMove bestMove = _getBest(*graph, aiPlayer);
	AIMove bestMove = GetBestMove(*graph, aiPlayer);
	player.PlaceNode(bestMove.x, bestMove.y);
}




// Recursively itterates throuugh each state of play, testing all potential moves for each potential future turn
// with the intention of returning the best possible move.
// Some credit goes to MakingGamesWithBen for providing significant insight in how to tackle this challenge.
template <typename T>
AIMove ComputerInputComponent::GetBestMove(const Graph<T>& graph, int player) {

	HexgameCore::GetInstance().GetGraph()->PrintGraph();


	// Hex cannot end in a draw, so only a victory for player 1 and/or for player 2 require testing, otherwise continue recursion
	if (lastTestedNode != nullptr) { // Should only be null on first pass
		Pathfinder pathFinder;

		//std::cout << "Last tested node loc = "<< lastTestedNode->GetCoordinates().X() << ", " << lastTestedNode->GetCoordinates().Y() << std::endl;
		
		bool pathFound = pathFinder.SearchForPath(lastTestedNode, graph.GetMaxX(), graph.GetMaxY());
		if (pathFound) {
			std::cout << "pathfound-" << std::endl;
			if ((int)lastTestedNode->GetOwner() == aiPlayer) {
				std::cout << "cpuWin-" << std::endl;
				return AIMove(10);
			}
			else if ((int)lastTestedNode->GetOwner() == humanPlayer) {
				std::cout << "playerWin-" << std::endl;
				return AIMove(-10);
			}
		}
		else {
			std::cout << "NoPath-" << std::endl;
		}
	}


		// Store the potential moves for this state
	std::vector<AIMove> moves;

	int numberOfEmptyNodes = 0;

	//std::cout << "GetBestMove. Player = " << player << std::endl;
	
	for (int y = 0; y < graph.GetMaxY() +1; y++) {
		for (int x = 0; x < graph.GetMaxX() +1; x++) {

			// If a node has no owner, then consider it for best move
			if (graph.GetNodeOwner(x, y) == NodeOwner::None) {
				numberOfEmptyNodes++;
				//std::cout << "numberOfEmptyNodes = " << numberOfEmptyNodes << std::endl;
				
				AIMove currentMove = AIMove(x, y);

				//graph.SetNodeOwner(x, y, (NodeOwner)player);

				//std::cout << "Player index = " << player << std::endl;

				graph.FindNode(currentMove.x, currentMove.y, lastTestedNode);
				lastTestedNode->ModifyOwner((NodeOwner)player);
				//graph.SetNodeOwner(x, y, (NodeOwner)player );
				
				if (player == aiPlayer) {// The current turn is the aiPlayer's
					currentMove.score = GetBestMove(graph, humanPlayer).score;
				}
				else {	// The current turn is the humanPlayer's
					currentMove.score = GetBestMove(graph, aiPlayer).score;
				}
				
				moves.push_back(currentMove);
				//std::cout << "moves.size = " << moves.size() << std::endl;

				// Reset the graph's node to its previous value
				graph.SetNodeOwner(x, y, NodeOwner::None);
			}
		}
	}
	




	int bestMove = 0;
	if (player == aiPlayer) {
		int bestScore = -10000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		int bestScore = 10000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	//std::cout << "moves.size = " << moves.size() <<  ", x, y = " << moves[bestMove].x << ", " << moves[bestMove].y << std::endl;

	//return AIMove(0,0, 10);
	return moves[bestMove];
}







