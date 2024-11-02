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

    if (TTF_Init() != 0) {
        printf("ERROR INITING TTF");
        return 0;
    }

    Menu m;
    Node* b = new Node({50, 50}, NULL, true);
    Node* n = new Node({0, 0}, b, false);
    b->generateTextures();

    // Path creation
    SetupPath();
    cats.push_back(std::make_unique<GenericCat>());

    // Player Setup
    player = std::make_unique<Player>();
    player->Setup();

    // Time tracking
    Uint64 tickStart;
    Uint64 tickEnd;
    Uint64 deltaTicks;

    /*
     * MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP
     */

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
        n->render();

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

        for (auto cat = cats.begin(); cat != cats.end();) {
            cat->get()->Display();
            cat->get()->MoveToNode();

            if (cat->get()->IsDead() || cat->get()->ReachedEnd())
                cat = cats.erase(cat);
            else
                cat++;
        }

        /*
         * PLAYER UI PLAYER UI PLAYER UI PLAYER UI PLAYER UI PLAYER
         */

        player->Display();
        window->Display();
    }

    return 0;
}
