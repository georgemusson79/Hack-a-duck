

#ifndef PATHHEADER_H
#define PATHHEADER_H

#include <memory>
#include <vector>

#include "Vector2.h"

// Each Tile is 20x20, making a 50x50 grid.
class Node {
   private:
    Vector2 nodePos;
    Node* nextNode;
    bool isLastNode;
    bool isFirstNode;

   public:
    Node(Vector2 _nodePos, Node* _lastNode, bool isLast = false);
    [[nodiscard]] Node* GetNextNode() const { return nextNode; };
    [[nodiscard]] Vector2 GetPosition() const { return nodePos; };
    void display() {
        }
};

inline std::vector<std::unique_ptr<Node>> pathNodes;

inline void SetupPath() {
    pathNodes.clear();

    // Populate the path nodes
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 750}, nullptr));
    pathNodes.push_back(std::make_unique<Node>(Vector2{250, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{280, 700}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{300, 680}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{350, 650}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{410, 610}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{510, 500}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{570, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{600, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{630, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{660, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{690, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 750}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 750}, pathNodes.back().get(), true));
}

#endif