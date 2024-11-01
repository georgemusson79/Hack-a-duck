


#ifndef PATHHEADER_H
#define PATHHEADER_H

#include "Vector2.h"

// Each Tile is 20x20, making a 50x50 grid.
class Node {
    private:
        Vector2 nodePos;
        Node* nextNode;
        bool isLastNode;
        bool isFirstNode;

    public:
        Node(Vector2 _nodePos, Node* _lastNode, bool isLast);
        [[nodiscard]] Node* GetNextNode() const { return nextNode; };
};

#endif