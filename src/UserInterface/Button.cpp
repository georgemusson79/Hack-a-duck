//
// Created by cew05 on 01/11/2024.
//

#include "Button.h"

#include "MainWindow.h"
#include "Mouse.h"

void Button::Display() {
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
        fn();
    }
}
