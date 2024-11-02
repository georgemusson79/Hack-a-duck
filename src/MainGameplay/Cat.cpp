//
// Created by cew05 on 01/11/2024.
//

#include <cmath>
#include "Cat.h"
#include "Player.h"

GenericCat::GenericCat() {
    catRect = new SDL_Rect{200,200,50,50};
    x = 200;
    y = 200;
    currPathNode = pathNodes.front().get();

    auto s = IMG_Load(imgPath.c_str());
    catTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void GenericCat::Display() {
//    this->t.render();
    SDL_RenderCopy(window->GetRenderer(), catTexture, nullptr, catRect);
}

void GenericCat::TakeDamage(int dmg) {
    health -= dmg;

    // cat perish
    if (health <= 0) {

    }
}

void GenericCat::MoveToNode() {
    if (currPathNode == nullptr) return; // end of track

    int distX = currPathNode->GetPosition().x - catRect->x;
    int distY = currPathNode->GetPosition().y - catRect->y;

    if (std::abs(distX) < 2 && std::abs(distY) < 2 ) {
        // has reached current node, select next node, if end node
        if (currPathNode->GetNextNode() == nullptr) {
            // END NODE TAKE LIFE
            player->TakeDamage(health);
            currPathNode = nullptr;
            return;
        }

        // otherwise continue to next node
        currPathNode = currPathNode->GetNextNode();
    }

    x += spd * ((distX < 0) ? -1 : 1);
    y += spd * ((distY < 0) ? -1 : 1);

    catRect->x = (int)x;
    catRect->y = (int)y;
}

void GenericCat::setRotation(double rot) {
//    this->t.rotation = rot;
}