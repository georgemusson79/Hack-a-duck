//
// Created by cew05 on 01/11/2024.
//

#include "Button.h"
#include "Mouse.h"

Button::Button() {

}

void Button::CheckClick() {
    // hovering
    bool hover = mouse->InRect(clickRegion);
    if (!hover) return;

    clicked = false;

    // mousedown over the button
    if (mouse->IsUnheldActive()) {
        clickStarted = true;
    }

    // mousedown released, over the button
    if (clickStarted && mouse->ClickOnRelease(buttonRect)) {
        clickStarted = false;
        clicked = true;
    }

    // mousedown released, not over button
    if (clickStarted && !mouse->IsHeldActive()) clickStarted = false;
}