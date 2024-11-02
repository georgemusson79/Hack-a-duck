//
// Created by cew05 on 01/11/2024.
//

#include "Button.h"

#include <utility>

#include "MainWindow.h"
#include "Mouse.h"
#include "TextureManager.h"

Button::Button(std::string imgPath, SDL_Rect dims, std::function<void()> _fn) {
    this->imgPath = imgPath;
    this->clickSound = std::make_unique<Sound>("../resources/clickSFX.wav");
    buttonRect = dims;
    clickRegion = buttonRect;
    fn = std::move(_fn);
}

void Button::Display() {
    if (hide) return;
    SDL_RenderCopy(window->GetRenderer(), tm->GetTexture(imgPath), nullptr, &buttonRect);
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
