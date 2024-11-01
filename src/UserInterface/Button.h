//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_BUTTON_H
#define HACK_A_DUCK_BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

class Button {
    private:
        SDL_Rect* clickRegion {};
        SDL_Rect* buttonRect {};

        std::string imgPath = "../../resources/StartButten.png";
        SDL_Texture* buttonTexture {};

        bool clicked = false;
        bool clickStarted = false;

    public:
        Button();

        void Display();
        void CheckClick();
};


#endif //HACK_A_DUCK_BUTTON_H
