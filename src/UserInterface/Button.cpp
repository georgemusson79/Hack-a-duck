//
// Created by cew05 on 01/11/2024.
//

#include "Button.h"

#include <utility>

#include "MainWindow.h"
#include "Mouse.h"

Button::Button(std::string imgPath, SDL_Rect dims, std::function<void()> _fn) {
    this->imgPath = imgPath;
    this->clickSound = std::make_unique<Sound>("../resources/clickSFX.wav");
    buttonRect = dims;
    clickRegion = buttonRect;
    fn = std::move(_fn);

    auto s = IMG_Load(imgPath.c_str());
    buttonTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Button::Display() {
    if (hide) return;
    SDL_RenderCopy(window->GetRenderer(), buttonTexture, nullptr, &buttonRect);
}

void Button::CheckClick() {
    // hovering
    bool hover = mouse->InRect(&clickRegion);
    if (!hover) return;

    clicked = false;

    // mousedown over the button
    if (mouse->IsUnheldActive()) {
        clicked = true;
        this->clickSound->play();
        fn();
    }
}
