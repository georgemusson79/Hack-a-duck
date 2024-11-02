//
// Created by cew05 on 02/11/2024.
//

#ifndef HACK_A_DUCK_PLAYER_H
#define HACK_A_DUCK_PLAYER_H

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../UserInterface/MainWindow.h"

class Player {
    private:

        TTF_Font* font = TTF_OpenFont("../resources/TCFR.ttf", 100);
        int lives = 150;
        int lastLives = lives + 1;
        SDL_Texture* livesTexture;
        SDL_Rect* livesRect;

        int money = 350;
        int lastMoney = money + 1;
        SDL_Texture* moneyTexture;
        SDL_Rect* moneyRect;

    public:
        Player() = default;
        void Setup();

        void TakeDamage(int _dmg);
        void AddMoney(int _amount);

        void Display();

        [[nodiscard]] int GetMoney() const { return money; };
};

inline std::unique_ptr<Player> player;

#endif //HACK_A_DUCK_PLAYER_H
