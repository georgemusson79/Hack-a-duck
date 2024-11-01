//
// Created by cew05 on 01/11/2024.
//

#include "Duck.h"
#include "../UserInterface/MainWindow.h"
#include "../UserInterface/Mouse.h"

Duck::Duck() {
    duckRect = new SDL_Rect{150,150,50,50};

    auto s = IMG_Load(imgPath.c_str());
    duckTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Duck::Display() {
    SDL_RenderCopy(window->GetRenderer(), duckTexture, nullptr, duckRect);
}

void Duck::PlaceDuck() {
    // place a duck at the mouse position


}