//
// Created by cew05 on 01/11/2024.
//

#include "Cat.h"

GenericCat::GenericCat() {
    catRect = new SDL_Rect{200,200,50,50};

    auto s = IMG_Load(imgPath.c_str());
    catTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void GenericCat::Display() {
//    this->t.render();
    SDL_RenderCopy(window->GetRenderer(), catTexture, nullptr, catRect);
}

void GenericCat::setRotation(double rot) {
//    this->t.rotation = rot;
}