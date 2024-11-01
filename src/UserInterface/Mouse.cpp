//
// Created by cew05 on 01/11/2024.
//

#include "Mouse.h"

bool Mouse::InRect(SDL_Rect* _rect) {
    UpdatePosition();
    return abs(x - (_rect->x + _rect->w / 2)) <= _rect->w / 2 &&
    abs(y - (_rect->y + _rect->h / 2)) <= _rect->h / 2;
}

bool Mouse::UnheldClick(SDL_Rect* _rect) {
    UpdatePosition();
    return active && !heldactive && InRect(_rect);
}

bool Mouse::ClickOnRelease(SDL_Rect* _rect) {
    UpdatePosition();
    return !active && prevactive && InRect(_rect);
}