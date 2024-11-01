//
// Created by cew05 on 01/11/2024.
//

#include "Button.h"

#include "MainWindow.h"
#include "Mouse.h"

void Button::Display() {
    SDL_RenderCopy(window->GetRenderer(), buttonTexture, nullptr, buttonRect);
}

void Button::CheckClick() {
    // hovering
    bool hover = mouse->InRect(clickRegion);
    if (!hover) return;

    clicked = false;

    // mousedown over the button
    if (mouse->IsUnheldActive()) {
        clicked = true;
    }
}
Button::Button(std::string imgPath, SDL_Rect dims) {
    this->imgPath = imgPath;
    buttonRect = new SDL_Rect{0, 0, 50, 50};
    clickRegion = buttonRect;

    auto s = IMG_Load(imgPath.c_str());
    buttonTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}
