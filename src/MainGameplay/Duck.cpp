//
// Created by cew05 on 01/11/2024.
//

#include "Duck.h"
#include "../UserInterface/Mouse.h"
#include "../UserInterface/MainWindow.h"

Duck::Duck() {
    duckRect = new SDL_Rect{150,150,50,50};

    auto s = IMG_Load(imgPath.c_str());
    duckTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Duck::Display() {
    if (showRedError) {
        SDL_Rect r = *duckRect;
        r.w *= 2;
        r.h *= 2;
        r.x -= duckRect->w/2;
        r.y -= duckRect->h/2;

        auto s = IMG_Load("../resources/red (1).png");
        auto t = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_RenderCopy(window->GetRenderer(), t, nullptr, &r);
        shoddyTimer++;
        if (shoddyTimer > 50) {
            showRedError = false;
            shoddyTimer = 0;
        }
    }

    SDL_RenderCopy(window->GetRenderer(), duckTexture, nullptr, duckRect);
}


// determine if a cat position is within duck range, and lock on to it
void Duck::FindTarget() {
    for (const auto& cat : cats) {
        int x = cat->catRect->x - duckRect->x + 25;
        int y = cat->catRect->y - duckRect->y + 25;

        if (float(x*x) + float(y*y) < radius*radius){
            target = cat.get();
            printf("QUACK! TARGET FOUND!\n");
            return;
        }
    }
}

Duck* Duck::DuckAtMouse(float _mouseRadius) {
    for (const auto& duck : playerDucks) {
        int x = duck->duckRect->x - mouse->GetPosition().first +25;
        int y = duck->duckRect->y - mouse->GetPosition().second +25;

        printf("dist %d %d\n", x, y);

        if (float(x*x) + float(y*y) < _mouseRadius*_mouseRadius) return duck.get();
    }

    return nullptr;
}

void Duck::PlaceDuck() {
    if (!mouse->IsUnheldActive()) return;

    // is space occupied by another duck?
    Duck* duck;
    if ((duck = DuckAtMouse(50)) != nullptr) {
        duck->showRedError = true;
        return;
    }

    // place a duck at the mouse position
    auto [x, y] = mouse->GetPosition();
    std::unique_ptr<Duck> d = std::make_unique<Duck>();
    d->duckRect = new SDL_Rect{x-25, y-25, 50, 50};

    playerDucks.push_back(std::move(d));
}