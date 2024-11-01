#include "Path.h"
#include "Cat.h"
#include <vector>

Node::Node(Vector2 _nodePos, Node* _lastNode, bool isLast) {
	nodePos = _nodePos;
	isFirstNode = (_lastNode == nullptr);
	isLastNode = isLast; 
	if (_lastNode != nullptr) _lastNode->nextNode = this;
}
/**
 * @brief Chooses a valid move from an array of moves. 
 * 
 * @param currentTile The current tile of the cat.
 **/
// This is here just in case we want to have multiple possible paths :3
// void Path::FindMove(int[] &currentTile) {
// 	int[][] adjacentTiles;
// 	for (int[] tile : adjacentTiles) {
// 		if (tile.collide = true)
// 	}
// }

/**
 * @brief Returns the paths adjacent to the current tile
 *
 * @param &currentTile The current tile of the cat.
 *
 * @return int[][] A 2d array of possible moves.
 **/
