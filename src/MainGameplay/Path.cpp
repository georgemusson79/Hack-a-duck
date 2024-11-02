#include "Path.h"

Node::Node(Vector2 _nodePos, Node* _lastNode, bool isLast) {
    nodePos = _nodePos;
    isFirstNode = (_lastNode == nullptr);
    isLastNode = isLast;
    if (_lastNode != nullptr) {
        _lastNode->nextNode = this;
        _lastNode->generateTextures();
    }
}
