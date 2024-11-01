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

class Button {
   private:
    SDL_Rect clickRegion{};
    SDL_Rect buttonRect{};

    std::string imgPath = "../resources/StartButten.png";
    SDL_Texture* buttonTexture{};
    std::function<void()> fn;

    bool clicked = false;
    bool clickStarted = false;

   public:
    template <typename Fn>
    Button(std::string imgPath, SDL_Rect dims, Fn fn) {
        this->imgPath = imgPath;

        buttonRect = dims;
        clickRegion = buttonRect;
        this->fn = std::bind(fn);

        auto s = IMG_Load(imgPath.c_str());
        buttonTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);
    }

    void Display();
    void CheckClick();
    [[nodiscard]] bool IsClicked() const { return clicked; }
};

#endif  // HACK_A_DUCK_BUTTON_H
