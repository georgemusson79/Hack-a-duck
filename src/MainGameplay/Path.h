

#ifndef PATHHEADER_H
#define PATHHEADER_H

#include <memory>
#include <vector>

#include "../UserInterface/Texture.h"
#include "Vector2.h"

// Each Tile is 20x20, making a 50x50 grid.
class Node {
   private:
    Texture* t;
    Vector2 nodePos;
    std::vector<Texture*> toNextNode = {};
    Node* nextNode;
    bool isLastNode;
    bool isFirstNode;
    int w = 1000 / 20;
    int h = 1000 / 20;

   public:
    void generateTextures() {
        std::vector<std::string> pngs = {"pad.png", "lilypad.png", "cluster.png"};
        std::string png = "../resources/" + pngs[rand() % 3];
        this->t = new Texture(png, this->nodePos.x, this->nodePos.y, this->w, this->h);
        double rotation = rand() % 360;
        this->t->rotation = rotation;
        if (!this->isLastNode && this->nextNode) {
            int spaceX = this->nextNode->nodePos.x - this->nodePos.x;
            int spaceY = this->nextNode->nodePos.y - this->nodePos.y;

            bool xFinished = false;
            bool yFinished = false;
            int y = std::min(this->nextNode->nodePos.y, this->nodePos.y);
            int x = std::min(this->nextNode->nodePos.x, this->nodePos.x);
            while (!xFinished || !yFinished) {
                if (x < std::max(this->nextNode->nodePos.x, this->nodePos.x)) {
                    x += this->w;
                } else {
                    xFinished = true;
                }
                if (y + this->h < std::max(this->nextNode->nodePos.y, this->nodePos.y)) {
                    y += h;
                } else {
                    yFinished = true;
                }

                if (xFinished && yFinished) break;

                double rotation = rand() % 360;
                std::vector<std::string> pngs = {"pad.png", "lilypad.png", "cluster.png"};
                std::string png = "../resources/" + pngs[rand() % 3];
                this->toNextNode.push_back(new Texture(png, x, y, this->w, this->h));
            }
        }
    }

    Node(Vector2 _nodePos, Node* _lastNode, bool isLast = false);

    [[nodiscard]] Node* GetNextNode() const { return nextNode; };
    [[nodiscard]] bool LastNode() const { return isLastNode; }
    [[nodiscard]] Vector2 GetPosition() const { return nodePos; };

    void render() {
        t->render();
        for (Texture* t : this->toNextNode) t->render();
    }
};

inline std::vector<std::unique_ptr<Node>> pathNodes;

inline void SetupPath() {
    pathNodes.clear();

    // Populate the path nodes
    pathNodes.push_back(std::make_unique<Node>(Vector2{-100, 700}, nullptr));
    pathNodes.push_back(std::make_unique<Node>(Vector2{500, 700}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{680, 570}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{750, 500}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{750, 400}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{680, 350}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{580, 350}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{200, 425}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{75, 375}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{75, 250}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{225, 150}, pathNodes.back().get()));
    pathNodes.push_back(std::make_unique<Node>(Vector2{800, 150}, pathNodes.back().get(), true));
}

#endif