//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED

#include <iostream>
#include "User Interface/MainWindow.h"

int main(int argc, char** argv) {
    window = std::make_unique<MainWindow>();

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

        window->Display();


    }

    return 0;
}
