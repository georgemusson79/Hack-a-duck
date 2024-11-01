//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED

#include <iostream>

#include "MainWindow.h"

int main(int argc, char** argv) {
    MainWindow* w = new MainWindow();

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_RenderPresent(w->GetRenderer());
        SDL_RenderClear(w->GetRenderer());
    }

    return 0;
}
