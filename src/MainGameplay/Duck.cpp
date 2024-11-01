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
    if (!mouse->IsUnheldActive()) return;

    printf("quak!");

    // place a duck at the mouse position

    auto [x, y] = mouse->GetPosition();
    std::unique_ptr<Duck> d = std::make_unique<Duck>();
    d->duckRect = new SDL_Rect{x-25, y-25, 50, 50};

    playerDucks.push_back(std::move(d));
}