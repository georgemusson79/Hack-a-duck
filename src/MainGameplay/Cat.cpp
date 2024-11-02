//
// Created by cew05 on 01/11/2024.
//

#include <cmath>
#include "Cat.h"
#include "Player.h"

GenericCat::GenericCat() {
    currPathNode = pathNodes.front().get();
    catRect = new SDL_Rect{currPathNode->GetPosition().x,currPathNode->GetPosition().y,50,50};
    x = catRect->x;
    y = catRect->y;

    auto s = IMG_Load(imgPath.c_str());
    catTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void GenericCat::Display() {
    SDL_Rect displayRect = *catRect;
    displayRect.x -= displayRect.w/2;
    displayRect.h -= displayRect.h/2;
    SDL_RenderCopy(window->GetRenderer(), catTexture, nullptr, &displayRect);
}

void GenericCat::TakeDamage(int dmg) {
    health -= dmg;

    // cat perish
    if (health <= 0) {
        player->AddMoney(1);
    }
}

void GenericCat::MoveToNode(Uint64 _deltaTicks) {
    if (currPathNode == nullptr) return; // end of track

    waitTicks -= _deltaTicks;
    if ((int)waitTicks > 0) return; // YES THE INT IS NECESSARY
    waitTicks = -1;

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

    x += spd * ((int)_deltaTicks / 1000.0) * ((distX < 0) ? -1 : 1);
    y += spd * ((int)_deltaTicks / 1000.0) * ((distY < 0) ? -1 : 1);

    catRect->x = (int)std::round(x);
    catRect->y = (int)std::round(y);

}

void GenericCat::AddDelayBeforeMoving(Uint64 _ticksDelay) {
    waitTicks = _ticksDelay;
}

void GenericCat::MoveToRect(SDL_Rect _rect) {
    catRect->x = _rect.x;
    catRect->y = _rect.y;
    catRect->w = _rect.w;
    catRect->h = _rect.h;
}

void GenericCat::setRotation(double rot) {
//    this->t.rotation = rot;
}