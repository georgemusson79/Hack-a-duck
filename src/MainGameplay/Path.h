


#ifndef PATHHEADER_H
#define PATHHEADER_H

#include "Vector2.h"

// Each Tile is 20x20, making a 50x50 grid.
class Node {
	Vector2 nodePos;
	Node *nextNode;
	bool isLastNode;
};

#endif