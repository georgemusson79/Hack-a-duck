//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED
#include <iostream>

#include "MainGameplay/Duck.h"
#include "MainMenu/Menu.h"
#include "UserInterface/MainWindow.h"
#include "UserInterface/Mouse.h"
#include "MainGameplay/Path.h"

int main(int argc, char** argv) {

    /*
     * SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP
     */

    window = std::make_unique<MainWindow>();
    mouse = std::make_unique<Mouse>();
    SetupPath();

    Menu m;

    // Path creation
    SetupPath();
    cats.push_back(std::make_unique<GenericCat>());

    // Time tracking
    Uint64 tickStart;
    Uint64 tickEnd;
    Uint64 deltaTicks;

    bool running = true;
    while (running) {
        // Update deltaTicks
        tickStart = SDL_GetTicks64();
        deltaTicks = tickStart - tickEnd;
        tickEnd = tickStart;

        // Check for exit / other events
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

        // Update mouse
        mouse->UpdateActive();

        /*
         * MAIN MENU / BACKGROUND / MAIN MENU / BACKGROUND
         */

        m.Display();

        /*
         * DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS
         */

        // Check for the user trying to place a duck down
        Duck::PlaceDuck();

        for (auto& duck : playerDucks) {
            duck->Display();

            // find target
            duck->FindTarget();

            // attack target
            duck->AttackTarget(deltaTicks);
            duck->Update();
        }

        /*
         * CATS CATS CATS CATS CATS CATS CATS CATS CATS CATS CATS
         */

        for (auto& cat : cats) {
            cat->Display();
            cat->moveToNextPath();
        }

        window->Display();
    }

    return 0;
}
