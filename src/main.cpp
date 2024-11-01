//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED
#include <iostream>

#include "MainGameplay/Duck.h"
#include "MainMenu/Menu.h"
#include "UserInterface/MainWindow.h"
#include "UserInterface/Mouse.h"

int main(int argc, char** argv) {
    window = std::make_unique<MainWindow>();
    mouse = std::make_unique<Mouse>();
    Menu m;

    Duck::PlaceDuck();

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouse->MouseDown(true);
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouse->MouseDown(false);
                    break;
            }
        }
        mouse->UpdateActive();
        m.update();

        Duck::PlaceDuck();

        for (auto& duck : playerDucks) {
            duck->Display();
        }

        window->Display();
    }

    return 0;
}
