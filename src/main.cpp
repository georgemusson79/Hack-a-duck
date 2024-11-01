//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED
#include <iostream>

#include "MainGameplay/Duck.h"
#include "MainGameplay/Path.h"
#include "MainMenu/Menu.h"
#include "UserInterface/MainWindow.h"
#include "UserInterface/Mouse.h"

int main(int argc, char** argv) {
    /*
     * SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP
     */
    window = std::make_unique<MainWindow>();
    mouse = std::make_unique<Mouse>();
    SetupPath();

    Menu m;

    Duck::PlaceDuck();

    cats.emplace_back(new GenericCat());

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
