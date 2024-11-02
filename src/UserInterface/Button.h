//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_BUTTON_H
#define HACK_A_DUCK_BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <functional>
#include <string>

#include "MainWindow.h"
#include "Sound.h"

class Button {
   private:
    SDL_Rect clickRegion{};
    SDL_Rect buttonRect{};
    std::unique_ptr<Sound> clickSound;

    std::string imgPath = "../resources/StartButten.png";
    std::function<void()> fn;

    bool clicked = false;
    bool clickStarted = false;

    bool hide = false;

    std::function<void()> func;

   public:
    Button(std::string imgPath, SDL_Rect dims, std::function<void()> _fn);

    void Display();
    void CheckClick();
    void MakeHidden(bool hidden) { hide = hidden; };
    SDL_Rect getRect() {
        return this->buttonRect;
    }

    void setRect(SDL_Rect r) {
        this->buttonRect = r;
        this->clickRegion = r;
    }

    [[nodiscard]] bool IsClicked() const { return clicked; }
};

#endif  // HACK_A_DUCK_BUTTON_H
