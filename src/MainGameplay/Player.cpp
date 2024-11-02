//
// Created by cew05 on 02/11/2024.
//

#include "Player.h"

void Player::Setup() {
    lives = 1;
    money = 350;

    livesRect = new SDL_Rect{25, 25, 150, 25};
    moneyRect = new SDL_Rect{625, 25, 150, 25};
}

void Player::TakeDamage(int _dmg) {
    lives -= _dmg;

    if (lives <= 0) {
        // game over!
    }
}

void Player::Display() {
    // Recreate lives text
    if (lives != lastLives) {
        SDL_Color c{255, 255, 255, 255};
        std::string livesString = "Lives: " + std::to_string(lives);
        SDL_Surface* s = TTF_RenderText_Blended(font, livesString.c_str(), c);
        livesTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);
        lastLives = lives;
    }

    // Recreate money text
    if (money != lastMoney) {

        SDL_Color c{255, 255, 255, 255};
        std::string livesString = "Bread Funds: " + std::to_string(money);
        SDL_Surface* s = TTF_RenderText_Blended(font, livesString.c_str(), c);
        moneyTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);
        lastMoney = money;
    }

    SDL_RenderCopy(window->GetRenderer(), livesTexture, nullptr, livesRect);
    SDL_RenderCopy(window->GetRenderer(), moneyTexture, nullptr, moneyRect);
}

void Player::UpdateSelection(int _scroll) {
    _scroll = _scroll/_scroll; // turn to +-1

    int selected = (int)holdingDucky;
    selected += _scroll;

    if (selected < (int)DUCK::NONE) selected = (int)DUCK::BASIC;
    if (selected > (int)DUCK::BASIC) selected = (int)DUCK::NONE;

    holdingDucky = (DUCK)selected;
}

void Player::AddMoney(int _amount) {
    money += _amount;
}