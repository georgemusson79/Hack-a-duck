//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED
#include <SDL_mixer.h>

#include <iostream>
#include <SDL.h>

#include "MainGameplay/Duck.h"
#include "MainGameplay/Path.h"
#include "MainMenu/Menu.h"
#include "UserInterface/MainWindow.h"
#include "UserInterface/Mouse.h"
#include "UserInterface/Sound.h"

int main(int argc, char** argv) {
    /*
     * SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP
     */

    window = std::make_unique<MainWindow>();
    mouse = std::make_unique<Mouse>();

    tm = std::make_unique<TextureManager>();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "shitass mixer broke :(\n";
        return 0;
    }
    if (TTF_Init() != 0) {
        printf("ERROR INITING TTF");
        return 0;
    }

    Menu userMenu;
//    Node* b = new Node({50, 50}, NULL, true);
//    Node* n = new Node({0, 0}, b, false);
//    b->generateTextures();

    // Path creation
    SetupPath();

    // Player Setup
    player = std::make_unique<Player>();

    // Time tracking
    Uint64 tickStart;
    Uint64 tickEnd;
    Uint64 deltaTicks;

    /*
     * MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP MAIN LOOP
     */

    bool running = true;
    bool gameMenuFlop = false;

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

                case SDL_MOUSEWHEEL:
                    player->UpdateSelection((int)e.wheel.y);
            }
        }

        // Update mouse
        mouse->UpdateActive();

        /*
         * MAIN MENU / BACKGROUND / MAIN MENU / BACKGROUND
         */

        userMenu.Display();

        if (!gameMenuFlop) {
            userMenu.CheckButtons();
            gameMenuFlop = userMenu.MenuClosed();
        }

        if (player->GameOver()) {
            userMenu.ReturnToMenu();
            cats.clear();
            playerDucks.clear();
        }

        /*
         * DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS DUCKS
         */

        // Check for the user trying to place a duck down
        if (gameMenuFlop) {
            DisplayDuckMode();

            Duck::DuckAtMouse(40);
            if (player->HoldingDuck() == DUCK::NONE && mouse->IsUnheldActive() && mouseHoverDuck != nullptr) {
                mouseHoverDuck->ShowUpgradeWindow(true);
                selectedDuck = mouseHoverDuck;
            }
            else if (player->HoldingDuck() == DUCK::NONE && mouse->IsUnheldActive() && mouseHoverDuck == nullptr) {
                if (selectedDuck != nullptr && mouse->GetPosition().first <= 800) {
                    selectedDuck->ShowUpgradeWindow(false);
                    selectedDuck = nullptr;
                }
            }

            if (mouse->GetPosition().first >= 25 && mouse->GetPosition().first <= 775 &&
                    mouse->GetPosition().second >= 25 && mouse->GetPosition().second <= 775)
                Duck::PlaceDuck();
        }

        for (auto& duck : playerDucks) {
            duck->Display();

            // find target
            duck->FindTarget();

            // attack target
            duck->AttackTarget(deltaTicks);
            duck->Update(deltaTicks);
            duck->CheckButtons();
        }

        /*
         * CATS CATS CATS CATS CATS CATS CATS CATS CATS CATS CATS
         */

        if (userMenu.RoundStarted() && !catsSummoned) SummonCats(userMenu.GetLevel());

        for (auto cat = cats.begin(); cat != cats.end();) {
            cat->get()->Display();
            cat->get()->MoveToNode(deltaTicks);

            if (cat->get()->IsDead() || cat->get()->ReachedEnd()) cat = cats.erase(cat);
            else cat++;
        }

        // cats defeated?
        if (catsSummoned && cats.empty()) {
            player->AddMoney(userMenu.EndRound());
            catsSummoned = false;
        }

        /*
         * PLAYER UI PLAYER UI PLAYER UI PLAYER UI PLAYER UI PLAYER
         */

        if (gameMenuFlop) player->Display();
        window->Display();
    }

    return 0;
}
