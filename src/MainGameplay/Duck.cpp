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
    SDL_SetRenderDrawColor(window->GetRenderer(), 0, 0, 255, 255);
    SDL_RenderFillRect(window->GetRenderer(), duckRect);
    SDL_SetRenderDrawColor(window->GetRenderer(), 0, 0, 0, 255);

    SDL_RenderCopy(window->GetRenderer(), duckTexture, nullptr, duckRect);
}

Duck* Duck::DuckAtMouse(float _mouseRadius) {
    for (const auto& duck : playerDucks) {
        int x = duck->duckRect->x - mouse->GetPosition().first;
        int y = duck->duckRect->y - mouse->GetPosition().second;

        if (float(x*x) + float(y*y) < _mouseRadius) return duck.get();
    }

    return nullptr;
}

void Duck::PlaceDuck() {
    if (!mouse->IsUnheldActive()) return;

    // is space occupied by another duck?
    if (DuckAtMouse() != nullptr) {
        // highlight duck in red
        // ...
        return;
    }

    // place a duck at the mouse position
    auto [x, y] = mouse->GetPosition();
    std::unique_ptr<Duck> d = std::make_unique<Duck>();
    d->duckRect = new SDL_Rect{x-25, y-25, 50, 50};

    playerDucks.push_back(std::move(d));
}