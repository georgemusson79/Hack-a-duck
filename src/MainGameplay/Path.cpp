#include "Path.h"

Node::Node(Vector2 _nodePos, Node* _lastNode, bool isLast) {
    nodePos = _nodePos;
    isFirstNode = (_lastNode == nullptr);
    isLastNode = isLast;
    if (_lastNode != nullptr) _lastNode->nextNode = this;
    double rotation = rand() % 360;
    std::vector<std::string> pngs = {"pad.png", "lilypad.png", "cluster.png"};
    std::string png = "resources/" + pngs[rand() % 3];
    t = Texture(png, this->nodePos.x, this->nodePos.y, this->w, this->h);
    t.rotation = rotation;
}
