//
// Created by cew05 on 01/11/2024.
//

#define SDL_MAIN_HANDLED
#include <iostream>

#include "UserInterface/MainWindow.h"
#include "UserInterface/Button.h"
#include "UserInterface/Mouse.h"

int main(int argc, char** argv) {
    window = std::make_unique<MainWindow>();
    mouse = std::make_unique<Mouse>();

    Button b;

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

        b.Display();

        b.CheckClick();

        if (b.IsClicked()) printf("wwwwwwww");

        window->Display();
    }

    return 0;
}
